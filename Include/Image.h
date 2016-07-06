//
//  Image.h
//  Application
//
//  Created by Narendra Umate on 5/4/14.
//
//

#ifndef IMAGE
#define IMAGE

#include <iostream>
#include <vector>
using namespace std;

class Image
{
public:
	Image(const string& name);
	virtual ~Image();
	
	inline unsigned char* getPixels() { return m_pixels; } const
	inline int getSizeX() const { return m_sizeX; }
	inline int getSizeY() const { return m_sizeY; }	

	void flipY();
	
private:
	unsigned char* m_pixels;
	int m_sizeX;
	int m_sizeY;
	int m_channels;
	int m_count;
};

#endif // IMAGE
