//
//  Bound.h
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#ifndef TEST_Bound_H
#define TEST_Bound_H

#include <list>
#include "Math.h"
#include "Transform.h"
#include "Vector.h"
#include "VisualEffect.h"

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

    void create(const std::list<Bound3>& boxes);
    void create(const std::list<Vec3>& points);

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
