//
//  BoundingBox.h
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#ifndef TEST_BoundingBox_H
#define TEST_BoundingBox_H

#include "Vector.h"

class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(const Vec3& center, const Vec3& halfDimension);
	BoundingBox(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ);
	virtual ~BoundingBox();

	inline Vec3 getCenter() { return m_center; }
	inline Vec3 getHalfDimension() const { return m_halfDimension; }
	inline Vec3 getCornerMin() { return m_cornerMin; }
	inline Vec3 getCornerMax() { return m_cornerMax; }

	void update(const Vec3& center);
	void update(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ);

	bool contains(const Vec3& p) const;
	bool contains(const BoundingBox& other) const;
	bool intersects(const BoundingBox& other) const;

private:
	Vec3 m_center;
	Vec3 m_halfDimension;
	Vec3 m_cornerMin;
	Vec3 m_cornerMax;
};

#endif // TEST_BoundingBox_H
