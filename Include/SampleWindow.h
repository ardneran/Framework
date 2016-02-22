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
#include "SDLWindow.h"

class SampleWindow : public SDLWindow {
public:
    SampleWindow(Parameters& parameters);
    virtual ~SampleWindow();

private:
    void createEffects();
    void createScene();
    void destroyEffects();
    void destroyScene();

	Vec3 getDirection(const unsigned int& octant); // TODO Remove
	void testTransform(); // TODO Remove

    VisualEffect* m_visualEffects[3];
};

#endif
