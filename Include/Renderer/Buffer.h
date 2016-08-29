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
    VertexBuffer(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texcoords);
    virtual ~VertexBuffer();

    void bind();
    void unbind();
    void initialize();
    void deinitialize();

private:
    unsigned int m_vertexArray;
	std::vector<float> m_positions;
	std::vector<float> m_normals;
	std::vector<float> m_texcoords;
};
////////////////////////////////////////////////////////////////////////////////
class IndexBuffer : public Buffer {
public:
    IndexBuffer(const std::vector<unsigned int>& indices);
    virtual ~IndexBuffer();

    void bind();
    void unbind();
    void initialize();
    void deinitialize();

private:
	std::vector<unsigned int> m_indices;
};
////////////////////////////////////////////////////////////////////////////////
class Texture2D {
public:
	Texture2D();
	virtual ~Texture2D();

	void bind();
	void unbind();
	void initialize(const int& width, const int& height, void* const data);
	void deinitialize();

private:
	unsigned int m_texture;
};
////////////////////////////////////////////////////////////////////////////////
class Material {
public:
	Material();
	virtual ~Material();

	void enable();
	void disable();

	void initialize();
	void deinitialize();

public:
	////std::string name;
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float transmittance[3];
	float emission[3];
	float shininess;
	float ior;      // index of refraction
	float dissolve; // 1 == opaque; 0 == fully transparent
	int illum; 	// illumination model (see http://www.fileformat.info/format/material/)
	int dummy; // Supress padding warning.

	Texture2D* ambient_texname;            // map_Ka
	Texture2D* diffuse_texname;            // map_Kd
	Texture2D* specular_texname;           // map_Ks
	Texture2D* specular_highlight_texname; // map_Ns
	Texture2D* bump_texname;               // map_bump, bump
	Texture2D* displacement_texname;       // disp
	Texture2D* alpha_texname;              // map_d
	////std::map<std::string, std::string> unknown_parameter;
};
////////////////////////////////////////////////////////////////////////////////
#endif /* Buffer_h */
