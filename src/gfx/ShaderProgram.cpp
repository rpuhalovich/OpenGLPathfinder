#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const char* vertname, const char* fragname) {
    Shader* vertex = new Shader(vertname, ShaderType::vertex);
    Shader* fragment = new Shader(fragname, ShaderType::fragment);

    glc(glEnable(GL_DEPTH_TEST));

    glc(id = glCreateProgram());
    glc(glAttachShader(id, vertex->getId()));
    glc(glAttachShader(id, fragment->getId()));
    glc(glLinkProgram(id));

    int success;
    char infoLog[512];
    glc(glGetProgramiv(id, GL_LINK_STATUS, &success));
    if (!success) {
        glc(glGetShaderInfoLog(id, 512, NULL, infoLog));
        std::cout << "Error: shader program compilation failed.\n" << infoLog << std::endl;
    }

    // printSource(vertex, fragment);

    delete vertex;
    delete fragment;
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::use() {
    glc(glUseProgram(id));
}

void ShaderProgram::printSource(Shader* vertex, Shader* fragment) {
    vertex->printShader();
    fragment->printShader();
}
