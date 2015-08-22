//
//  Main.cpp
//  Framework
//
//  Created by Narendra Umate on 8/18/15.
//
//

#include "Main.h"

int main(int argc, char* argv[]) {

	Window::Parameters parameters;
	parameters.title = "Framework";
	parameters.xOrigin = 0;
	parameters.yOrigin = 0;
	parameters.xSize = 1024;
	parameters.ySize = 768;

	SampleWindow* sampleWindow = new SampleWindow(parameters);

	while (sampleWindow->isActive()) {
		sampleWindow->onIdle();
	}

	delete sampleWindow;

	return 0;
}
