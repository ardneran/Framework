//
//  Transform.h
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#ifndef Framework_Transform_h
#define Framework_Transform_h

#include "Quaternion.h"
#include "Matrix.h"

//#define SUPPORT_INVERTED

class Transform {
public:
    Transform();
    Transform(const Vec3& translate, const Quat& rotate, const Vec3& scale);
    virtual ~Transform();

    void setStraightMatrix(const Mat4& matrix);
    Mat4 getStraightMatrix();
#if defined(SUPPORT_INVERTED)
    void setInvertedMatrix(const Mat4& matrix);
    Mat4 getInvertedMatrix();
#endif // defined(SUPPORT_INVERTED)
    void setTranslate(const Vec3& translate);
    Vec3 getTranslate();
    void setRotate(const Quat& rotate);
    Quat getRotate();
    void setScale(const Vec3& scale);
    Vec3 getScale();
    void setTranslateRotateScale(const Vec3& translate, const Quat& rotate, const Vec3& scale);
    void getTranslateRotateScale(Vec3& translate, Quat& rotate, Vec3& scale);

    Transform operator*(const Transform& other);
    Transform operator*=(const Transform& other);

private:
    void composeStraightMatrix();
    void decomposeStraightMatrix();

    Mat4 m_straightMatrix;
#if defined(SUPPORT_INVERTED)
    Mat4 m_invertedMatrix;
#endif // defined(SUPPORT_INVERTED)
    Vec3 m_translate;
    Quat m_rotate;
    Vec3 m_scale;
};

#endif
