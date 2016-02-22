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
#define GL_GLEXT_PROTOTYPES

#include <vector>

#if defined(__linux__)
#include <GL/gl.h> // sudo apt-get install mesa-common-dev mesa-utils freeglut3 freeglut3-dev
#include <GL/glx.h>
#elif defined(__APPLE__)
#include "SDL_opengl.h"
#endif //defined(__APPLE__)
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
class VertexBuffer : public Buffer {
public:
    VertexBuffer();
    virtual ~VertexBuffer();

    void bind();
    void unbind();
    void initialize(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texcoords);
    void deinitialize();

private:
    unsigned int m_vertexArray;
};
////////////////////////////////////////////////////////////////////////////////
class IndexBuffer : public Buffer {
public:
    IndexBuffer();
    virtual ~IndexBuffer();

    void bind();
    void unbind();
    void initialize(const std::vector<unsigned int>& indices);
    void deinitialize();
};
////////////////////////////////////////////////////////////////////////////////
class Texture {
public:
	Texture();
	virtual ~Texture() = 0;

	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	unsigned int m_texture;
};
////////////////////////////////////////////////////////////////////////////////
class Texture2D : public Texture {
public:
	Texture2D();
	virtual ~Texture2D();

	void bind();
	void unbind();
	void initialize();
	void deinitialize();
};
////////////////////////////////////////////////////////////////////////////////
#endif /* Buffer_h */
