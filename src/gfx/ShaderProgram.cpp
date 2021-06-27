#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const std::string& vertname, const std::string& fragname) {
    Shader* vs = new Shader(vertname, ShaderType::vertex);
    Shader* fs = new Shader(fragname, ShaderType::fragment);

    // link shaders
    id = glCreateProgram();
    glAttachShader(id, vs->getId());
    glAttachShader(id, fs->getId());
    glLinkProgram(id);

    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    delete vs;
    delete fs;
}

ShaderProgram::~ShaderProgram() {
    glc(glDeleteProgram(id));
}

void ShaderProgram::use() {
    glc(glUseProgram(id));
}
