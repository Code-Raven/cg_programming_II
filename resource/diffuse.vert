#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 2) in vec3 vertNorm;

uniform mat4 MMatrix;
uniform mat4 MVPMatrix;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

out vec3 vertColor;

void main(){
    float refCoefficient
    
	vec3 lightDir = normalize(vec3(1, 1, 1));

	mat4 normalMatrix = transpose(inverse(MMatrix));
	vec3 normal = normalize((normalMatrix * vec4(vertNorm, 0)).xyz);

	float NdotL = max(dot(normal, lightDir), 0.0);

    if(NdotL > 0.92){
        vertColor = specular;
    }
    else if(NdotL > 0.6){
        vertColor = diffuse;
    }
    else {
        vertColor = ambient;
    }

	gl_Position = MVPMatrix * vec4(vertPos, 1);
}