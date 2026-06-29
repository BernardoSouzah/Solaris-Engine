#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>


Shader::Shader(const char* vertPath, const char* fragPath) {
    unsigned int vert = compileShader(vertPath, GL_VERTEX_SHADER);
    unsigned int frag = compileShader(fragPath, GL_FRAGMENT_SHADER);

    id = glCreateProgram();
    glAttachShader(id, vert);
    glAttachShader(id, frag);
    glLinkProgram(id);
    checkError(id, true);

    glDeleteShader(vert);
    glDeleteShader(frag);

}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() const {
    glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

unsigned int Shader::compileShader(const char* path, GLenum type) {

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Shader: not found file" << path << std::endl;
        return 0;
    }
    std::stringstream ss;
    ss << file.rdbuf();
    std::string src = ss.str();
    const char* srcPtr = src.c_str();

    //compile
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &srcPtr, nullptr);
    glCompileShader(shader);
    checkError(shader, false);

    return shader;
}

void Shader::checkError(unsigned int obj, bool isProgram) {
    int success;
    char log[512];
    if (isProgram) {
        glGetProgramiv(obj, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(obj, 512, nullptr, log);
            std::cerr << "Shader link error: " << log << std::endl;
        }
    }else {
        glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
        if (!success) {
             glGetShaderInfoLog(obj, 512, nullptr, log);
             std::cerr << "Shader compile error: " << log << std::endl;
        }
    }
}
