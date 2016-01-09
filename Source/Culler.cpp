//
//  Culler.cpp
//  Framework
//
//  Created by Narendra Umate on 12/31/15.
//
//

#include "Culler.h"

// TODO fix this class so it actually does the thing it is supposed to do

Culler::Culler() {
}

Culler::~Culler() {
}

std::list<Spatial*> Culler::cull(Camera* camera, Octree* octree) {
    std::list<Spatial*> culledSpatials;
    culledSpatials = octree->collect();
    return culledSpatials;
}
