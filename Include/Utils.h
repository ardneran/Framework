//
//  Utils.h
//  Application
//
//  Created by Narendra Umate on 1/2/14.
//
//

#ifndef __Application__Utils__
#define __Application__Utils__

#include <iostream>
#include <fstream>
#include <string>

#if defined(__APPLE__)
#define GLOBAL_MESHES_DIR "/Users/ardneran/Documents/Projects/GitHub/Framework/Meshes/"
#define GLOBAL_SHADERS_DIR "/Users/ardneran/Documents/Projects/GitHub/Framework/Shaders/"
#elif defined(__linux__)
#define GLOBAL_MESHES_DIR "/home/numate/GitHub/Framework/Meshes/"
#define GLOBAL_SHADERS_DIR "/home/numate/GitHub/Framework/Shaders/"
#elif defined(_WIN32)
#define GLOBAL_MESHES_DIR "/Meshes/" //TODO
#define GLOBAL_SHADERS_DIR "/Shaders/" //TODO
#endif //defined(_WIN32)

//namespace Engine
//{

class Utils {
public:
    Utils();
    virtual ~Utils();

    static bool fileExists(const std::string filepath);
    static std::string findFilePath(const std::string& strFileName);
    static std::string findBasePath(const std::string& strFileName);
};

//}

#endif /* defined(__Application__Utils__) */
