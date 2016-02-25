//
//  Buffer.cpp
//  Framework
//
//  Created by Narendra Umate on 1/15/16.
//
//

#include "Buffer.h"
////////////////////////////////////////////////////////////////////////////////
Buffer::Buffer()
: m_buffer(0)
, m_count(0)
, m_size(0) {
}

Buffer::~Buffer() {
}

unsigned int Buffer::getCount() {
    return m_count;
}

unsigned int Buffer::getSize() {
    return m_size;
}
////////////////////////////////////////////////////////////////////////////////
VertexBuffer::VertexBuffer()
: Buffer() {
    glGenVertexArrays(1, &m_vertexArray);
    glGenBuffers(1, &m_buffer);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_buffer);
    glDeleteVertexArrays(1, &m_vertexArray);
}

void VertexBuffer::bind() {
    glBindVertexArray(m_vertexArray);
    ////glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void VertexBuffer::unbind() {
    ////glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexBuffer::initialize(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texcoords) {
    m_count = (positions.size() / 3.0f) * 8.0f;
    m_size = m_count * sizeof(float);
    glBindVertexArray(m_vertexArray);
    //
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_size, NULL, GL_STATIC_DRAW);
    //
    void* m_bufferPointer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    float* m_vertexData = reinterpret_cast<float*>(m_bufferPointer);
    unsigned int vertexCount = positions.size() / 3.0f;
    bool fillNormals = normals.size() > 0;
    bool fillTexcoords = texcoords.size() > 0;
    for (unsigned int i = 0; i < vertexCount; ++i) {
        m_vertexData[i * 8 + 0] = positions.at(i * 3 + 0);
        m_vertexData[i * 8 + 1] = positions.at(i * 3 + 1);
        m_vertexData[i * 8 + 2] = positions.at(i * 3 + 2);
        m_vertexData[i * 8 + 3] = fillNormals ? normals.at(i * 3 + 0) : 0.0f;
        m_vertexData[i * 8 + 4] = fillNormals ? normals.at(i * 3 + 1) : 0.0f;
        m_vertexData[i * 8 + 5] = fillNormals ? normals.at(i * 3 + 2) : 0.0f;
        m_vertexData[i * 8 + 6] = fillTexcoords ? texcoords.at(i * 2 + 0) : 0.0f;
        m_vertexData[i * 8 + 7] = fillTexcoords ? texcoords.at(i * 2 + 1) : 0.0f;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    //
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(float) * 6));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
    glBindVertexArray(0);
}

void VertexBuffer::deinitialize() {
    m_count = 0;
    m_size = 0;
    glBindVertexArray(m_vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
////////////////////////////////////////////////////////////////////////////////
IndexBuffer::IndexBuffer()
: Buffer() {
    glGenBuffers(1, &m_buffer);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_buffer);
}

void IndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::initialize(const std::vector<unsigned int>& indices) {
    m_count = indices.size();
    m_size = m_count * sizeof(unsigned int);
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, NULL, GL_STATIC_DRAW);
    //
    void* m_bufferPointer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
    unsigned int* m_indexData = reinterpret_cast<unsigned int*>(m_bufferPointer);
    for (unsigned int i = 0; i < m_count; ++i) {
        m_indexData[i] = indices.at(i);
    }
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //
}

void IndexBuffer::deinitialize() {
    m_count = 0;
    m_size = 0;
}
////////////////////////////////////////////////////////////////////////////////
Texture2D::Texture2D() {
	glGenTextures(1, &m_texture);
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &m_texture);
}

void Texture2D::bind() {
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glEnable(GL_TEXTURE_2D);
}

void Texture2D::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void Texture2D::initialize(const int& width, const int& height, void* const data) {
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::deinitialize() {
	// TODO
}
////////////////////////////////////////////////////////////////////////////////
Material::Material() {
}

Material::~Material() {
}

void Material::enable() {
	glActiveTexture(GL_TEXTURE0);
	ambient_texname.bind();
	glActiveTexture(GL_TEXTURE1);
	diffuse_texname.bind();
	glActiveTexture(GL_TEXTURE2);
	specular_texname.bind();
	glActiveTexture(GL_TEXTURE3);
	specular_highlight_texname.bind();
	glActiveTexture(GL_TEXTURE4);
	bump_texname.bind();
	glActiveTexture(GL_TEXTURE5);
	displacement_texname.bind();
	glActiveTexture(GL_TEXTURE6);
	alpha_texname.bind();
	glActiveTexture(0);
}

void Material::disable() {
	glActiveTexture(GL_TEXTURE0);
	ambient_texname.unbind();
	glActiveTexture(GL_TEXTURE1);
	diffuse_texname.unbind();
	glActiveTexture(GL_TEXTURE2);
	specular_texname.unbind();
	glActiveTexture(GL_TEXTURE3);
	specular_highlight_texname.unbind();
	glActiveTexture(GL_TEXTURE4);
	bump_texname.unbind();
	glActiveTexture(GL_TEXTURE5);
	displacement_texname.unbind();
	glActiveTexture(GL_TEXTURE6);
	alpha_texname.unbind();
	glActiveTexture(0);
}

void Material::initialize() {
}

void Material::deinitialize() {
}
////////////////////////////////////////////////////////////////////////////////
