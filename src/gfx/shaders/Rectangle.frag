#version 410 core

out vec4 fragColor;

in vec3 ourColor;

void main() {
    fragColor = vec4(ourColor, 1.0f);
    //fragColor = vec4(1.0f);
}
