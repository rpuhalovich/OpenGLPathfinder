#include "Shader.hpp"

Shader::Shader(const std::string& filename, ShaderType type) :
    type(type)
{
    if (type == ShaderType::vertex) {
        glc(id = glCreateShader(GL_VERTEX_SHADER));
    } else if (type == ShaderType::fragment) {
        glc(id = glCreateShader(GL_FRAGMENT_SHADER));
    }

    std::string temp = Shader::readShader(filename);
    const char* src = temp.c_str();

    glc(glShaderSource(id, 1, &src, NULL));
    glc(glCompileShader(id));

    // check for shader compile errors
    int success;
    char infoLog[512];
    glc(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if (!success) {
        glc(glGetShaderInfoLog(id, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

Shader::~Shader() {
    glc(glDeleteShader(id));
}

std::string Shader::readShader(const std::string& filename) {
    std::ifstream in(std::string(SHADER_DIR) + std::string(filename));
    if (!in) {
        std::cout << "Error reading file." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return s;
}
