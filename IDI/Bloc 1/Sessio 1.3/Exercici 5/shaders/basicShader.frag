#version 330 core

out vec4 FragColor;
in vec3 fcolor;

uniform float val;

void main() {
    FragColor = vec4(fcolor, 1);
}

