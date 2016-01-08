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
#include "Culler.h"
#include "Octree.h"
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

    Octree* m_octree;
    Culler* m_culler;
};

#endif
