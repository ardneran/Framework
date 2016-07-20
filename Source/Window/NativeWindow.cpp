//
//  NativeWindow.cpp
//
//
//  Created by Narendra Umate on 8/17/15.
//
//

#include "NativeWindow.h"

std::map<Nativewindow*, NativeWindow*> NativeWindow::s_windowMap;

void nativeErrorCallback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

void nativeFramebufferSizeCallback(Nativewindow* window, int width, int height) {
    NativeWindow::s_windowMap[window]->onResize(width, height);
}

void nativeWindowCloseCallback(Nativewindow* window) {
    NativeWindow::s_windowMap[window]->onClose();
}

void nativeKeyCallback(Nativewindow* window, int k, int s, int action, int mods) {
    /*
    const float increment = 0.50f;
    if (action == NATIVE_PRESS) {
        switch (k) {
            case NATIVE_KEY_ESCAPE:
                NativeWindow::s_windowMap[window]->onClose();
                break;
            case NATIVE_KEY_UP:
            {
                Vec3 position;
                NativeWindow::s_windowMap[window]->getCamera()->getPosition(position);
                NativeWindow::s_windowMap[window]->getCamera()->setPosition(position + Vec3(0, 0, increment));
            }
                break;
            case NATIVE_KEY_DOWN:
            {
                Vec3 position;
                NativeWindow::s_windowMap[window]->getCamera()->getPosition(position);
                NativeWindow::s_windowMap[window]->getCamera()->setPosition(position + Vec3(0, 0, -increment));
            }
                break;
            case NATIVE_KEY_RIGHT:
            {
                Vec3 position;
                NativeWindow::s_windowMap[window]->getCamera()->getPosition(position);
                NativeWindow::s_windowMap[window]->getCamera()->setPosition(position + Vec3(increment, 0, 0));
            }
                break;
            case NATIVE_KEY_LEFT:
            {
                Vec3 position;
                NativeWindow::s_windowMap[window]->getCamera()->getPosition(position);
                NativeWindow::s_windowMap[window]->getCamera()->setPosition(position + Vec3(-increment, 0, 0));
            }
                break;
            default:
                break;
        }
    }
    */
}

NativeWindow::NativeWindow(Parameters& parameters)
: AbstractWindow(parameters)
, m_nativeWindow(NULL) {
    initializeNative();
    initializeMetal();
    m_renderer->initialize(); // Called here after the context is created.
}

NativeWindow::~NativeWindow() {
    m_renderer->deinitialize(); // Called here before the context is destroyed.
    deinitializeMetal();
    deinitializeNative();
}

void NativeWindow::handlePollEvent() {
    ////nativePollEvents();
}

void NativeWindow::setSwapInterval(const int& syncInterval) {
    ////nativeSwapInterval(syncInterval);
}

void NativeWindow::swapWindow() {
    ////nativeSwapBuffers(m_nativeWindow);
}

void NativeWindow::initializeNative() {
    ////nativeSetErrorCallback(nativeErrorCallback);
    ////nativeInit();
}

void NativeWindow::initializeMetal() {
    /*nativeWindowHint(NATIVE_RESIZABLE, NATIVE_TRUE);
    
    // Create Context
    m_nativeWindow = nativeCreateWindow(m_xSize, m_ySize, m_title.c_str(), NULL, NULL);
    if (m_nativeWindow == NULL) {
        printf("nativeCreateWindow Error: Unknown\n");
        assert(m_nativeWindow != NULL);
    }
    
    // Set callbacks
    nativeSetFramebufferSizeCallback(m_nativeWindow, &nativeFramebufferSizeCallback);
    nativeSetWindowCloseCallback(m_nativeWindow, &nativeWindowCloseCallback);
    nativeSetKeyCallback(m_nativeWindow, &nativeKeyCallback);
    
    // Insert entry into map
    s_windowMap[m_nativeWindow] = this;
    nativeMakeContextCurrent(m_nativeWindow);
    
    // The returned dimensions could be different from the expected ones so scale accordingly
    int width = 0;
    int height = 0;
    nativeGetFramebufferSize(m_nativeWindow, &width, &height);
    onResize(width, height);*/
}

void NativeWindow::deinitializeNative() {
    ////nativeTerminate();
    ////nativeSetErrorCallback(NULL);
}

void NativeWindow::deinitializeMetal() {
    // Remove entry from map
    ////s_windowMap.erase(m_nativeWindow);
    ////nativeDestroyWindow(m_nativeWindow);
}
