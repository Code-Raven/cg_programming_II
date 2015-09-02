#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 2) in vec3 vertNorm;

uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 MVPMatrix;
uniform mat4 normMatrix;

uniform vec3 lightPos = vec3(1, 0, 0);	
uniform vec3 emissiveColor = vec3(0, 0, 0);	
uniform vec3 ambientColor = vec3(1, 1, 1);	
uniform vec3 lightColor = vec3(1, 1, 1);	
uniform vec3 objColor = vec3(1, 1, 1);	
uniform vec3 specColor = vec3(1, 1, 1);	

uniform float objShine = 1.0f;
uniform float objReflect = 1.0f;

out vec3 vertColor;

void main(){
	vec3 lightDir = normalize(lightPos - vertPos);
	vec3 eyeDir = -normalize((modelViewMatrix * vec4(vertPos, 1)).xyz);

	vec3 normal = normalize((normMatrix * vec4(vertNorm, 1)).xyz);
	float NdotL = max(dot(normal, lightDir), 0.0);

	vec3 half = normalize(eyeDir + lightDir);
	int facing = NdotL > 0 ? 1 : 0;

	vec3 emissive = emissiveColor;										
	vec3 ambient= objReflect * ambientColor;										
	vec3 diffuse = objColor * lightColor * NdotL;	
	vec3 specular = specColor * lightColor * facing * pow(max(dot(normal,half), 0), objShine);	

	vertColor = emissive + ambient + diffuse + specular;
	gl_Position = MVPMatrix * vec4(vertPos, 1);
}