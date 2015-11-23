//
//  Renderer.h
//  Framework
//
//  Created by Narendra Umate on 11/22/15.
//
//

#ifndef Renderer_h
#define Renderer_h

class Renderer
{
public:
	virtual ~Renderer();
	Renderer();
	void resize(const int& xSize, const int& ySize);
};

#endif /* Renderer_h */
