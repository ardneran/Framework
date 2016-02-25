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
	for (std::map<std::string, Texture2D*>::iterator it = m_pathTextureMap.begin(); it != m_pathTextureMap.end(); ++it)
	{
		delete it->second;
		it->second = NULL;
	}
}

Texture2D* TextureManager::loadTexture(const std::string& path) {
	if (m_pathTextureMap[path] == NULL)
	{
        Image image(path);
        image.flipY();
        Texture2D* texture = new Texture2D();
        texture->initialize(image.getSizeX(), image.getSizeY(), image.getPixels());
		m_pathTextureMap[path] = texture;
	}
	return m_pathTextureMap[path];
}
