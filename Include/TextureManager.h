//
//  TextureManager.h
//  Application
//
//  Created by Narendra Umate on 5/4/14.
//
//

#ifndef __Application__TextureManager__
#define __Application__TextureManager__

#include <map>
#include <string>
#include "Buffer.h"
#include "Image.h"

class TextureManager {
public:
	TextureManager();
	~TextureManager();

	Texture2D* loadTexture(const std::string& path);

private:
	std::map<std::string, Texture2D*> m_pathTextureMap;
};

#endif /* defined(__Application__TextureManager__) */
