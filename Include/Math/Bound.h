//
//  Bound.h
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#ifndef TEST_Bound_H
#define TEST_Bound_H

#include <vector>
#include "Math.h"
#include "Transform.h"
#include "Vector.h"

// Bound2

class Bound2 {
public:
	Bound2();
	Bound2(const Vec2& center, const Vec2& extent);
	Bound2(const float& minX, const float& minY, const float& maxX, const float& maxY);
	virtual ~Bound2();

	inline Vec2 getCenter() const { return m_center; }
	inline Vec2 getExtent() const { return m_extent; }
	inline Vec2 getCornerMin() const { return m_cornerMin; }
	inline Vec2 getCornerMax() const { return m_cornerMax; }

	void updateCenter(const Vec2& center);
	void updateCenterExtent(const Vec2& center, const Vec2& extent);
	void updateMinMax(const float& minX, const float& minY, const float& maxX, const float& maxY);
	void updateMinMax(const Vec2& cornerMin, const Vec2& cornerMax);

	void create(const std::vector<Bound2>& boxes);
	void create(const std::vector<Vec2>& points);

	bool contains(const Vec2& p) const;
	bool contains(const Bound2& other) const;
	bool intersects(const Bound2& other) const;
	Bound2 transform(const Mat3& m) const;
	Bound2 transform(const Transform& t) const;

	bool operator==(const Bound2& other) const;
	bool operator!=(const Bound2& other) const;

private:
	Vec2 m_center;
	Vec2 m_extent;
	Vec2 m_cornerMin;
	Vec2 m_cornerMax;
};

// Bound3

class Bound3 {
public:
	Bound3();
	Bound3(const Vec3& center, const Vec3& extent);
	Bound3(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ);
	virtual ~Bound3();

	inline Vec3 getCenter() const { return m_center; }
	inline Vec3 getExtent() const { return m_extent; }
	inline Vec3 getCornerMin() const { return m_cornerMin; }
	inline Vec3 getCornerMax() const { return m_cornerMax; }

	void updateCenter(const Vec3& center);
	void updateCenterExtent(const Vec3& center, const Vec3& extent);
	void updateMinMax(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ);
	void updateMinMax(const Vec3& cornerMin, const Vec3& cornerMax);

	void create(const std::vector<Bound3>& boxes);
	void create(const std::vector<Vec3>& points);
	//void create(const std::vector<Vertex>& vertices);

	bool contains(const Vec3& p) const;
	bool contains(const Bound3& other) const;
	bool intersects(const Bound3& other) const;
	Bound3 transform(const Mat4& m) const;
	Bound3 transform(const Transform& t) const;

	bool operator==(const Bound3& other) const;
	bool operator!=(const Bound3& other) const;

private:
	Vec3 m_center;
	Vec3 m_extent;
	Vec3 m_cornerMin;
	Vec3 m_cornerMax;
};

#endif // TEST_Bound_H
