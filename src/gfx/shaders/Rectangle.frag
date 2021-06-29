#version 410 core

in vec3 ourColor;

out vec4 fragColor;

uniform vec4 changeColor;

void main() {
//    vec3 outColor = ourColor;
//
//    if (outColor != changeColor.rgb) {
//         outColor = changeColor.rgb;
//    }

    fragColor = vec4(changeColor, 1.0f);
}
