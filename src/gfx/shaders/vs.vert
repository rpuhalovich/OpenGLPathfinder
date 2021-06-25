#version 330 core

layout (location = 0) in vec3 ipos;

void main() {
    gl_Position = vec4(ipos.x, ipos.y, ipos.z, 1.0f);
}
