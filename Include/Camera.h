//
//  Camera.h
//  Framework
//
//  Created by Narendra Umate on 11/29/15.
//
//

#ifndef Camera_h
#define Camera_h

#include "Matrix.h"
#include "Vector.h"

class Camera {
public:
	Camera();
	~Camera();

	void setFrame(const Vec3& position, const Vec3& right, const Vec3& up, const Vec3& front);
	void setPosition(const Vec3& position);
	void setAxes(const Vec3& right, const Vec3& up, const Vec3& front);
	void setFrustum(const float& upFovDegrees, const float& aspectRatio, const float& frontMin, const float& frontMax);
	void setFrustum(const float& rightMin, const float& rightMax, const float& upMin, const float& upMax, const float& frontMin, const float& frontMax);

	void getFrame(Vec3& position, Vec3& right, Vec3& up, Vec3& front);
	void getPosition(Vec3& position);
	void getAxes(Vec3& right, Vec3& up, Vec3& front);
	void getFrustum(float& upFovDegrees, float& aspectRatio, float& frontMin, float& frontMax);
	void getFrustum(float& rightMin, float& rightMax, float& upMin, float& upMax, float& frontMin, float& frontMax);

private:
	void onFrameChange();
	void onFrustumChange();
	void updateViewMatrix();
	void updateProjectionMatrix();
	void updateViewProjectionMatrix();

	Vec3 m_position;
	Vec3 m_right;
	Vec3 m_up;
	Vec3 m_front;

	float m_upFovDegrees;
	float m_aspectRatio;
	float m_rightMin;
	float m_rightMax;
	float m_upMin;
	float m_upMax;
	float m_frontMin;
	float m_frontMax;

	Mat4 m_preViewMatrix;
	Mat4 m_viewMatrix;
	Mat4 m_orthographicProjectionMatrix;
	Mat4 m_perspectiveProjectionMatrix;
	Mat4 m_viewOrthographicProjectionMatrix;
	Mat4 m_viewPerspectiveProjectionMatrix;
	Mat4 m_postProjectionMatrix;
};

#endif /* Camera_h */
