#version 330 core

//https://en.wikibooks.org/wiki/GLSL_Programming/GLUT/Multiple_Lights
//https://developer.valvesoftware.com/wiki/Constant-Linear-Quadratic_Falloff
//TODO: point lights...
//TODO: attenuation...
//TODO: spot lights
//TODO: per pixel lighting...
//TODO: multiple lights in scene...

//TODO: next week, Introduction to antialiasing and texture mipmapping
//Last week, sun and moon scene. show off projects...


//TODO: normal vectors and positions are interpolated for each fragment,
//		and the lighting is computed in the fragment shader

layout(location = 0) in vec3 vertPos;	//keep
layout(location = 2) in vec3 vertNorm;	//keep

uniform mat4 MVPMatrix;		//keep
uniform mat4 normMatrix;	//keep

out vec3 position;
out vec3 normal;	//keep

void main(){
	normal = normalize((normMatrix * vec4(vertNorm, 1)).xyz);
	gl_Position = MVPMatrix * vec4(vertPos, 1);
}