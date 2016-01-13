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
    createScene();
}

SampleWindow::~SampleWindow() {
    destroyScene();
    m_renderer->deinitialize();
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
    /*
	Transform a;
    a.setTranslate(Vec3(1000, 2000, 3000));
    a.setRotate(Quat(100 * M_DEGREE_TO_RADIAN, 200 * M_DEGREE_TO_RADIAN, 300 * M_DEGREE_TO_RADIAN));
    a.setScale(Vec3(10, 20, 30));
    Transform b;
    b.setTranslate(Vec3(100, 200, 300));
    b.setRotate(Quat(10 * M_DEGREE_TO_RADIAN, 20 * M_DEGREE_TO_RADIAN, 30 * M_DEGREE_TO_RADIAN));
    b.setScale(Vec3(1, 2, 3));
    Transform c = a * b;
	*/

    // TODO Update eye position when camera moves
    Vec3 eyePosition; // = m_camera->getPosition();

    const int programType = 1;

    for (int i = 0; i < 8; ++i) {
        std::list<Visual*> visualsCube = m_objMeshLoader->load("/Users/ardneran/Documents/Projects/GitHub/Framework/Meshes/cube/cube.obj",
                                                               "/Users/ardneran/Documents/Projects/GitHub/Framework/Meshes/cube/");
        for (std::list<Visual*>::iterator it = visualsCube.begin(); it != visualsCube.end(); ++it) {
            (*it)->setTranslate(Spatial::Space::World, getDirection(i) * 10);
            GlProgram* program = NULL;
            switch (programType) {
                case 0:
                    program = new GlProgram("gouraud.vert", "gouraud.frag");
                    break;
                case 1:
                    program = new GlProgram("phong.vert", "phong.frag");
                    break;
            }
            program->set3fv("eyePosition", 1, (float*)&eyePosition);
            (*it)->setProgram(program);
            m_octree->insert(*it);
        }
        std::list<Visual*> visualsTeapot = m_objMeshLoader->load("/Users/ardneran/Documents/Projects/GitHub/Framework/Meshes/teapot/teapot.obj",
                                                                 "/Users/ardneran/Documents/Projects/GitHub/Framework/Meshes/teapot/");
        for (std::list<Visual*>::iterator it = visualsTeapot.begin(); it != visualsTeapot.end(); ++it) {
            (*it)->setTranslate(Spatial::Space::World, getDirection(i) * 20);
            GlProgram* program = NULL;
            switch (programType) {
                case 0:
                    program = new GlProgram("gouraud.vert", "gouraud.frag");
                    break;
                case 1:
                    program = new GlProgram("phong.vert", "phong.frag");
                    break;
            }
            program->set3fv(program->getLocation("eyePosition"), 1, (float*)&eyePosition);
            (*it)->setProgram(program);
            m_octree->insert(*it);
        }
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
