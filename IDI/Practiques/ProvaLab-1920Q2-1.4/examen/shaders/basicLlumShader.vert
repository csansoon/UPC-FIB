#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

out vec3 vertexF;
out vec3 normalF;

out vec3 matambF;
out vec3 matdiffF;
out vec3 matspecF;
out float matshinF;

uniform vec3 posFocus;
out vec3 posFocusF;

void main()
{	
    vertexF = (view * TG * vec4(vertex, 1.0)).xyz;
	normalF = (inverse(transpose(mat3(view * TG)))) * normal;
    
    matambF     = matamb;
    matdiffF    = matdiff;
    matspecF    = matspec;
    matshinF    = matshin;
    
    posFocusF = vec3(view * vec4(posFocus, 1.0));
    
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
