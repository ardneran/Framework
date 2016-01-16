//
//  Buffer.h
//  Framework
//
//  Created by Narendra Umate on 1/15/16.
//
//

#ifndef Buffer_h
#define Buffer_h

#include <vector>

class Buffer {
public:
    Buffer();
    virtual ~Buffer() = 0;

    unsigned int getCount();
    unsigned int getSize();

    virtual void bind() = 0;
    virtual void unbind() = 0;

protected:
    unsigned int m_count;
    unsigned int m_size;
};

class VertexBuffer : public Buffer {
public:
    VertexBuffer();
    virtual ~VertexBuffer();

    void bind();
    void unbind();
    void initialize(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texcoords);
    void deinitialize();

private:
    float* m_vertexData;
};

class IndexBuffer : public Buffer {
public:
    IndexBuffer();
    virtual ~IndexBuffer();

    void bind();
    void unbind();
    void initialize(const std::vector<unsigned int>& indices);
    void deinitialize();

private:
    unsigned int* m_indexData;
};

#endif /* Buffer_h */
