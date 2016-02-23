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
#include "stb_image_helper.h"

class TextureManager {
public:
	TextureManager();
	~TextureManager();

	Image* loadTexture(const std::string& path);

private:
	std::map<std::string, Image*> m_pathImageMap;
};

#endif /* defined(__Application__TextureManager__) */
