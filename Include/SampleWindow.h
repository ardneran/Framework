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
#include "AbstractWindow.h"

class SampleWindow : public AbstractWindow {
public:
    SampleWindow(Parameters& parameters);
    virtual ~SampleWindow();

    virtual void onIdle();

private:
    void createEffects();
    void createScene();
    void destroyEffects();
    void destroyScene();

	Vec3 getDirection(const unsigned int& octant);
	void testTransform();

    VisualEffect* m_visualEffects[3];
};

#endif
