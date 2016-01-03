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
    m_renderer->setClearColor(Color::Gray);
    m_renderer->clearColorBuffer();
    createScene();
}

SampleWindow::~SampleWindow() {
}

void SampleWindow::onIdle() {
    m_renderer->clearBuffers();
    m_renderer->displayColorBuffer(0);
}

void SampleWindow::createScene() {
}
