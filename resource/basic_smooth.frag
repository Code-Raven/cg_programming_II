#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 2) in vec3 vertNorm;

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat4 normMatrix;

uniform vec3 objEmissive = vec3(0.0f, 0.0f, 0.0f);
uniform vec3 lightCol = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 objColor = vec3(0.7f, 0.5f, 0.8f);
uniform vec3 specLightCol = vec3(1.0f, 1.0f, 1.0f);

uniform vec3 lightPos = vec3(1.0f, 0.0f, 0.0f);
uniform vec3 viewPos = vec3(0.0f, 1.0f, 0.0f);

uniform float objRefl = 0.03f;
uniform float objSpecRefl = 1.0f;
uniform int objShine = 72;

in vec3 vertColor;
out vec3 color;

void main()
{
	//color = vertColor;

	vec3 normal = normalize((normMatrix * vec4(vertNorm, 1)).xyz);
	vec3 toView = normalize(viewPos - vertPos);
	vec3 toLight = normalize(lightPos);

	vec3 half = normalize(toLight + toView);
	float nDotL = max(dot(normal, toLight), 0);
	float facing = ((nDotL > 0.0f) ? 1 : 0);									
	vec3 ambient= objRefl * lightCol;										
	vec3 diffuse = objColor * lightCol * nDotL;		
	vec3 specular = objSpecRefl * specLightCol * facing *
		pow(max(dot(normal,half), 0), objShine);

	vertColor = objEmissive + ambient + diffuse + specular;
}