//
//  GLFWWindow.cpp
//
//
//  Created by Narendra Umate on 8/17/15.
//
//

#include "GLFWWindow.h"

std::map<GLFWwindow*, GLFWWindow*> GLFWWindow::s_windowMap;

void glfwErrorCallback(int error, const char* description) {
    if (strncmp(description, "Requested client API version 4.5, got version 4.1", 32) != 0 &&
        strncmp(description, "Requested client API version 4.4, got version 4.1", 32) != 0 &&
        strncmp(description, "Requested client API version 4.3, got version 4.1", 32) != 0 &&
        strncmp(description, "Requested client API version 4.2, got version 4.1", 32) != 0) {
        fprintf(stderr, "Error %d: %s\n", error, description);
    }
}

void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    GLFWWindow::s_windowMap[window]->onResize(width, height);
}

void glfwWindowCloseCallback(GLFWwindow* window) {
    GLFWWindow::s_windowMap[window]->onClose();
}

void glfwKeyCallback(GLFWwindow* window, int k, int s, int action, int mods) {
    const float increment = 0.50f;
    if (action == GLFW_PRESS) {
        switch (k) {
            case GLFW_KEY_ESCAPE:
                GLFWWindow::s_windowMap[window]->onClose();
                break;
            case GLFW_KEY_UP:
            {
                Vec3 position = GLFWWindow::s_windowMap[window]->getCamera()->getPosition();
                GLFWWindow::s_windowMap[window]->getCamera()->setPosition(position + Vec3(0, 0, increment));
            }
                break;
            case GLFW_KEY_DOWN:
            {
                Vec3 position = GLFWWindow::s_windowMap[window]->getCamera()->getPosition();
                GLFWWindow::s_windowMap[window]->getCamera()->setPosition(position + Vec3(0, 0, -increment));
            }
                break;
            case GLFW_KEY_RIGHT:
            {
                Vec3 position = GLFWWindow::s_windowMap[window]->getCamera()->getPosition();
                GLFWWindow::s_windowMap[window]->getCamera()->setPosition(position + Vec3(increment, 0, 0));
            }
                break;
            case GLFW_KEY_LEFT:
            {
                Vec3 position = GLFWWindow::s_windowMap[window]->getCamera()->getPosition();
                GLFWWindow::s_windowMap[window]->getCamera()->setPosition(position + Vec3(-increment, 0, 0));
            }
                break;
            default:
                break;
        }
    }
}

GLFWWindow::GLFWWindow(Parameters& parameters)
: AbstractWindow(parameters)
, m_glfwWindow(NULL) {
    initializeGLFW();
    switch (m_renderer->getType()) {
        case Renderer::GL:
            initializeOpenGL();
            break;
            
        case Renderer::Metal:
            initializeMetal();
            break;
            
        default:
            break;
    }
    m_renderer->initialize(); // Called here after the context is created.
}

GLFWWindow::~GLFWWindow() {
	m_renderer->deinitialize(); // Called here before the context is destroyed.
    deinitializeOpenGL();
    deinitializeGLFW();
}

void GLFWWindow::handlePollEvent() {
    glfwPollEvents();
}

void GLFWWindow::setSwapInterval(const int& syncInterval) {
    glfwSwapInterval(syncInterval);
}

void GLFWWindow::swapWindow() {
    glfwSwapBuffers(m_glfwWindow);
}

void GLFWWindow::initializeGLFW() {
    glfwSetErrorCallback(glfwErrorCallback);
    glfwInit();
}

void GLFWWindow::initializeOpenGL() {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#if defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)
    // Create Context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CONTEXT_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CONTEXT_MINOR_VERSION);
    m_glfwWindow = glfwCreateWindow(m_xSize, m_ySize, m_title.c_str(), NULL, NULL);
    if (m_glfwWindow == NULL) {
        printf("glfwCreateWindow Error: Unknown\n");
        assert(m_glfwWindow != NULL);
    } else {
        std::cout << "OpenGL context: " << CONTEXT_MAJOR_VERSION << "." << CONTEXT_MINOR_VERSION << std::endl;
    }
#else
    // Create Context
    const int major[] = { 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 2 };
    const int minor[] = { 5, 4, 3, 2, 1, 0, 3, 2, 1, 0, 0 };
    int index = 0;
    for (index = 0; index < 11; ++index) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major[index]);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor[index]);
        m_glfwWindow = glfwCreateWindow(m_xSize, m_ySize, m_title.c_str(), NULL, NULL);
        if (m_glfwWindow != NULL) {
            break;
        }
    }
    if (m_glfwWindow == NULL) {
        printf("glfwCreateWindow Error: Unknown\n");
        assert(m_glfwWindow != NULL);
    } else {
        std::cout << "OpenGL context: " << major[index] << "." << minor[index] << std::endl;
    }
#endif // defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)

    // Set callbacks
    glfwSetFramebufferSizeCallback(m_glfwWindow, &glfwFramebufferSizeCallback);
    glfwSetWindowCloseCallback(m_glfwWindow, &glfwWindowCloseCallback);
    glfwSetKeyCallback(m_glfwWindow, &glfwKeyCallback);

    // Insert entry into map
    s_windowMap[m_glfwWindow] = this;
    glfwMakeContextCurrent(m_glfwWindow);
    
    // The returned dimensions could be different from the expected ones so scale accordingly
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(m_glfwWindow, &width, &height);
    onResize(width, height);
}

void GLFWWindow::initializeMetal() {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    m_glfwWindow = glfwCreateWindow(m_xSize, m_ySize, m_title.c_str(), NULL, NULL);
    if (m_glfwWindow == NULL) {
        printf("glfwCreateWindow Error: Unknown\n");
        assert(m_glfwWindow != NULL);
    }
    
    // Set callbacks
    glfwSetFramebufferSizeCallback(m_glfwWindow, &glfwFramebufferSizeCallback);
    glfwSetWindowCloseCallback(m_glfwWindow, &glfwWindowCloseCallback);
    glfwSetKeyCallback(m_glfwWindow, &glfwKeyCallback);
    
    // Insert entry into map
    s_windowMap[m_glfwWindow] = this;
    glfwMakeContextCurrent(m_glfwWindow);
    
    // The returned dimensions could be different from the expected ones so scale accordingly
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(m_glfwWindow, &width, &height);
    onResize(width, height);
}

void GLFWWindow::deinitializeGLFW() {
    glfwTerminate();
    glfwSetErrorCallback(NULL);
}

void GLFWWindow::deinitializeOpenGL() {
    // Remove entry from map
    s_windowMap.erase(m_glfwWindow);
    glfwDestroyWindow(m_glfwWindow);
}

void GLFWWindow::deinitializeMetal() {
}
