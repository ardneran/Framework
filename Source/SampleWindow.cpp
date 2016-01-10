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
    for (int i = 0; i < 5; ++i) {
        std::list<Visual*> visualsCube = m_objMeshLoader->load("/Users/ardneran/Documents/Projects/GitHub/Framework/Meshes/cube/cube.obj",
                                                               "/Users/ardneran/Documents/Projects/GitHub/Framework/Meshes/cube/");
        for (std::list<Visual*>::iterator it = visualsCube.begin(); it != visualsCube.end(); ++it) {
            m_octree->insert(*it);
        }
    }
    for (int i = 0; i < 5; ++i) {
        std::list<Visual*> visualsTeapot = m_objMeshLoader->load("/Users/ardneran/Documents/Projects/GitHub/Framework/Meshes/teapot/teapot.obj",
                                                                 "/Users/ardneran/Documents/Projects/GitHub/Framework/Meshes/teapot/");
        for (std::list<Visual*>::iterator it = visualsTeapot.begin(); it != visualsTeapot.end(); ++it) {
            m_octree->insert(*it);
        }
    }
}

void SampleWindow::destroyScene() {
}
