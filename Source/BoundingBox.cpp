//
//  BoundingBox.cpp
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#include "BoundingBox.h"

BoundingBox::BoundingBox()
{ }

BoundingBox::BoundingBox(const Vec3& center, const Vec3& halfDimension)
	: m_center(center)
	, m_halfDimension(halfDimension)
{
	m_cornerMin = center - halfDimension;
	m_cornerMax = center + halfDimension;
}

BoundingBox::BoundingBox(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ)
	: m_cornerMin(minX, minY, minZ)
	, m_cornerMax(maxX, maxY, maxZ)
{
	m_center.x = (minX + maxX) / 2.0f;
	m_center.y = (minY + maxY) / 2.0f;
	m_center.z = (minZ + maxZ) / 2.0f;
	m_halfDimension.x = maxX - m_center.x;
	m_halfDimension.y = maxY - m_center.y;
	m_halfDimension.z = maxZ - m_center.z;
}

BoundingBox::~BoundingBox()
{ }

void BoundingBox::Update(const Vec3& center)
{
	m_center = center;
	m_cornerMin.x = center.x - m_halfDimension.x;
	m_cornerMin.y = center.y - m_halfDimension.y;
	m_cornerMin.z = center.z - m_halfDimension.z;
	m_cornerMax.x = center.x + m_halfDimension.x;
	m_cornerMax.y = center.y + m_halfDimension.y;
	m_cornerMax.z = center.z + m_halfDimension.z;
}

void BoundingBox::Update(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ)
{
	m_cornerMin.x = minX;
	m_cornerMin.y = minY;
	m_cornerMin.z = minZ;
	m_cornerMax.x = maxX;
	m_cornerMax.y = maxY;
	m_cornerMax.z = maxZ;
	m_center.x = (minX + maxX) * 0.5f;
	m_center.y = (minY + maxY) * 0.5f;
	m_center.z = (minZ + maxZ) * 0.5f;
	m_halfDimension.x = fabsf(maxX - m_center.x);
	m_halfDimension.y = fabsf(maxY - m_center.y);
	m_halfDimension.z = fabsf(maxZ - m_center.z);
}

bool BoundingBox::Contains(const Vec3& p) const
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

bool BoundingBox::Contains(const BoundingBox& other) const
{
	return (Contains(other.m_cornerMin) && Contains(other.m_cornerMax));
}

bool BoundingBox::Intersects(const BoundingBox& other) const
{
	// Calculate current and minimum-non-intersecting distances between centers.
	float distanceX = m_center.x - other.m_center.x;
	float distanceY = m_center.y - other.m_center.y;
	float distanceZ = m_center.z - other.m_center.z;

	float minDistanceX = m_halfDimension.x + other.m_halfDimension.x;
	float minDistanceY = m_halfDimension.y + other.m_halfDimension.y;
	float minDistanceZ = m_halfDimension.z + other.m_halfDimension.z;

	// If we are not intersecting at all, return (0, 0).
	if (fabsf(distanceX) >= minDistanceX || fabsf(distanceY) >= minDistanceY || fabsf(distanceZ) >= minDistanceZ)
	{
		return false;
	}

	return true;
}
