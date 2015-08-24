//
//  Spatial.h
//  Framework
//
//  Created by Narendra Umate on 8/23/15.
//
//

#ifndef Spatial_h
#define Spatial_h

#include "Transform.h"

class Spatial {
public:
	virtual ~Spatial();
	inline Spatial* getParent() { return m_parent; }
	inline void setParent(Spatial* const parent) { m_parent = parent; }
	void update(const bool& initiator = true);

	Transform m_localTransform;
	Transform m_worldTransform;

protected:
	// Abstract base class
	Spatial();

	virtual void updateWorldTransforms();
	virtual bool updateWorldBounds();
	void propagateWorldBoundsToParent();

private:
	Spatial* m_parent;
};

#endif /* Spatial_h */
