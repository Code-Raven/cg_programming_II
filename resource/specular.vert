#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 2) in vec3 vertNorm;

uniform mat4 MMatrix;
uniform mat4 MVPMatrix;
uniform vec3 objColor;			
uniform float glow;
uniform float lightCol;
uniform float objRefl;
uniform float objSpecRelf;


out vec3 vertColor;

void main(){
	vec3 emissive = objColor * glow;										
	vec3 ambient= objRelf * lightCol;										
	vec3 diffuse = objColor * lightCol * max(dot(normal, lightDir), 0);		
	vec3 specular = objSpecRefl * lightCol * facing * pow(max(dot(normal,half), 0),shininess);	

	vertCol = emmisive + ambient + diffuse + specular;

	//emissive = Ke
	//ambient = Ka x globalAmbient
	//diffuse = Kd x lightColor x max(N · L, 0)
	//specular = Ks x lightColor x facing x (max(N · H, 0)) shininess

	gl_Position = MVPMatrix * vec4(vertPos, 1);
}