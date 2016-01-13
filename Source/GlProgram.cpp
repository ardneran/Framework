//
//  GlProgram.cpp
//  Application
//
//  Created by Narendra Umate on 3/14/14.
//
//

#include "GlProgram.h"

//namespace Engine
//{

GlProgram::GlProgram(const std::string& vsfilename, const std::string& fsfilename) {
    GLuint program = glCreateProgram();
    GLuint vsindex = loadShader(vsfilename, GL_VERTEX_SHADER);
    GLuint fsindex = loadShader(fsfilename, GL_FRAGMENT_SHADER);
    glAttachShader(program, vsindex);
    glAttachShader(program, fsindex);
    glLinkProgram(program);
    GLint status = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint logLenth;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logLenth);
        GLchar* logString = new GLchar[logLenth + 1];
        glGetProgramInfoLog(program, logLenth, NULL, logString);
        std::cout << "Link Error: " << logString;
        delete[] logString;
    }
    glDetachShader(program, vsindex);
    glDeleteShader(vsindex);
    glDetachShader(program, fsindex);
    glDeleteShader(fsindex);
}

GlProgram::~GlProgram() {
    glDeleteProgram(m_program);
}

GLuint GlProgram::loadShader(const std::string& shaderFilename, const GLenum& shaderType) {
    std::string strFilename = Utils::findFilePath(shaderFilename);
    if (!strFilename.empty()) {
        char* shaderString = loadShaderSourceFile(strFilename.c_str());
        //std::cout << shaderString << std::endl;
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, const_cast<const GLchar**>(&shaderString), NULL);
        glCompileShader(shader);
        delete[] shaderString;
        GLint status = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            GLchar* logString = new GLchar[logLength + 1];
            glGetProgramInfoLog(shader, logLength, NULL, logString);

            fprintf(stderr, "Compile Error: %s\n%s", shaderFilename.c_str(), logString);
            delete[] logString;
        }
        return shader;
    } else {
        fprintf(stderr, "File Missing: %s\n", shaderFilename.c_str());
        return 0;
    }
}

// TODO return string instead of allocated char array
char* GlProgram::loadShaderSourceFile(const char* shaderSourceFile) {
    std::ifstream fin;
    long int fileSize = 0;
    char* buffer;

    // Open the shader source file
    fin.open(shaderSourceFile);

    // If it could not open the file then exit
    if (fin.fail() == true) {
        return 0;
    }

    // Find filesize
    fin.seekg(0, fin.end);
    fileSize = fin.tellg();

    // Place get pointer at the beginning
    fin.seekg(0, fin.beg);

    // Initialize the buffer to read the shader source file into
    // Not sure if I should add 1
    buffer = new char[fileSize];
    if (buffer == NULL) {
        fin.close();
        return 0;
    }

    // Read the shader text file into the buffer as a block
    fin.read(buffer, fileSize);

    // Close the file
    fin.close();

    // Null terminate the buffer
    // Don't know if this is needed
    buffer[fileSize] = '\0';

    return buffer;
}

//}
