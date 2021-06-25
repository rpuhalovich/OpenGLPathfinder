#include "Shader.hpp"

Shader::Shader(const char* filename, ShaderType type) {
     shaderSource = readShader(filename);

    if (type == ShaderType::vertex) {
        glc(id = glCreateShader(GL_VERTEX_SHADER));
    } else if (type == ShaderType::fragment) {
        glc(id = glCreateShader(GL_FRAGMENT_SHADER));
    }

    const char* src = shaderSource.c_str();
    glc(glShaderSource(id, 1, &src, NULL));
    glc(glCompileShader(id));

    int success;
    char infoLog[512];
    glc(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if (!success) {
        glc(glGetShaderInfoLog(id, 512, NULL, infoLog));
        std::cout << "Error: shader compilation failed.\n" << infoLog << std::endl;
    }
}

Shader::~Shader() {
    glc(glDeleteShader(id));
}

std::string Shader::readShader(const char* filename) {
    std::ifstream in (std::string(SHADER_DIR) + std::string(filename));
    if (!in) errorExit("Error reading shader file.", EXIT_FAILURE);
    std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return s;
}

void Shader::printShader() {
    std::cout << this->shaderSource << std::endl;
}
