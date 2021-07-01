#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const std::string& vertname, const std::string& fragname, float winWidth, float winHeight) {
    Shader* vs = new Shader(vertname, ShaderType::vertex);
    Shader* fs = new Shader(fragname, ShaderType::fragment);

    // link shaders
    id = glCreateProgram();
    glAttachShader(id, vs->getId());
    glAttachShader(id, fs->getId());
    glLinkProgram(id);

    delete vs;
    delete fs;

    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    setMat4Uniform4fv(glm::mat4(1.0f), std::string("model"));
    setMat4Uniform4fv(glm::mat4(1.0f), std::string("view"));
    setMat4Uniform4fv(glm::ortho(0.0f, winWidth, 0.0f, winHeight, -1.0f, 1.0f), std::string("projection"));
}

ShaderProgram::~ShaderProgram() {
    glc(glDeleteProgram(id));
}

void ShaderProgram::use() {
    glc(glUseProgram(id));
}

void ShaderProgram::setMat4Uniform4fv(const glm::mat4& mat, const std::string& type) {
    // TODO: https://www.youtube.com/watch?v=nBB0LGSIm5Q&t=23s

    use();
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = mat;
    glc(unsigned int uniformLoc = glGetUniformLocation(id, type.c_str()));
    glc(glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(matrix)));
}

void ShaderProgram::setMat4Uniform4iv(const glm::vec4& vec, const std::string& type) {
    use();
    glm::vec4 vector = glm::vec4(1.0f);
    vector = vec;
    glc(unsigned int uniformLoc = glGetUniformLocation(id, type.c_str()));
    glc(glUniform4fv(uniformLoc, 1, glm::value_ptr(vector)));
}
