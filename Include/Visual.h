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
#include "Spatial.h"

class Visual : public Spatial {
public:
    Visual();
    virtual ~Visual();

    void setName(const std::string& name);
    void setPositions(const std::vector<float>& positions);
    void setNormals(const std::vector<float>& normals);
    void setTexcoords(const std::vector<float>& texcoords);
    void setIndices(const std::vector<unsigned int>& indices);
    void setMaterialIds(const std::vector<int>& materialIds);

private:
    char* m_name;
    float* m_positions;
    float* m_normals;
    float* m_texcoords;
    unsigned int* m_indices;
    int* m_materialIds;

    unsigned int m_nameSize;
    unsigned int m_positionsSize;
    unsigned int m_normalsSize;
    unsigned int m_texcoordsSize;
    unsigned int m_indicesSize;
    unsigned int m_materialIdsSize;
};

#endif /* Visual_h */
