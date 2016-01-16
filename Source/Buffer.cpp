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
: m_count(0)
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
: Buffer()
, m_vertexData(NULL) {
}

VertexBuffer::~VertexBuffer() {
    if (m_vertexData) {
        delete m_vertexData;
    }
}

void VertexBuffer::bind() {
}

void VertexBuffer::unbind() {
}

void VertexBuffer::initialize(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texcoords) {
    m_count = (positions.size() / 3.0f) * 8.0f;
    m_size = m_count * sizeof(float);
    m_vertexData = new float[m_count];
    unsigned int vertexCount = positions.size() / 3.0f;
    for (unsigned int i = 0; i < vertexCount; ++i) {
        m_vertexData[i * 8 + 0] = positions.at(i * 3 + 0);
        m_vertexData[i * 8 + 1] = positions.at(i * 3 + 1);
        m_vertexData[i * 8 + 2] = positions.at(i * 3 + 2);
        m_vertexData[i * 8 + 3] = normals.at(i * 3 + 0);
        m_vertexData[i * 8 + 4] = normals.at(i * 3 + 1);
        m_vertexData[i * 8 + 5] = normals.at(i * 3 + 2);
        m_vertexData[i * 8 + 6] = texcoords.at(i * 2 + 0);
        m_vertexData[i * 8 + 7] = texcoords.at(i * 2 + 1);
    }
}

void VertexBuffer::deinitialize() {
    m_count = 0;
    m_size = 0;
    if (m_vertexData) {
        delete m_vertexData;
        m_vertexData = NULL;
    }
}
////////////////////////////////////////////////////////////////////////////////
IndexBuffer::IndexBuffer()
: Buffer()
, m_indexData(NULL) {
}

IndexBuffer::~IndexBuffer() {
    if (m_indexData) {
        delete m_indexData;
    }
}

void IndexBuffer::bind() {
}

void IndexBuffer::unbind() {
}

void IndexBuffer::initialize(const std::vector<unsigned int>& indices) {
    m_count = indices.size();
    m_size = m_count * sizeof(unsigned int);
    m_indexData = new unsigned int[m_count];
    for (unsigned int i = 0; i < m_count; ++i) {
        m_indexData[i] = indices.at(i);
    }
}

void IndexBuffer::deinitialize() {
    m_count = 0;
    m_size = 0;
    if (m_indexData) {
        delete m_indexData;
        m_indexData = NULL;
    }
}
