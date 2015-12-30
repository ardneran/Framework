//
//  SampleWindow.h
//  Framework
//
//  Created by Narendra Umate on 8/18/15.
//
//

#ifndef Framework_SampleWindow_h
#define Framework_SampleWindow_h

#include "Window.h"

class SampleWindow : public Window {
public:
    SampleWindow(Parameters& parameters);
    ~SampleWindow();

    virtual void onIdle();

private:
    void createScene();
};

#endif
