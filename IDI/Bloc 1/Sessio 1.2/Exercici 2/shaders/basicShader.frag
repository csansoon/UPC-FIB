#version 330 core

out vec4 FragColor;

uniform vec2 finestra;

void main() {

    if (gl_FragCoord.y < finestra.y/2) {        //DOWN:
        if (gl_FragCoord.x < finestra.x/2) { //LEFT:
        FragColor = vec4(1.0, 1.0, 0.0, 1);
        }
        else {                               //RIGHT:
        FragColor = vec4(0.0, 1.0, 0.0, 1);
        }
    }
    else {                                      //UP:
    if (gl_FragCoord.x < finestra.x/2) { //LEFT:
        FragColor = vec4(1.0, 0.0, 0.0, 1);
        }
        else {                               //RIGHT:
        FragColor = vec4(0.0, 0.0, 1.0, 1);
        }
    }
    
    
    if (int(gl_FragCoord.y) % 20 > 10) {
        discard;
    }

}

