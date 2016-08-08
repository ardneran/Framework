//
//  Utils.cpp
//  Application
//
//  Created by Narendra Umate on 1/2/14.
//
//

#include "Utils.h"

//namespace Engine
//{

Utils::Utils() {
}

Utils::~Utils() {
}

bool Utils::fileExists(const std::string filepath) {
    std::ifstream testFile(filepath.c_str());
    if (testFile.is_open()) {
        testFile.close();
        return true;
    }
    return false;
}

// TODO Faster file check
std::string Utils::findFilePath(const std::string& strFileName) {
    std::string strFilePath = GLOBAL_MESHES_DIR + strFileName;
    if (fileExists(strFilePath)) {
        return strFilePath;
    }

    strFilePath = GLOBAL_SHADERS_DIR + strFileName;
    if (fileExists(strFilePath)) {
        return strFilePath;
    }

    strFilePath.empty();
    return strFilePath;
}

std::string Utils::findBasePath(const std::string& strFileName) {
    std::string strFilePath = findFilePath(strFileName);
    if (strFilePath.empty()) {
        return "";
    } else {
        unsigned found = strFilePath.find_last_of("/\\");
        return strFilePath.substr(0, found + 1); // base directory with ending /
        //return strFilePath.substr(found + 1);	// file name without starting /
    }
}

//}
