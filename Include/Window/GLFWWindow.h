//
//  GLFWWindow.h
//  Framework
//
//  Created by Narendra Umate on 7/17/16.
//
//

#ifndef GLFWWindow_h
#define GLFWWindow_h

#include <cassert>

#include "AbstractWindow.h"

#include "glfw3.h"
#include "glfw_config.h"

struct Parameters;

class GLFWWindow : public AbstractWindow {

public:
	GLFWWindow(Parameters& parameters);
	virtual ~GLFWWindow() = 0;

	void handlePollEvent();

	virtual void setSwapInterval(const int& syncInterval);
	virtual void swapWindow();

    static std::map<GLFWwindow*, GLFWWindow*> s_windowMap;
    
private:
	void initializeGLFW();
    void initializeOpenGL();
	void deinitializeGLFW();
    void deinitializeOpenGL();

    GLFWwindow* m_glfwWindow;
};

#endif /* GLFWWindow_h */
