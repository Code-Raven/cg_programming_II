#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 2) in vec3 vertNorm;

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform vec3 objColor = vec3(0.7f, 0.5f, 0.8f);			
uniform float glow = 0.0f;
uniform vec3 lightCol = vec3(1.0f, 1.0f, 1.0f);
uniform float objRefl = 0.2f;
uniform float objSpecRefl = 0.3f;
uniform mat4 normMatrix;
uniform vec3 lightDir = vec3(1.0f, 0.0f, 0.0f);
uniform int shininess = 2;

out vec3 vertColor;

void main(){
	vec3 normal = normalize((normMatrix * vec4(vertNorm, 1)).xyz);
	//vec3 half = **left off here finish half vector: normalize(L + V)**
	vec3 nDotL = max(dot(normal, lightDir), 0);
	float facing = ((nDotL < 0.0f) ? 0 : 1);
	vec3 emissive = objColor * glow;										
	vec3 ambient= objRelf * lightCol;										
	vec3 diffuse = objColor * lightCol * nDotL;		
	vec3 specular = objSpecRefl * lightCol * facing * pow(max(dot(normal,half), 0),shininess);	

	vertCol = emissive + ambient + diffuse + specular;

	//emissive = Ke
	//ambient = Ka x globalAmbient
	//diffuse = Kd x lightColor x max(N · L, 0)
	//specular = Ks x lightColor x facing x (max(N · H, 0)) shininess

	gl_Position = MVPMatrix * vec4(vertPos, 1);
}