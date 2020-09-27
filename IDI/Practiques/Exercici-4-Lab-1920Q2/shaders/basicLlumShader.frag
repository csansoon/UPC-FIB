#version 330 core

in vec3 fcolor;
out vec4 FragColor;

in vec3 vertexF;
in vec3 normalF;

in vec3 matambF;
in vec3 matdiffF;
in vec3 matspecF;
in float matshinF;

in vec3 colFocusF;
in vec3 llumAmbientF;
in vec3 posFocusF;

vec3 Lambert (vec3 NormSCO, vec3 L) 
{
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbientF * matambF;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + colFocusF * matdiffF * dot (L, NormSCO);
    return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO) 
{
    // Els vectors estan normalitzats

    // Inicialitzem color a Lambert
    vec3 colRes = Lambert (NormSCO, L);

    // Calculem R i V
    if (dot(NormSCO,L) < 0)
      return colRes;  // no hi ha component especular

    vec3 R = reflect(-L, NormSCO); // equival a: normalize (2.0*dot(NormSCO,L)*NormSCO - L);
    vec3 V = normalize(-vertSCO.xyz);

    if ((dot(R, V) < 0) || (matshinF == 0))
      return colRes;  // no hi ha component especular
    
    // Afegim la component especular
    float shine = pow(max(0.0, dot(R, V)), matshinF);
    return (colRes + matspecF * colFocusF * shine); 
}

void main()
{	
    vec3 L = normalize(posFocusF - vertexF.xyz);
    vec3 NM = normalize(normalF);
    vec3 color = Phong(NM, L, vec4(vertexF, 1));
    
	FragColor = vec4(color,1);	
}

