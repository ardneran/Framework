//
//  Sample.cpp
//  Framework
//
//  Created by Narendra Umate on 8/18/15.
//
//

#include "Sample.h"

int main(int argc, char* argv[]) {

    Parameters parameters;
    parameters.title = "Framework";
    parameters.xOrigin = 0;
    parameters.yOrigin = 0;
    parameters.xSize = 1280;
    parameters.ySize = 720;
#define USE_GL 1
#if USE_GL
	parameters.renderer = new GlRenderer(parameters.xSize, parameters.ySize);
#else
    parameters.renderer = new MetalRenderer(parameters.xSize, parameters.ySize);
#endif
#undef USE_GL
    SampleWindow* sampleWindow = new SampleWindow(parameters);

    while (true) {
        if (sampleWindow->isActive()) {
            sampleWindow->handlePollEvent();
            if (!sampleWindow->isMinimized()) {
                sampleWindow->onIdle();
            }
        } else {
            break;
        }
    }

    delete sampleWindow;

    delete parameters.renderer;

    return 0;
}
