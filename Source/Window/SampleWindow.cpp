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
	m_renderer->setClearColor(Gray);
	m_camera->setPosition(Vec3(0.0f, 0.0f, -10.0f));
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
    const int visualEffectTypeSmooth = 0;
	const int visualEffectTypePhong = 2;
	BoundingBox::visualEffect = m_visualEffects[visualEffectTypeSmooth];
#define TEST
#ifdef TEST
    std::list<VisualSpatial*> visualsCube = m_objMeshLoader->load(Utils::findFilePath("house/house.obj"),
                                                                  Utils::findBasePath("house/house.obj"));
    for (std::list<VisualSpatial*>::iterator it = visualsCube.begin(); it != visualsCube.end(); ++it) {
        (*it)->setVisualEffect(m_visualEffects[visualEffectTypePhong]);
		(*it)->setTranslate(Vec3(0, -2.5, 0));
		(*it)->setRotate(Quat(0, 0, 0));
		(*it)->setScale(Vec3(0.09f, 0.09f, 0.09f));
        m_octree->insert(*it);
    }
#else
    for (int i = 0; i < 8; ++i) {
        std::list<VisualSpatial*> visualsCube = m_objMeshLoader->load(Utils::findFilePath("cube/cube.obj"),
                                                                      Utils::findBasePath("cube/cube.obj"));
        for (std::list<VisualSpatial*>::iterator it = visualsCube.begin(); it != visualsCube.end(); ++it) {
			(*it)->setVisualEffect(m_visualEffects[visualEffectTypeSmooth]);
            (*it)->setTranslate(getDirection(i) * 2.5);
            m_octree->insert(*it);
        }
        std::list<VisualSpatial*> visualsTeapot = m_objMeshLoader->load(Utils::findFilePath("teapot/teapot.obj"),
                                                                        Utils::findBasePath("teapot/teapot.obj"));
        for (std::list<VisualSpatial*>::iterator it = visualsTeapot.begin(); it != visualsTeapot.end(); ++it) {
            (*it)->setVisualEffect(m_visualEffects[visualEffectTypePhong]);
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
