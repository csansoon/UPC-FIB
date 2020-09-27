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

// Valors per als components que necessitem dels focus de llum
vec3 llumAmbient = vec3(1.0, 1.0, 1.0);
uniform vec3 posFocus;
uniform vec3 colFocus;
uniform int llumEspasa;

//out vec3 fcolor;
out vec3 vertexF;
out vec3 normalF;

out vec3 matambF;
out vec3 matdiffF;
out vec3 matspecF;
out float matshinF;

out vec3 colFocusF;
out vec3 llumAmbientF;
out vec3 posFocusF;


void main()
{	
    vertexF = (view * TG * vec4(vertex, 1.0)).xyz;
	normalF = (inverse(transpose(mat3(view * TG)))) * normal;
    
    matambF     = matamb;
    matdiffF    = matdiff;
    matspecF    = matspec;
    matshinF    = matshin;
    
    colFocusF   = colFocus;
    llumAmbientF= llumAmbient;
    posFocusF   = posFocus;
    
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
