//
//  BoundingBox.cpp
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#include "BoundingBox.h"

VisualEffect* BoundingBox::visualEffect = nullptr;

BoundingBox::BoundingBox()
: m_center(Vec3::zero)
, m_extent(Vec3::zero) {
}

BoundingBox::BoundingBox(const Vec3& center, const Vec3& extent)
: m_center(center)
, m_extent(extent) {
    m_cornerMin = center - extent;
    m_cornerMax = center + extent;
}

BoundingBox::BoundingBox(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ) {
    m_cornerMin.x = minX;
    m_cornerMin.y = minY;
    m_cornerMin.z = minZ;
    m_cornerMax.x = maxX;
    m_cornerMax.y = maxY;
    m_cornerMax.z = maxZ;
    m_center = (m_cornerMin + m_cornerMax) * 0.5f;
    m_extent = m_center - m_cornerMin;
}

BoundingBox::~BoundingBox() {
}

void BoundingBox::updateCenter(const Vec3& center) {
    m_center = center;
    m_cornerMin = center - m_extent;
    m_cornerMax = center + m_extent;
}

void BoundingBox::updateCenterExtent(const Vec3& center, const Vec3& extent) {
    m_center = center;
    m_extent = extent;
    m_cornerMin = center - extent;
    m_cornerMax = center + extent;
}

void BoundingBox::updateMinMax(const Vec3& cornerMin, const Vec3& cornerMax) {
    m_cornerMin = cornerMin;
    m_cornerMax = cornerMax;
    m_center = (m_cornerMin + m_cornerMax) * 0.5f;
    m_extent = m_center - m_cornerMin;
}

void BoundingBox::updateMinMax(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ) {
    m_cornerMin.x = minX;
    m_cornerMin.y = minY;
    m_cornerMin.z = minZ;
    m_cornerMax.x = maxX;
    m_cornerMax.y = maxY;
    m_cornerMax.z = maxZ;
    m_center = (m_cornerMin + m_cornerMax) * 0.5f;
    m_extent = m_center - m_cornerMin;
}

void BoundingBox::create(const std::list<BoundingBox>& boxes) {
    std::list<Vec3> points;
    for (std::list<BoundingBox>::const_iterator boxPointer = boxes.begin(); boxPointer != boxes.end(); ++boxPointer) {
        points.push_back(boxPointer->getCornerMin());
        points.push_back(boxPointer->getCornerMax());
    }
    create(points);
}

void BoundingBox::create(const std::list<Vec3>& points) {
    Vec3 cornerMin = Vec3::max;
    Vec3 cornerMax = Vec3::min;
    for (std::list<Vec3>::const_iterator pointPointer = points.begin(); pointPointer != points.end(); ++pointPointer) {
        if (pointPointer->x < cornerMin.x) {
            cornerMin.x = pointPointer->x;
        }

        if (pointPointer->x > cornerMax.x) {
            cornerMax.x = pointPointer->x;
        }

        if (pointPointer->y < cornerMin.y) {
            cornerMin.y = pointPointer->y;
        }

        if (pointPointer->y > cornerMax.y) {
            cornerMax.y = pointPointer->y;
        }

        if (pointPointer->z < cornerMin.z) {
            cornerMin.z = pointPointer->z;
        }

        if (pointPointer->z > cornerMax.z) {
            cornerMax.z = pointPointer->z;
        }
    }
}

bool BoundingBox::contains(const Vec3& p) const {
    if (p.x > m_cornerMax.x) {
        return false;
    }

    if (p.x < m_cornerMin.x) {
        return false;
    }

    if (p.y > m_cornerMax.y) {
        return false;
    }

    if (p.y < m_cornerMin.y) {
        return false;
    }

    if (p.z > m_cornerMax.z) {
        return false;
    }

    if (p.z < m_cornerMin.z) {
        return false;
    }

    return true;
}

bool BoundingBox::contains(const BoundingBox& other) const {
    return (contains(other.m_cornerMin) && contains(other.m_cornerMax));
}

bool BoundingBox::intersects(const BoundingBox& other) const {
    // Calculate current and min non intersecting distance between centers.
    // If we are not intersecting at all then return (0, 0).
    Vec3 curDistance = m_center - other.m_center;
    Vec3 minDistance = m_extent + other.m_extent;
    return ((!(fabsf(curDistance.x) >= minDistance.x)) && (!(fabsf(curDistance.y) >= minDistance.y)) && (!(fabsf(curDistance.z) >= minDistance.z)));
}

BoundingBox BoundingBox::transform(const Mat4& m) const {
    BoundingBox boundingBox;
    boundingBox.updateMinMax(m_cornerMin * m, m_cornerMax * m);
    return boundingBox;
}

BoundingBox BoundingBox::transform(const Transform& t) const {
	return transform(t.getMatrix());
}

bool BoundingBox::operator==(const BoundingBox& other) const {
    return (m_center == other.m_center && m_extent == other.m_extent);
}

bool BoundingBox::operator!=(const BoundingBox& other) const {
    return (m_center != other.m_center || m_extent != other.m_extent);
}
