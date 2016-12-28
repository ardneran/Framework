//
//  Bound.cpp
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#include "Bound.h"

// Bound2

Bound2::Bound2()
: m_center(Vec2::zero)
, m_extent(Vec2::zero) {
}

Bound2::Bound2(const Vec2& center, const Vec2& extent)
: m_center(center)
, m_extent(extent) {
	m_cornerMin = center - extent;
	m_cornerMax = center + extent;
}

Bound2::Bound2(const float& minX, const float& minY, const float& maxX, const float& maxY) {
	m_cornerMin.x = minX;
	m_cornerMin.y = minY;
	m_cornerMax.x = maxX;
	m_cornerMax.y = maxY;
	m_center = (m_cornerMin + m_cornerMax) * 0.5f;
	m_extent = m_center - m_cornerMin;
}

Bound2::~Bound2() {
}

void Bound2::updateCenter(const Vec2& center) {
	m_center = center;
	m_cornerMin = center - m_extent;
	m_cornerMax = center + m_extent;
}

void Bound2::updateCenterExtent(const Vec2& center, const Vec2& extent) {
	m_center = center;
	m_extent = extent;
	m_cornerMin = center - extent;
	m_cornerMax = center + extent;
}

void Bound2::updateMinMax(const Vec2& cornerMin, const Vec2& cornerMax) {
	m_cornerMin = cornerMin;
	m_cornerMax = cornerMax;
	m_center = (m_cornerMin + m_cornerMax) * 0.5f;
	m_extent = m_center - m_cornerMin;
}

void Bound2::updateMinMax(const float& minX, const float& minY, const float& maxX, const float& maxY) {
	m_cornerMin.x = minX;
	m_cornerMin.y = minY;
	m_cornerMax.x = maxX;
	m_cornerMax.y = maxY;
	m_center = (m_cornerMin + m_cornerMax) * 0.5f;
	m_extent = m_center - m_cornerMin;
}

void Bound2::create(const std::list<Bound2>& boxes) {
	std::list<Vec2> points;
	for (std::list<Bound2>::const_iterator boxPointer = boxes.begin(); boxPointer != boxes.end(); ++boxPointer) {
		points.push_back(boxPointer->getCornerMin());
		points.push_back(boxPointer->getCornerMax());
	}
	create(points);
}

void Bound2::create(const std::list<Vec2>& points) {
	m_cornerMin = Vec2::max;
	m_cornerMax = Vec2::min;
	for (std::list<Vec2>::const_iterator pointPointer = points.begin(); pointPointer != points.end(); ++pointPointer) {
		if (pointPointer->x < m_cornerMin.x) {
			m_cornerMin.x = pointPointer->x;
		}

		if (pointPointer->x > m_cornerMax.x) {
			m_cornerMax.x = pointPointer->x;
		}

		if (pointPointer->y < m_cornerMin.y) {
			m_cornerMin.y = pointPointer->y;
		}

		if (pointPointer->y > m_cornerMax.y) {
			m_cornerMax.y = pointPointer->y;
		}
	}
	m_center = (m_cornerMin + m_cornerMax) * 0.5f;
	m_extent = m_center - m_cornerMin;
}

bool Bound2::contains(const Vec2& point) const {
	if (point.x > m_cornerMax.x) {
		return false;
	}

	if (point.x < m_cornerMin.x) {
		return false;
	}

	if (point.y > m_cornerMax.y) {
		return false;
	}

	if (point.y < m_cornerMin.y) {
		return false;
	}

	return true;
}

bool Bound2::contains(const Bound2& bound) const {
	return (contains(bound.m_cornerMin) && contains(bound.m_cornerMax));
}

bool Bound2::intersects(const Bound2& bound) const {
	// Calculate current and min non intersecting distance between centers.
	// If we are not intersecting at all then return (0, 0).
	Vec2 curDistance = m_center - bound.m_center;
	Vec2 minDistance = m_extent + bound.m_extent;
	return ((!(fabsf(curDistance.x) >= minDistance.x)) && (!(fabsf(curDistance.y) >= minDistance.y)));
}

bool Bound2::completelyInside(const Bound2& bound) const {
	return bound.contains(*this);
}

bool Bound2::completelyInside(const Frustum2& frustum) const {
	// TODO
	return true;
}

Bound2 Bound2::transform(const Mat3& m) const {
#if defined UNOPTIMIZED
	Bound boundingBox;
	Vec2 min = Vec2::max;
	Vec2 max = Vec2::min;
	for (unsigned int i = 0; i < 8; ++i) {
		Vec4 p4 = pointVector(m_center + entrywiseProduct(m_extent, getDirection(i))) * m;
		Vec2 p3 = Vec2(p4.x, p4.y, p4.z);
		min = minVec(min, p3);
		max = maxVec(max, p3);
	}
	boundingBox.updateMinMax(min, max);
	return boundingBox;
#else
	Bound2 boundingBox;
	Vec2 xa = m.Right() * m_cornerMin.x;
	Vec2 xb = m.Right() * m_cornerMax.x;
	Vec2 ya = m.Up() * m_cornerMin.y;
	Vec2 yb = m.Up() * m_cornerMax.y;
	Vec2 min = minVec(xa, xb) + minVec(ya, yb) + m.Translation();
	Vec2 max = maxVec(xa, xb) + maxVec(ya, yb) + m.Translation();
	boundingBox.updateMinMax(min, max);
	return boundingBox;
#endif
}

Bound2 Bound2::transform(const Transform& t) const {
	return transform(t);
}

bool Bound2::operator==(const Bound2& other) const {
	return (memcmp(this, &other, sizeof(Bound2)) == 0);
}

bool Bound2::operator!=(const Bound2& other) const {
	return (memcmp(this, &other, sizeof(Bound2)) != 0);
}

// Bound3

Bound3::Bound3()
: m_center(Vec3::zero)
, m_extent(Vec3::zero) {
}

Bound3::Bound3(const Vec3& center, const Vec3& extent)
: m_center(center)
, m_extent(extent) {
    m_cornerMin = center - extent;
    m_cornerMax = center + extent;
}

Bound3::Bound3(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ) {
    m_cornerMin.x = minX;
    m_cornerMin.y = minY;
    m_cornerMin.z = minZ;
    m_cornerMax.x = maxX;
    m_cornerMax.y = maxY;
    m_cornerMax.z = maxZ;
    m_center = (m_cornerMin + m_cornerMax) * 0.5f;
    m_extent = m_center - m_cornerMin;
}

Bound3::~Bound3() {
}

void Bound3::updateCenter(const Vec3& center) {
    m_center = center;
    m_cornerMin = center - m_extent;
    m_cornerMax = center + m_extent;
}

void Bound3::updateCenterExtent(const Vec3& center, const Vec3& extent) {
    m_center = center;
    m_extent = extent;
    m_cornerMin = center - extent;
    m_cornerMax = center + extent;
}

void Bound3::updateMinMax(const Vec3& cornerMin, const Vec3& cornerMax) {
    m_cornerMin = cornerMin;
    m_cornerMax = cornerMax;
    m_center = (m_cornerMin + m_cornerMax) * 0.5f;
    m_extent = m_center - m_cornerMin;
}

void Bound3::updateMinMax(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ) {
    m_cornerMin.x = minX;
    m_cornerMin.y = minY;
    m_cornerMin.z = minZ;
    m_cornerMax.x = maxX;
    m_cornerMax.y = maxY;
    m_cornerMax.z = maxZ;
    m_center = (m_cornerMin + m_cornerMax) * 0.5f;
    m_extent = m_center - m_cornerMin;
}

void Bound3::create(const std::vector<Bound3>& boxes) {
    std::vector<Vec3> points;
    for (std::vector<Bound3>::const_iterator boxPointer = boxes.begin(); boxPointer != boxes.end(); ++boxPointer) {
        points.push_back(boxPointer->getCornerMin());
        points.push_back(boxPointer->getCornerMax());
    }
    create(points);
}

void Bound3::create(const std::vector<Vec3>& points) {
    m_cornerMin = Vec3::max;
    m_cornerMax = Vec3::min;
    for (std::vector<Vec3>::const_iterator pointPointer = points.begin(); pointPointer != points.end(); ++pointPointer) {
        if (pointPointer->x < m_cornerMin.x) {
            m_cornerMin.x = pointPointer->x;
        }

        if (pointPointer->x > m_cornerMax.x) {
            m_cornerMax.x = pointPointer->x;
        }

        if (pointPointer->y < m_cornerMin.y) {
            m_cornerMin.y = pointPointer->y;
        }

        if (pointPointer->y > m_cornerMax.y) {
            m_cornerMax.y = pointPointer->y;
        }

        if (pointPointer->z < m_cornerMin.z) {
            m_cornerMin.z = pointPointer->z;
        }

        if (pointPointer->z > m_cornerMax.z) {
            m_cornerMax.z = pointPointer->z;
        }
    }
	m_center = (m_cornerMin + m_cornerMax) * 0.5f;
	m_extent = m_center - m_cornerMin;
}

/*void Bound3::create(const std::vector<Vertex>& vertices) {
	m_cornerMin = Vec3::max;
	m_cornerMax = Vec3::min;
	for (std::vector<Vertex>::const_iterator vertexPointer = vertices.begin(); vertexPointer != vertices.end(); ++vertexPointer) {
		if (vertexPointer->position.x < m_cornerMin.x) {
			m_cornerMin.x = vertexPointer->position.x;
		}

		if (vertexPointer->position.x > m_cornerMax.x) {
			m_cornerMax.x = vertexPointer->position.x;
		}

		if (vertexPointer->position.y < m_cornerMin.y) {
			m_cornerMin.y = vertexPointer->position.y;
		}

		if (vertexPointer->position.y > m_cornerMax.y) {
			m_cornerMax.y = vertexPointer->position.y;
		}

		if (vertexPointer->position.z < m_cornerMin.z) {
			m_cornerMin.z = vertexPointer->position.z;
		}

		if (vertexPointer->position.z > m_cornerMax.z) {
			m_cornerMax.z = vertexPointer->position.z;
		}
	}
	m_center = (m_cornerMin + m_cornerMax) * 0.5f;
	m_extent = m_center - m_cornerMin;
}*/

bool Bound3::contains(const Vec3& point) const {
    if (point.x > m_cornerMax.x) {
        return false;
    }

    if (point.x < m_cornerMin.x) {
        return false;
    }

    if (point.y > m_cornerMax.y) {
        return false;
    }

    if (point.y < m_cornerMin.y) {
        return false;
    }

    if (point.z > m_cornerMax.z) {
        return false;
    }

    if (point.z < m_cornerMin.z) {
        return false;
    }

    return true;
}

bool Bound3::contains(const Bound3& bound) const {
    return (contains(bound.m_cornerMin) && contains(bound.m_cornerMax));
}

bool Bound3::intersects(const Bound3& bound) const {
	// Calculate current and min non intersecting distance between centers.
	// If we are not intersecting at all then return (0, 0, 0).
	Vec3 curDistance = m_center - bound.m_center;
	Vec3 minDistance = m_extent + bound.m_extent;
	return ((!(fabsf(curDistance.x) >= minDistance.x)) && (!(fabsf(curDistance.y) >= minDistance.y)) && (!(fabsf(curDistance.z) >= minDistance.z)));
}

bool Bound3::completelyInside(const Bound3& bound) const {
	return bound.contains(*this);
}

bool Bound3::completelyInside(const Frustum3& frustum) const {
	return false; // TODO
}

Bound3 Bound3::transform(const Mat4& m) const {
//#define UNOPTIMIZED
#if defined UNOPTIMIZED
	Vec3 min = Vec3::max;
	Vec3 max = Vec3::min;
	for (unsigned int i = 0; i < 8; ++i) {
		// The order of multiplication below between matrix and vector is correct and verified.
		Vec4 p4 = m * pointVector(m_center + entrywiseProduct(m_extent, getDirection(i)));
		Vec3 p3 = Vec3(p4.x, p4.y, p4.z);
		min = minVec(min, p3);
		max = maxVec(max, p3);
	}
	Bound3 boundingBox;
    boundingBox.updateMinMax(min, max);
	return boundingBox;
#else
	Vec3 xa = m.Right() * m_cornerMin.x;
	Vec3 xb = m.Right() * m_cornerMax.x;
	Vec3 ya = m.Up() * m_cornerMin.y;
	Vec3 yb = m.Up() * m_cornerMax.y;
	Vec3 za = m.Forward() * m_cornerMin.z;
	Vec3 zb = m.Forward() * m_cornerMax.z;
	Vec3 min = minVec(xa, xb) + minVec(ya, yb) + minVec(za, zb) + m.Translation();
	Vec3 max = maxVec(xa, xb) + maxVec(ya, yb) + maxVec(za, zb) + m.Translation();
	Bound3 boundingBox;
	boundingBox.updateMinMax(min, max);
	return boundingBox;
#endif
//#undef UNOPTIMIZED
}

Bound3 Bound3::transform(const Transform& t) const {
	return transform(t.getMatrix());
}

bool Bound3::operator==(const Bound3& other) const {
	return (memcmp(this, &other, sizeof(Bound3)) == 0);
}

bool Bound3::operator!=(const Bound3& other) const {
	return (memcmp(this, &other, sizeof(Bound3)) != 0);
}
