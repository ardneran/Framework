//
//  TextureManager.cpp
//  Application
//
//  Created by Narendra Umate on 5/4/14.
//
//

#include "TextureManager.h"

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
	for (std::map<std::string, Image*>::iterator it = m_pathImageMap.begin(); it != m_pathImageMap.end(); ++it)
	{
		delete it->second;
		it->second = NULL;
	}
}

Image* TextureManager::loadTexture(const std::string& path) {
	if (m_pathImageMap[path] == NULL)
	{
		Image* image = new Image(path);
		image->flipY();
		m_pathImageMap[path] = image;
	}
	return m_pathImageMap[path];
}
