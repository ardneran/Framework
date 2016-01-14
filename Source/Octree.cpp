//
//  Octree.cpp
//  Framework
//
//  Created by Narendra Umate on 1/7/16.
//
//

#include "Octree.h"

const int Octree::bucketSize = 1;
const int Octree::maxDepth = 8;

Octree::Octree(const int& depth, const BoundingBox& boundingBox)
: m_depth(depth)
, m_boundingBox(boundingBox) {
    for (int i = 0; i < 8; ++i) {
        m_children[i] = NULL;
    }
}

Octree::Octree(const int& depth, const Vec3& center, const Vec3 extent)
: m_depth(depth)
, m_boundingBox(center, extent) {
    for (int i = 0; i < 8; ++i) {
        m_children[i] = NULL;
    }
}

Octree::~Octree() {
    if (subtreesArePresent()) {
        for (int i = 0; i < 8; ++i) {
            delete m_children[i];
            m_children[i] = NULL;
        }
    }

    // Cleanup accepted spatials that still exist during abrupt termination
    for (std::list<Spatial*>::iterator it = m_acceptedSpatials.begin(); it != m_acceptedSpatials.end(); ++it) {
        delete (*it);
        *it = NULL;
    }
    m_acceptedSpatials.clear();

    // Cleanup rejected spatials that still exist during abrupt termination
    for (std::list<Spatial*>::iterator it = m_rejectedSpatials.begin(); it != m_rejectedSpatials.end(); ++it) {
        delete (*it);
        *it = NULL;
    }
    m_rejectedSpatials.clear();
}

bool Octree::insert(Spatial* spatial) {
    // Check if spatial fits in the tree
    if (!m_boundingBox.contains(spatial->getWorldBoundingBox())) {
        return false;
    }

    // TODO verify that this actually works
    // Fill here because of the depth limit
    if (m_depth >= maxDepth) {
        m_acceptedSpatials.push_back(spatial);
        return true;
    }

    // Fill here because of the bucket limit
    if (m_acceptedSpatials.size() < bucketSize) {
        m_acceptedSpatials.push_back(spatial);
        return true;
    }

    // Subdivide
    if (!subtreesArePresent()) {
        Vec3 middle = m_boundingBox.getCenter();
        Vec3 extent = m_boundingBox.getExtent() / 2.0f;
        m_children[NNN] = new Octree(m_depth + 1, Vec3(middle.x - extent.x, middle.y - extent.y, middle.z - extent.z), extent);
        m_children[NNP] = new Octree(m_depth + 1, Vec3(middle.x - extent.x, middle.y - extent.y, middle.z + extent.z), extent);
        m_children[NPN] = new Octree(m_depth + 1, Vec3(middle.x - extent.x, middle.y + extent.y, middle.z - extent.z), extent);
        m_children[NPP] = new Octree(m_depth + 1, Vec3(middle.x - extent.x, middle.y + extent.y, middle.z + extent.z), extent);
        m_children[PNN] = new Octree(m_depth + 1, Vec3(middle.x + extent.x, middle.y - extent.y, middle.z - extent.z), extent);
        m_children[PNP] = new Octree(m_depth + 1, Vec3(middle.x + extent.x, middle.y - extent.y, middle.z + extent.z), extent);
        m_children[PPN] = new Octree(m_depth + 1, Vec3(middle.x + extent.x, middle.y + extent.y, middle.z - extent.z), extent);
        m_children[PPP] = new Octree(m_depth + 1, Vec3(middle.x + extent.x, middle.y + extent.y, middle.z + extent.z), extent);
    }

    // Disperse
    if (!m_children[NNN]->insert(spatial)
        && !m_children[NNP]->insert(spatial)
        && !m_children[NPN]->insert(spatial)
        && !m_children[NPP]->insert(spatial)
        && !m_children[PNN]->insert(spatial)
        && !m_children[PNP]->insert(spatial)
        && !m_children[PPN]->insert(spatial)
        && !m_children[PPP]->insert(spatial)) {
        // No child accepted this but the spatial lies within boundary so must be moving between borders
        m_acceptedSpatials.push_back(spatial);
    }

    return true;
}

void Octree::update() {
    // A list of spatials that this update will update
    std::list<Spatial*> spatialsToUpdate;

    // A list of spatials that this update will distribute
    std::list<Spatial*> spatialsToDistribute;

    // Move all previously accepted spatials into this new list
    spatialsToUpdate.splice(spatialsToUpdate.end(), m_acceptedSpatials);

    // Update all children and move their rejected spatials into this new list
    if (subtreesArePresent()) {
        m_children[NNN]->update();
        m_children[NNP]->update();
        m_children[NPN]->update();
        m_children[NPP]->update();
        m_children[PNN]->update();
        m_children[PNP]->update();
        m_children[PPN]->update();
        m_children[PPP]->update();

        // Move all spatials rejected by children into this new list
        spatialsToDistribute.splice(spatialsToDistribute.end(), m_children[NNN]->m_rejectedSpatials);
        spatialsToDistribute.splice(spatialsToDistribute.end(), m_children[NNP]->m_rejectedSpatials);
        spatialsToDistribute.splice(spatialsToDistribute.end(), m_children[NPN]->m_rejectedSpatials);
        spatialsToDistribute.splice(spatialsToDistribute.end(), m_children[NPP]->m_rejectedSpatials);
        spatialsToDistribute.splice(spatialsToDistribute.end(), m_children[PNN]->m_rejectedSpatials);
        spatialsToDistribute.splice(spatialsToDistribute.end(), m_children[PNP]->m_rejectedSpatials);
        spatialsToDistribute.splice(spatialsToDistribute.end(), m_children[PPN]->m_rejectedSpatials);
        spatialsToDistribute.splice(spatialsToDistribute.end(), m_children[PPP]->m_rejectedSpatials);

        // Cull out the empty sub trees to reduce depth of recursion
        if (subtreesAreEmpty()) {
            delete m_children[NNN];
            delete m_children[NNP];
            delete m_children[NPN];
            delete m_children[NPP];
            delete m_children[PNN];
            delete m_children[PNP];
            delete m_children[PPN];
            delete m_children[PPP];
            m_children[NNN] = NULL;
            m_children[NNP] = NULL;
            m_children[NPN] = NULL;
            m_children[NPP] = NULL;
            m_children[PNN] = NULL;
            m_children[PNP] = NULL;
            m_children[PPN] = NULL;
            m_children[PPP] = NULL;
        }
    }

    // Run the update and distribute on the update list and classify it into accept and reject
    for (std::list<Spatial*>::iterator it = spatialsToUpdate.begin(); it != spatialsToUpdate.end(); ++it) {
        (*it)->update();
        if (!insert(*it)) {
            if (m_depth == 0) {
                delete (*it);
            } else {
                m_rejectedSpatials.push_back(*it);
            }
        }
    }

    // Run the distribute on the distribute list and classify it into accept and reject
    for (std::list<Spatial*>::iterator it = spatialsToDistribute.begin(); it != spatialsToDistribute.end(); ++it) {
        if (!insert(*it)) {
            if (m_depth == 0) {
                delete (*it);
            } else {
                m_rejectedSpatials.push_back(*it);
            }
        }
    }
}

std::list<Spatial*> Octree::collect() {
    std::list<Spatial*> allCollectedSpatials;
    std::list<Spatial*> childCollectedSpatials;
    if (subtreesArePresent()) {
        for (int i = 0; i < 8; ++i) {
            childCollectedSpatials = m_children[i]->collect();
            allCollectedSpatials.splice(allCollectedSpatials.end(), childCollectedSpatials);
        }
    }
    allCollectedSpatials.insert(allCollectedSpatials.end(), m_acceptedSpatials.begin(), m_acceptedSpatials.end());
    allCollectedSpatials.insert(allCollectedSpatials.end(), m_rejectedSpatials.begin(), m_rejectedSpatials.end());
    return allCollectedSpatials;
}

bool Octree::treeIsEmpty() {
    if (m_acceptedSpatials.size() == 0 && m_rejectedSpatials.size() == 0) {
        if (!subtreesArePresent()) {
            return true;
        } else {
            return (subtreesAreEmpty());
        }
    } else {
        return false;
    }
}

bool Octree::subtreesAreEmpty() {
    return (m_children[NNN]->treeIsEmpty()
            && m_children[NNP]->treeIsEmpty()
            && m_children[NPN]->treeIsEmpty()
            && m_children[NPP]->treeIsEmpty()
            && m_children[PNN]->treeIsEmpty()
            && m_children[PNP]->treeIsEmpty()
            && m_children[PPN]->treeIsEmpty()
            && m_children[PPP]->treeIsEmpty());
}

bool Octree::subtreesArePresent() {
    return (m_children[NNN] != NULL);
}
