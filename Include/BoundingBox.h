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

	inline Vec3 GetCenter() { return m_center; }
	inline Vec3 GetHalfDimension() const { return m_halfDimension; }
	inline Vec3 GetCornerMin() { return m_cornerMin; }
	inline Vec3 GetCornerMax() { return m_cornerMax; }

	void Update(const Vec3& center);
	void Update(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ);

	bool Contains(const Vec3& p) const;
	bool Contains(const BoundingBox& other) const;
	bool Intersects(const BoundingBox& other) const;

private:
	Vec3 m_center;
	Vec3 m_halfDimension;
	Vec3 m_cornerMin;
	Vec3 m_cornerMax;
};

#endif // TEST_BoundingBox_H
