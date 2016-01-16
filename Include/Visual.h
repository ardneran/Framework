//
//  Visual.h
//  Framework
//
//  Created by Narendra Umate on 8/28/15.
//
//

#ifndef Visual_h
#define Visual_h

#include <string>
#include <vector>
#include "Camera.h"
#include "GlProgram.h"
#include "Spatial.h"
#include "Buffer.h"
#include "VisualEffect.h"

class Visual : public Spatial {
public:
    Visual();
    virtual ~Visual();

    void update();

    void setTranslate(const Vec3& translate);
    void setRotate(const Quat& rotate);
    void setScale(const Vec3& scale);

    void setViewMatrix(const Mat4& viewMatrix);
    void setViewProjectionMatrix(const Mat4& viewProjectionMatrix);

    void setName(const std::string& name);
    void setPositions(const std::vector<float>& positions);
    void setNormals(const std::vector<float>& normals);
    void setTextureCoordinates(const std::vector<float>& texcoords);
    void setIndices(const std::vector<unsigned int>& indices);
    void setMaterialIds(const std::vector<int>& materialIds);

    char* getName() { return m_name; }
    float* getPositions() { return m_positions; }
    float* getNormals() { return m_normals; }
    float* getTextureCoordinates() { return m_textureCoordinates; }
    unsigned int* getIndices() { return m_indices; }
    int* getMaterialIds() { return m_materialIds; }

    unsigned int getNameSize() { return m_nameSize; }
    unsigned int getPositionsSize() { return m_positionsSize; }
    unsigned int getNormalsSize() { return m_normalsSize; }
    unsigned int getTexcoordsSize() { return m_textureCoordinatesSize; }
    unsigned int getIndicesSize() { return m_indicesSize; }
    unsigned int getMaterialIdsSize() { return m_materialIdsSize; }

    Mat4 getNormMatrix() { return m_normMatrix; }
    Mat4 getWorldViewProjectionMatrix() { return m_worldViewProjectionMatrix; }

    void setVertexBuffer(VertexBuffer* vertexBuffer) { m_vertexBuffer = vertexBuffer; }
    void setIndexBuffer(IndexBuffer* indexBuffer) { m_indexBuffer = indexBuffer; }
    void setVisualEffect(VisualEffect* visualEffect) { m_visualEffect = visualEffect; }

    VertexBuffer* getVertexBuffer() { return m_vertexBuffer; }
    IndexBuffer* getIndexBuffer() { return m_indexBuffer; }
    VisualEffect* getVisualEffect() { return m_visualEffect; }

protected:
    void updateWorldBoundingBox();
    void updateWorldNormals();
    void updateWorldViewProjectionMatrix();

private:
    char* m_name;
    float* m_positions;
    float* m_normals;
    float* m_textureCoordinates;
    unsigned int* m_indices;
    int* m_materialIds;

    BoundingBox m_modelBoundingBox;
    std::vector<float> m_modelNormals;

    unsigned int m_nameSize;
    unsigned int m_positionsSize;
    unsigned int m_normalsSize;
    unsigned int m_textureCoordinatesSize;
    unsigned int m_indicesSize;
    unsigned int m_materialIdsSize;

    Mat4 m_viewMatrix;
    Mat4 m_normMatrix;
    Mat4 m_viewProjectionMatrix;
    Mat4 m_worldViewProjectionMatrix;

    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
    VisualEffect* m_visualEffect;
};

#endif /* Visual_h */
