#version 330 core

layout(location = 0)
in vec3 model_space_pos;

uniform mat4 MVPMatrix;

void main(){
	gl_Position = MVPMatrix * vec4(model_space_pos, 1);
}