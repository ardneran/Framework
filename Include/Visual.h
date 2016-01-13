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
#include "GlProgram.h"
#include "Spatial.h"

class Visual : public Spatial {
public:
    Visual();
    virtual ~Visual();

    void setName(const std::string& name);
    void setPositions(const std::vector<float>& positions);
    void setNormals(const std::vector<float>& normals);
    void setTextureCoordinates(const std::vector<float>& texcoords);
    void setIndices(const std::vector<unsigned int>& indices);
    void setMaterialIds(const std::vector<int>& materialIds);
    void setProgram(GlProgram* program);

    char* getName() { return m_name; }
    float* getPositions() { return m_positions; }
    float* getNormals() { return m_normals; }
    float* getTextureCoordinates() { return m_textureCoordinates; }
    unsigned int* getIndices() { return m_indices; }
    int* getMaterialIds() { return m_materialIds; }
    GlProgram* getProgram() { return m_program; }

    unsigned int getNameSize() { return m_nameSize; }
    unsigned int getPositionsSize() { return m_positionsSize; }
    unsigned int getNormalsSize() { return m_normalsSize; }
    unsigned int getTexcoordsSize() { return m_textureCoordinatesSize; }
    unsigned int getIndicesSize() { return m_indicesSize; }
    unsigned int getMaterialIdsSize() { return m_materialIdsSize; }

private:
    char* m_name;
    float* m_positions;
    float* m_normals;
    float* m_textureCoordinates;
    unsigned int* m_indices;
    int* m_materialIds;
    GlProgram* m_program;

    unsigned int m_nameSize;
    unsigned int m_positionsSize;
    unsigned int m_normalsSize;
    unsigned int m_textureCoordinatesSize;
    unsigned int m_indicesSize;
    unsigned int m_materialIdsSize;
};

#endif /* Visual_h */
