//
//  Buffer.h
//  Framework
//
//  Created by Narendra Umate on 1/15/16.
//
//

#ifndef Buffer_h
#define Buffer_h

class Buffer {
public:
    Buffer();
    virtual ~Buffer() = 0;

    unsigned int getCount();
    unsigned int getSize();

    virtual void bind() = 0;
    virtual void unbind() = 0;

private:
    unsigned int m_count;
    unsigned int m_size;
};

class VertexBuffer : public Buffer {
public:
    void bind();
    void unbind();
};

class IndexBuffer : public Buffer {
public:
    void bind();
    void unbind();
};

#endif /* Buffer_h */
