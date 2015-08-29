//
//  BoundingBox.cpp
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#include "BoundingBox.h"

BoundingBox::BoundingBox()
:	m_center(Vec3::zero)
,	m_extent(Vec3::zero)
{ }

BoundingBox::BoundingBox(const Vec3& center, const Vec3& extent)
:	m_center(center)
,	m_extent(extent)
{
	m_cornerMin = center - extent;
	m_cornerMax = center + extent;
}

BoundingBox::BoundingBox(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ)
:	m_cornerMin(minX, minY, minZ)
,	m_cornerMax(maxX, maxY, maxZ)
{
	m_center = (m_cornerMin + m_cornerMax) * 0.5f;
	m_extent = (m_center - m_cornerMin).abs();
}

BoundingBox::~BoundingBox()
{ }

void BoundingBox::update(const Vec3& center)
{
	m_center = center;
	m_cornerMin = center - m_extent;
	m_cornerMax = center + m_extent;
}

void BoundingBox::update(const Vec3& center, const Vec3& extent)
{
	m_center = center;
	m_extent = extent;
	m_cornerMin = center - extent;
	m_cornerMax = center + extent;
}
void BoundingBox::update(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ)
{
	m_cornerMin.x = minX;
	m_cornerMin.y = minY;
	m_cornerMin.z = minZ;
	m_cornerMax.x = maxX;
	m_cornerMax.y = maxY;
	m_cornerMax.z = maxZ;
	m_center = (m_cornerMin + m_cornerMax) * 0.5f;
	m_extent = (m_center - m_cornerMin).abs();
}

bool BoundingBox::contains(const Vec3& p) const
{
	if (p.x > m_cornerMax.x)
	{
		return false;
	}

	if (p.x < m_cornerMin.x)
	{
		return false;
	}

	if (p.y > m_cornerMax.y)
	{
		return false;
	}

	if (p.y < m_cornerMin.y)
	{
		return false;
	}

	if (p.z > m_cornerMax.z)
	{
		return false;
	}

	if (p.z < m_cornerMin.z)
	{
		return false;
	}

	return true;
}

bool BoundingBox::contains(const BoundingBox& other) const
{
	return (contains(other.m_cornerMin) && contains(other.m_cornerMax));
}

bool BoundingBox::intersects(const BoundingBox& other) const
{
	// Calculate current and minimum-non-intersecting distances between centers.
	float distanceX = m_center.x - other.m_center.x;
	float distanceY = m_center.y - other.m_center.y;
	float distanceZ = m_center.z - other.m_center.z;

	float minDistanceX = m_extent.x + other.m_extent.x;
	float minDistanceY = m_extent.y + other.m_extent.y;
	float minDistanceZ = m_extent.z + other.m_extent.z;

	// If we are not intersecting at all, return (0, 0).
	if (fabsf(distanceX) >= minDistanceX || fabsf(distanceY) >= minDistanceY || fabsf(distanceZ) >= minDistanceZ)
	{
		return false;
	}

	return true;
}

bool BoundingBox::operator==(const BoundingBox& other) const
{
	return (m_center == other.m_center && m_extent == other.m_extent);
}

bool BoundingBox::operator!=(const BoundingBox& other) const
{
	return (m_center != other.m_center || m_extent != other.m_extent);
}
