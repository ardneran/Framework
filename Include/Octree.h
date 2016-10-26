//
//  Octree.h
//  Framework
//
//  Created by Narendra Umate on 1/7/16.
//
//

#ifndef Octree_h
#define Octree_h

#include <list>
#include "Bound.h"
#include "Camera.h"
#include "Spatial.h"

class Octree {
public:
    Octree(const int& depth, const Bound3& boundingBox);
    Octree(const int& depth, const Vec3& center, const Vec3 extent);
    virtual ~Octree();

    bool insert(Spatial* spatial);
    void update();
	void collectTree(std::list<Spatial*>& collection, const Camera* camera);
	void collectNode(std::list<Spatial*>& collection, const Camera* camera);
	Bound3 boundingBox();
	Octree* node(const int& index);

private:
    enum OctreeChildren {
        NNN,
        NNP,
        NPN,
        NPP,
        PNN,
        PNP,
        PPN,
        PPP,
    };

    bool treeIsEmpty();
    bool subtreesAreEmpty();
    bool subtreesArePresent();

    int m_depth;
    Bound3 m_boundingBox;
    Octree* m_children[8];
    std::list<Spatial*> m_acceptedSpatials;
    std::list<Spatial*> m_rejectedSpatials;

    static const int bucketSize;
    static const int maxDepth;
};

#endif /* Octree_h */
