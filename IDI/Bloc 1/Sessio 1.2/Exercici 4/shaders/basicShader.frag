#version 330 core

in vec3 fcolor;

out vec4 FragColor;

uniform vec2 finestra;
    //gl_FragCoord
    //FragColor = vec4();
void main() {
    FragColor = vec4(fcolor,0.5);
}

