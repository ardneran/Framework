//
//  Buffer.h
//  Framework
//
//  Created by Narendra Umate on 1/15/16.
//
//

#ifndef Buffer_h
#define Buffer_h

#define BUFFER_OFFSET(offset) (void*)((char*)NULL + offset)
#define GL_GLEXT_PROTOTYPES 1
#include "SDL_opengl.h"

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
    unsigned int m_buffer;
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
};

class IndexBuffer : public Buffer {
public:
    IndexBuffer();
    virtual ~IndexBuffer();

    void bind();
    void unbind();
    void initialize(const std::vector<unsigned int>& indices);
    void deinitialize();
};

#endif /* Buffer_h */
