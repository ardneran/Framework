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

    SDL_Event event;

    while (true) {
        if (sampleWindow->isActive()) {
            if (SDL_PollEvent(&event)) {
                sampleWindow->handleEvent(event);
            } else {
                sampleWindow->onIdle();
            }
        } else {
            break;
        }
    }

    delete sampleWindow;

    return 0;
}
