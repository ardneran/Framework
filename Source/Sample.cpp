//
//  Sample.cpp
//  Framework
//
//  Created by Narendra Umate on 8/18/15.
//
//

#include "Sample.h"

int main(int argc, char* argv[]) {

    Window::Parameters parameters;
    parameters.title = "Framework";
    parameters.xOrigin = 0;
    parameters.yOrigin = 0;
    parameters.xSize = 1920;
    parameters.ySize = 1080;

    SampleWindow* sampleWindow = new SampleWindow(parameters);

    while (true) {
        sampleWindow->handleSwapWindow();
        if (sampleWindow->isActive()) {
            sampleWindow->handlePollEvent();
            sampleWindow->onIdle();
        } else {
            break;
        }
    }

    delete sampleWindow;

    return 0;
}
