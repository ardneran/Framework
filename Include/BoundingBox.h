//
//  BoundingBox.h
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#ifndef TEST_BoundingBox_H
#define TEST_BoundingBox_H

#include <list>
#include "Vector.h"

class BoundingBox {
public:
    BoundingBox();
    BoundingBox(const Vec3& center, const Vec3& extent);
    BoundingBox(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ);
    virtual ~BoundingBox();

    inline Vec3 getCenter() const { return m_center; }
    inline Vec3 getExtent() const { return m_extent; }
    inline Vec3 getCornerMin() const { return m_cornerMin; }
    inline Vec3 getCornerMax() const { return m_cornerMax; }

    void updateCenter(const Vec3& center);
    void updateCenterExtent(const Vec3& center, const Vec3& extent);
    void updateMinMax(const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ);
    void updateMinMax(const Vec3& cornerMin, const Vec3& cornerMax);

    void create(const std::list<BoundingBox>& boxes);
    void create(const std::list<Vec3>& points);

    bool contains(const Vec3& p) const;
    bool contains(const BoundingBox& other) const;
    bool intersects(const BoundingBox& other) const;
    BoundingBox transform(const Mat4& m) const;

    bool operator==(const BoundingBox& other) const;
    bool operator!=(const BoundingBox& other) const;

private:
    Vec3 m_center;
    Vec3 m_extent;
    Vec3 m_cornerMin;
    Vec3 m_cornerMax;
};

#endif // TEST_BoundingBox_H
