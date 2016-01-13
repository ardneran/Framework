//
//  GlProgram.h
//  Application
//
//  Created by Narendra Umate on 3/14/14.
//
//

#ifndef __Application__GlProgram__
#define __Application__GlProgram__

#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#elif defined(__linux__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h> // sudo apt-get install mesa-common-dev mesa-utils freeglut3 freeglut3-dev
#include <GL/glx.h>
#endif // defined(__linux__)

#include <iostream>
#include <vector>

#include "Utils.h"

//namespace Engine
//{

class GlProgram {
public:
    GlProgram(const std::string& vs, const std::string& fs);
    virtual ~GlProgram();

    void set1i(const std::string& name, GLint v0) { glUniform1i(glGetUniformLocation(m_program, name.c_str()), v0); }
    void set1f(const std::string& name, GLfloat v0) { glUniform1f(glGetUniformLocation(m_program, name.c_str()), v0); }
    void set3iv(const std::string& name, GLsizei count, const GLint* value) { glUniform3iv(glGetUniformLocation(m_program, name.c_str()), count, value); }
    void set3fv(const std::string& name, GLsizei count, const GLfloat* value) { glUniform3fv(glGetUniformLocation(m_program, name.c_str()), count, value); }
    void setMatrix3fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) { glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), count, transpose, value); }
    void setMatrix4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) { glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), count, transpose, value); }

    void set1i(GLint location, GLint v0) { glUniform1i(location, v0); }
    void set1f(GLint location, GLfloat v0) { glUniform1f(location, v0); }
    void set3iv(GLint location, GLsizei count, const GLint* value) { glUniform3iv(location, count, value); }
    void set3fv(GLint location, GLsizei count, const GLfloat* value) { glUniform3fv(location, count, value); }
    void setMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { glUniformMatrix3fv(location, count, transpose, value); }
    void setMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { glUniformMatrix4fv(location, count, transpose, value); }

    GLint getProgram() { return m_program; }
    GLint getLocation(const GLchar* name) { return glGetUniformLocation(m_program, name); }

private:
    GLuint loadShader(const std::string& shaderFilename, const GLenum& shaderType);
    char* loadShaderSourceFile(const char* shaderSourceFile);

    GLuint m_program;
};

//}

#endif /* defined(__Application__GlProgram__) */
