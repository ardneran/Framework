//
//  MetalWindow.h
//  Framework
//
//  Created by Narendra Umate on 7/17/16.
//
//

#ifndef MetalWindow_h
#define MetalWindow_h

#include "AbstractWindow.h"

struct Parameters;

class MetalWindow : public AbstractWindow {

public:
	MetalWindow(Parameters& parameters);
	virtual ~MetalWindow() = 0;

	void handlePollEvent();

	virtual void setSwapInterval(const int& syncInterval);
	virtual void swapWindow();

private:
	void initializeNative();
	void initializeMetal();
	void deinitializeNative();
	void deinitializeMetal();

	void handleWindowEvent();
	void handleKeyUpEvent();
	void handleKeyDownEvent();
};

#endif /* MetalWindow_h */
