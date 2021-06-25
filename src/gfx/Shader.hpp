#pragma once

#include "glutil.hpp"
#include "util.hpp"

enum class ShaderType { vertex, fragment };

class Shader {
public:
    Shader(const char* filename, ShaderType type);
    ~Shader();

    static std::string readShader(const char* filename);
    void printShader();

    unsigned int getId() { return id; }
private:
    unsigned int id;
    ShaderType type;
    std::string shaderSource;
};