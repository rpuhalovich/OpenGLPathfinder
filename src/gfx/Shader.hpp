#pragma once

#include "glutil.hpp"
#include "util.hpp"

enum class ShaderType { vertex, fragment };

class Shader {
public:
    Shader(const std::string& filename, ShaderType type);
    ~Shader();

    static std::string readShader(const std::string& filename);

    unsigned int getId() { return id; }
private:
    unsigned int id;
    ShaderType type;
};
