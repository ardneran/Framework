//
//  MetalRenderer.h
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Application__MetalRenderer__
#define __Application__MetalRenderer__

#if defined(__APPLE__)

#include "Renderer.h"

//namespace Engine {

class MetalRenderer : public Renderer {

public:
    MetalRenderer(const int& width, const int& height);
    virtual ~MetalRenderer();

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
    void draw(VisualSpatial* visual);
	void draw(BoundingBox* boundingBox);
};

//}

#endif // defined(__APPLE__)

#endif /* defined(__Application__MetalRenderer__) */
