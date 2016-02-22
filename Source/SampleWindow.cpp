//
//  SampleWindow.cpp
//
//
//  Created by Narendra Umate on 8/18/15.
//
//

#include "SampleWindow.h"

SampleWindow::SampleWindow(Parameters& parameters)
: SDLWindow(parameters) {
    createEffects();
    createScene();
}

SampleWindow::~SampleWindow() {
    destroyScene();
    destroyEffects();
}

void SampleWindow::createEffects() {
    m_visualEffects[0] = new VisualEffect(new GlProgram("smooth.vert", "smooth.frag"));
    m_visualEffects[1] = new VisualEffect(new GlProgram("gouraud.vert", "gouraud.frag"));
    m_visualEffects[2] = new VisualEffect(new GlProgram("phong.vert", "phong.frag"));
}

void SampleWindow::createScene() {
    const int visualEffectType = 0;
#define TEST
#ifdef TEST
    std::list<VisualSpatial*> visualsCube = m_objMeshLoader->load(Utils::findFilePath("house/house.obj"),
                                                                  Utils::findBasePath("house/house.obj"));
    for (std::list<VisualSpatial*>::iterator it = visualsCube.begin(); it != visualsCube.end(); ++it) {
        (*it)->setVisualEffect(m_visualEffects[visualEffectType]);
		(*it)->setTranslate(Vec3(0, -1.25, 0));
		(*it)->setRotate(Quat(0, 30 * M_DEGREE_TO_RADIAN, 0));
		(*it)->setScale(Vec3(0.09f, 0.09f, 0.09f));
        m_octree->insert(*it);
    }

#else
    for (int i = 0; i < 8; ++i) {
        std::list<VisualSpatial*> visualsCube = m_objMeshLoader->load(Utils::findFilePath("cube/cube.obj"),
                                                                      Utils::findBasePath("cube/cube.obj"));
        for (std::list<VisualSpatial*>::iterator it = visualsCube.begin(); it != visualsCube.end(); ++it) {
			(*it)->setVisualEffect(m_visualEffects[visualEffectType]);
            (*it)->setTranslate(getDirection(i) * 2.5);
            m_octree->insert(*it);
        }
        std::list<VisualSpatial*> visualsTeapot = m_objMeshLoader->load(Utils::findFilePath("teapot/teapot.obj"),
                                                                        Utils::findFilePath("teapot/teapot.obj"));
        for (std::list<VisualSpatial*>::iterator it = visualsTeapot.begin(); it != visualsTeapot.end(); ++it) {
            (*it)->setVisualEffect(m_visualEffects[visualEffectType]);
            (*it)->setTranslate(getDirection(i) * 1.25);
			(*it)->setScale(Vec3(0.0025,0.0025,0.0025));
            m_octree->insert(*it);
        }
    }
#endif
}

void SampleWindow::destroyEffects() {
    if (m_visualEffects[0]) {
        delete m_visualEffects[0];
    }
    if (m_visualEffects[1]) {
        delete m_visualEffects[1];
    }
    if (m_visualEffects[2]) {
        delete m_visualEffects[2];
    }
}

void SampleWindow::destroyScene() {
}

Vec3 SampleWindow::getDirection(const unsigned int& octant) {
    unsigned int localOctant = octant % 8;
    switch (localOctant) {
        case 0:
            return Vec3(-1, -1, -1);
        case 1:
            return Vec3(-1, -1, +1);
        case 2:
            return Vec3(-1, +1, -1);
        case 3:
            return Vec3(-1, +1, +1);
        case 4:
            return Vec3(+1, -1, -1);
        case 5:
            return Vec3(+1, -1, +1);
        case 6:
            return Vec3(+1, +1, -1);
        case 7:
        default:
            return Vec3(+1, +1, +1);
    }
}

void SampleWindow::testTransform() {
    Transform a;
    a.setTranslate(Vec3(1000, 2000, 3000));
    a.setRotate(Quat(100 * M_DEGREE_TO_RADIAN, 200 * M_DEGREE_TO_RADIAN, 300 * M_DEGREE_TO_RADIAN));
    a.setScale(Vec3(10, 20, 30));
    Transform b;
    b.setTranslate(Vec3(100, 200, 300));
    b.setRotate(Quat(10 * M_DEGREE_TO_RADIAN, 20 * M_DEGREE_TO_RADIAN, 30 * M_DEGREE_TO_RADIAN));
    b.setScale(Vec3(1, 2, 3));
    Transform c = a * b;
}
