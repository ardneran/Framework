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

void TextureManager::loadTexture(const std::string& path) {
	if (m_pathImageMap[path] == NULL)
	{
		m_pathImageMap[path] = new Image(path);
		m_pathImageMap[path]->flipY();
	}
}

int TextureManager::getSizeX(const std::string& path) {
	return m_pathImageMap[path]->getSizeX();
}

int TextureManager::getSizeY(const std::string& path) {
	return m_pathImageMap[path]->getSizeY();
}

void* TextureManager::getPixels(const std::string& path) {
	return &(m_pathImageMap[path]->getPixels()[0]);
}
