//
//  SampleWindow.cpp
//
//
//  Created by Narendra Umate on 8/18/15.
//
//

#include "SampleWindow.h"

SampleWindow::SampleWindow(Parameters& parameters)
: Window(parameters) {
    createScene();
    m_culler = new Culler();
}

SampleWindow::~SampleWindow() {
    delete m_culler;
    destroyScene();
}

void SampleWindow::onIdle() {
    m_renderer->clearBuffers();
    m_renderer->displayColorBuffer(0);
    std::list<Spatial*> spatials = m_culler->cull(m_camera, m_octree);
    for (std::list<Spatial*>::iterator it = spatials.begin(); it != spatials.end(); ++it) {
        m_renderer->draw(static_cast<Visual*>(*it));
    }
}

void SampleWindow::createScene() {
    m_octree = new Octree(0, BoundingBox(Vec3::zero, Vec3(100.0f, 100.0f, 100.0f)));
}

void SampleWindow::destroyScene() {
    delete m_octree;
}
