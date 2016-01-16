//
//  Buffer.cpp
//  Framework
//
//  Created by Narendra Umate on 1/15/16.
//
//

#include "Buffer.h"
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

void VertexBuffer::bind() {
}

void VertexBuffer::unbind() {
}

void IndexBuffer::bind() {
}

void IndexBuffer::unbind() {
}
