//
//  Shader.cpp
//  ogl
//
//  Created by logpoint on 8/9/20.
//

#include "Shader.h"

std::string Shader::loadShaderSrc(const char *filepath){
    std::ifstream file;
    std::stringstream buf;
    std::string ret = "";
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try{
        file.open(filepath);
        buf << file.rdbuf();
        ret= buf.str();
    }
    catch(std::ifstream::failure e){
           std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    file.close();
    return ret;
}

void Shader::generate(const char *vertexPath, const char *fragmentPath){
    int success;
    char infoLog[512];
    GLuint vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
    ID = glCreateProgram();
    glAttachShader(ID,vertexShader);
    glAttachShader(ID,fragShader);
    glLinkProgram(ID);
    
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if (!success){
        glad_glGetProgramInfoLog(ID,512,NULL,infoLog);
        std::cout << "ERROR: generate shader Program; status: Compile Failed"<< infoLog<<std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
    
    
}

GLuint Shader::compileShader(const char *filepath, GLuint type){
    int success;
    char infoLog[512];
    GLuint shader = glCreateShader(type);
    std::string shaderSrc = loadShaderSrc(filepath);
    const GLchar* shaderCode =shaderSrc.c_str();
    glShaderSource(shader,1,&shaderCode,NULL);
    glCompileShader(shader);
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success){
        glad_glGetShaderInfoLog(shader,512,NULL,infoLog);
        std::cout << "ERROR: compileShader; status: Compile Failed"<< infoLog<<std::endl;
    }
    return shader;
}


void  Shader::use(){
    glUseProgram(ID);
}
Shader::Shader(){
    
}
Shader::Shader(const char *vertexPath, const char *fragmentPath){
    generate(vertexPath, fragmentPath);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
