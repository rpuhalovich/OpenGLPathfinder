#version 410 core

layout (location = 0) in vec3 ipos;
layout (location = 1) in vec3 icolor;

out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(ipos, 1.0f);
    ourColor = icolor;
}
