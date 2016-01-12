//
//  SampleWindow.h
//  Framework
//
//  Created by Narendra Umate on 8/18/15.
//
//

#ifndef Framework_SampleWindow_h
#define Framework_SampleWindow_h

#include <list>
#include "Spatial.h"
#include "Window.h"

class SampleWindow : public Window {
public:
    SampleWindow(Parameters& parameters);
    virtual ~SampleWindow();

    virtual void onIdle();

private:
    void createScene();
    void destroyScene();
    Vec3 getDirection(const unsigned int& octant);
};

#endif
