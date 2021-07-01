#version 410 core

out vec4 fragColor;

uniform vec4 changeColor;

void main() {
    fragColor = changeColor;
}
