//
//  DxRenderer.h
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Application__DxRenderer__
#define __Application__DxRenderer__

#if defined(_WIN32)

#include "Renderer.h"

//namespace Engine {

class DxRenderer : public Renderer {

public:
    DxRenderer(const int& width, const int& height);
    virtual ~DxRenderer();

    void initialize();
    void deinitialize();

    void setClearColor(const Color4f& clearColor);
    Color4f getClearColor() const;
    void setClearDepth(const float& clearDepth);
    float getClearDepth() const;
    void setClearStencil(const unsigned int& clearStencil);
    unsigned int getClearStencil() const;
    void setViewport(const int& xPos, const int& yPos, const int& w, const int& h);
    void getViewport(int& xPos, int& yPos, int& w, int& h) const;
    void setDepthRange(const float& zMin, const float& zMax);
    void getDepthRange(float& zMin, float& zMax) const;
    void setSize(const int& width, const int& height);
    void getSize(int& width, int& height);

    void clearColorBuffer();
    void clearDepthBuffer();
    void clearStencilBuffer();
    void clearBuffers();
    void clearColorBuffer(const int& x, const int& y, const int& w, const int& h);
    void clearDepthBuffer(const int& x, const int& y, const int& w, const int& h);
    void clearStencilBuffer(const int& x, const int& y, const int& w, const int& h);
    void clearBuffers(const int& x, const int& y, const int& w, const int& h);
    void displayColorBuffer(const int& syncInterval);
    void draw(Visual* visual);
    void draw(VertexBuffer* vBuffer, IndexBuffer* iBuffer, VisualEffect* vEffect);
};

//}

#endif // defined(_WIN32)

#endif /* defined(__Application__DxRenderer__) */
