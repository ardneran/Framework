//
//  AbstractWindow.cpp
//  Framework
//
//  Created by Narendra Umate on 2/21/16.
//
//

#include "AbstractWindow.h"

AbstractWindow::AbstractWindow(Parameters& parameters)
: m_title(parameters.title)
, m_xOrigin(parameters.xOrigin)
, m_yOrigin(parameters.yOrigin)
, m_xSize(parameters.xSize)
, m_ySize(parameters.ySize)
, m_renderer(parameters.renderer)
, m_minimized(false)
, m_maximized(false)
, m_active(true) {
	m_renderer->setWindow(this);
	m_camera = new Camera(Camera::Perspective);
	if (m_camera) {
		if (m_camera->getType() == Camera::Orthographic) {
			m_camera->setFrustum(float(parameters.xSize) / 2.0f, -float(parameters.xSize) / 2.0f, float(parameters.ySize) / 2.0f, -float(parameters.ySize) / 2.0f, 1.0f, 100.0f);
		} else if (m_camera->getType() == Camera::Perspective) {
			m_camera->setFrustum(45.0f, float(parameters.xSize) / float(parameters.ySize), 0.1f, 1000.0f);
		}
	}
	m_octree = new Octree(0, Bound3(Vec3::zero, Vec3(100.0f, 100.0f, 100.0f)));
	m_objMeshLoader = new ObjMeshLoader();
}

AbstractWindow::~AbstractWindow() {
	if (m_objMeshLoader != NULL) {
		delete m_objMeshLoader;
	}
	if (m_octree != NULL) {
		delete m_octree;
	}
	if (m_camera != NULL) {
		delete m_camera;
	}
}

void AbstractWindow::onMove(const int& x, const int& y) {
	m_xOrigin = x;
	m_yOrigin = y;
}

bool AbstractWindow::onResize(const int& xSize, const int& ySize) {
	m_minimized = false;
	m_maximized = false;

	if (m_xSize != xSize || m_ySize != ySize) {
		m_xSize = xSize;
		m_ySize = ySize;

		if (m_renderer) {
			m_renderer->setSize(xSize, ySize);
		}

		if (m_camera) {
			m_camera->setSize(xSize, ySize);
		}

		return true;
	}
	return false;
}

void AbstractWindow::onMinimize() {
	m_minimized = true;
	m_maximized = false;
}

void AbstractWindow::onMaximize() {
	m_minimized = false;
	m_maximized = true;
}

void AbstractWindow::onRestore() {
	m_minimized = false;
	m_maximized = false;
}

void AbstractWindow::onDisplay() {
}

void AbstractWindow::onIdle() {
	// Update Octree.
	m_octree->update();
	std::list<Spatial*> spatials;
	m_octree->collectTree(spatials, m_camera);
	std::cout << "Spatials size: " << spatials.size() << "\n";

	// Render Octree.
	// Push common uniforms to all shaders.
	// TODO Remove hardcoded loop limit.
	for (int i = 0; i < 3; ++i) {
		static_cast<GlProgram*>(m_visualEffects[i]->getProgram())->set3fv("eyePosition", 1, m_camera->getPosition().data);
	}
	m_renderer->clearBuffers();
	for (std::list<Spatial*>::iterator it = spatials.begin(); it != spatials.end(); ++it) {
		VisualSpatial* visual = dynamic_cast<VisualSpatial*>(*it);
		if (visual) {
			visual->setViewProjectionMatrix(m_camera->getViewProjectionMatrix());
			visual->setViewMatrix(m_camera->getViewMatrix());
			m_renderer->draw(visual);
		}
	}
	m_renderer->displayColorBuffer(0);
}

void AbstractWindow::onClose() {
    m_active = false;
}
