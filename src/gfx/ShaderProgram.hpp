#pragma once

#include <glad/glad.h>
#include "glutil.hpp"
#include "Shader.hpp"
#include "Window.hpp"

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertname, const std::string& fragname, float winWidth, float winHeight);
    ~ShaderProgram();

    /**
     * \brief Uses the shader program (glc(glUseProgram(id));)
     */
    void use();

    /**
     * \brief Sets a matrix. 
     * \param type Should be either "model", "view" or "projection".
     */
    void setMat4Uniform4fv(const glm::mat4& mat, const std::string& type);
    void setMat4Uniform4iv(const glm::vec4& vec, const std::string& type);

    unsigned int getId() { return id; }
private:
    unsigned int id;
    float winWidth;
    float winHeight;
};
