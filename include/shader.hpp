#pragma once
#include <glad/glad.h>
#include <string>

class Shader {
    public:
        unsigned int id;


        Shader(const char* vertPath, const char* fragPath);
        ~Shader();

        void use() const;

        void setBool (const std::string& name, bool value) const;
        void setInt  (const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;

    private:
        unsigned int compileShader(const char* path, GLenum type);
        void checkError(unsigned int obj, bool isProgram);
};
