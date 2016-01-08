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
}

SampleWindow::~SampleWindow() {
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
}

void SampleWindow::destroyScene() {
}
