#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;



uniform int SCO;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

uniform vec3 posFocus;


out vec3 vertexF;
out vec3 normalF;

out vec3 matambF;
out vec3 matdiffF;
out vec3 matspecF;
out float matshinF;
out vec3 posFocusF;

//out vec3 fcolor;

void main()
{	
    if (SCO == 0) posFocusF = (view * vec4(posFocus, 1.0)).xyz; // Relatiu a l'escena
    //else posFocusF = posFocus;                                  // Relatiu a la càmera
    else posFocusF = vec3(0,0,0);                                  // Relatiu a la càmera

	// Passar posicio del vertex a SCO
	vertexF = (view * TG * vec4(vertex, 1.0)).xyz;
	
	// Passar vector normal a SCO
	mat3 NormalMatrix = (inverse(transpose(mat3(view * TG))));
	normalF = NormalMatrix * normal;
	
	matambF = matamb;
	matdiffF = matdiff;
	matspecF = matspec;
	matshinF = matshin;
	
	//fcolor = colFocus;
	gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
