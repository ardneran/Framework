//
//  Node.h
//  Framework
//
//  Created by Narendra Umate on 8/29/15.
//
//

#ifndef Node_h
#define Node_h

#include <vector>
#include "Spatial.h"

class Node : public Spatial {

public:
    Node();
    ~Node();

protected:
    virtual void updateWorldTransforms();
    virtual bool updateWorldBounds();

    std::vector<Spatial*> m_children;
};

#endif /* Node_h */
