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
    m_renderer->initialize();
    m_renderer->setSize(parameters.xSize, parameters.ySize);
    m_camera->setPosition(Vec3(0.0f, 0.0f, 10.0f));
    if (m_camera->getType() == Camera::Type::Perspective) {
        m_camera->setFrustum(45.0f, float(parameters.xSize) / float(parameters.ySize), 1.0f, 100.0f);
    }
    createEffects();
    createScene();
}

SampleWindow::~SampleWindow() {
    destroyScene();
    destroyEffects();
    m_renderer->deinitialize();
}

void SampleWindow::onIdle() {
    m_renderer->clearBuffers();
    std::list<Spatial*> spatials = m_culler->cull(m_camera, m_octree);
    for (std::list<Spatial*>::iterator it = spatials.begin(); it != spatials.end(); ++it) {
        Visual* visual = dynamic_cast<Visual*>(*it);
        if (visual) {
            visual->setViewProjectionMatrix(m_camera->getViewProjectionMatrix());
            visual->setViewMatrix(m_camera->getViewMatrix());
            m_renderer->draw(visual);
        }
    }
    m_renderer->displayColorBuffer(0);
}

void SampleWindow::createEffects() {
    m_visualEffects[0] = new VisualEffect(new GlProgram("smooth.vert", "smooth.frag"));
    //m_visualEffects[1] = new VisualEffect(new GlProgram("gouraud.vert", "gouraud.frag"));
    //m_visualEffects[2] = new VisualEffect(new GlProgram("phong.vert", "phong.frag"));
}

void SampleWindow::createScene() {
    const int visualEffectType = 0;
#define TEST
#ifdef TEST
    std::list<Visual*> visualsCube = m_objMeshLoader->load(Utils::findFilePath("cornell_box/cornell_box_multimaterial.obj"),
                                                           Utils::findBasePath("cornell_box/cornell_box_multimaterial.obj"));
    for (std::list<Visual*>::iterator it = visualsCube.begin(); it != visualsCube.end(); ++it) {
        (*it)->setVisualEffect(m_visualEffects[visualEffectType]);
        m_octree->insert(*it);
    }

#else
    for (int i = 0; i < 8; ++i) {
        std::list<Visual*> visualsCube = m_objMeshLoader->load(Utils::findFilePath("cube/cube.obj"),
                                                               Utils::findBasePath("cube/cube.obj"));
        for (std::list<Visual*>::iterator it = visualsCube.begin(); it != visualsCube.end(); ++it) {
            (*it)->setTranslate(getDirection(i) * 10);
            (*it)->setVisualEffect(m_visualEffects[visualEffectType]);
            m_octree->insert(*it);
        }
        std::list<Visual*> visualsTeapot = m_objMeshLoader->load(Utils::findFilePath("teapot/teapot.obj"),
                                                                 Utils::findFilePath("teapot/teapot.obj"));
        for (std::list<Visual*>::iterator it = visualsTeapot.begin(); it != visualsTeapot.end(); ++it) {
            (*it)->setTranslate(getDirection(i) * 20);
            (*it)->setVisualEffect(m_visualEffects[visualEffectType]);
            m_octree->insert(*it);
        }
    }
#endif
}

void SampleWindow::destroyEffects() {
    if (m_visualEffects[0]) {
        delete m_visualEffects[0]->getProgram();
        delete m_visualEffects[0];
    }
    if (m_visualEffects[1]) {
        delete m_visualEffects[1]->getProgram();
        delete m_visualEffects[1];
    }
    if (m_visualEffects[2]) {
        delete m_visualEffects[2]->getProgram();
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
