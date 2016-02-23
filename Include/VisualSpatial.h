//
//  VisualSpatial.h
//  Framework
//
//  Created by Narendra Umate on 8/28/15.
//
//

#ifndef VisualSpatial_h
#define VisualSpatial_h

#include <string>
#include <vector>
#include "Camera.h"
#include "GlProgram.h"
#include "Spatial.h"
#include "Buffer.h"
#include "VisualEffect.h"

class VisualSpatial : public Spatial {
public:
    VisualSpatial();
    virtual ~VisualSpatial();

    void update();

    void setTranslate(const Vec3& translate);
    void setRotate(const Quat& rotate);
    void setScale(const Vec3& scale);

    void setViewMatrix(const Mat4& viewMatrix);
    void setViewProjectionMatrix(const Mat4& viewProjectionMatrix);

    // TODO move definitions to cpp
    void setVertexBuffer(VertexBuffer* vertexBuffer) { m_vertexBuffer = vertexBuffer; }
    void setIndexBuffer(IndexBuffer* indexBuffer) { m_indexBuffer = indexBuffer; }
    void setVisualEffect(VisualEffect* VisualEffect) { m_visualEffect = VisualEffect; }
    void setModelBoundingBox(const std::vector<float>& positions) {
        Vec3 bbmin = Vec3::max;
        Vec3 bbmax = Vec3::min;
        unsigned int j = 0;
        unsigned int positionsCount = positions.size();
        for (j = 0; j < positionsCount;) {
            if (bbmin.x > positions[j]) {
                bbmin.x = positions[j];
            }
            if (bbmax.x < positions[j]) {
                bbmax.x = positions[j];
            }
            j++;
            if (bbmin.y > positions[j]) {
                bbmin.y = positions[j];
            }
            if (bbmax.y < positions[j]) {
                bbmax.y = positions[j];
            }
            j++;
            if (bbmin.z > positions[j]) {
                bbmin.z = positions[j];
            }
            if (bbmax.z < positions[j]) {
                bbmax.z = positions[j];
            }
            j++;
        }
        m_modelBoundingBox.updateMinMax(bbmin, bbmax);
        updateWorldBoundingBox();
    }

    Mat3& getWorldViewNormMatrix() { return m_worldViewNormMatrix; }
    Mat4& getWorldViewProjectionMatrix() { return m_worldViewProjectionMatrix; }

    VisualEffect* getVisualEffect() { return m_visualEffect; }
    VertexBuffer* getVertexBuffer() { return m_vertexBuffer; }
    IndexBuffer* getIndexBuffer() { return m_indexBuffer; }
	Material* getMaterial() { return m_material; }

    BoundingBox getModelBoudingBox() { return m_modelBoundingBox; }

protected:
    void updateWorldBoundingBox();
    void updateWorldViewNormMatrix();
    void updateWorldViewProjectionMatrix();

private:
	VisualEffect* m_visualEffect;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
	Material* m_material;

    BoundingBox m_modelBoundingBox;

    Mat3 m_worldViewNormMatrix;

    Mat4 m_viewMatrix;
    Mat4 m_viewProjectionMatrix;
    Mat4 m_worldViewProjectionMatrix;
};

#endif /* VisualSpatial_h */
