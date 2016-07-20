//
//  GLFWWindow.h
//  Framework
//
//  Created by Narendra Umate on 7/17/16.
//
//

#ifndef GLFWWindow_h
#define GLFWWindow_h

#include "AbstractWindow.h"

struct Parameters;

class GLFWWindow : public AbstractWindow {

public:
	GLFWWindow(Parameters& parameters);
	virtual ~GLFWWindow() = 0;

	void handlePollEvent();

	virtual void setSwapInterval(const int& syncInterval);
	virtual void swapWindow();

private:
	void initializeGLFW();
	void initializeOpenGL();
	void deinitializeGLFW();
	void deinitializeOpenGL();

	void handleWindowEvent();
	void handleKeyUpEvent();
	void handleKeyDownEvent();
};

#endif /* GLFWWindow_h */
