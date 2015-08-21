#version 330 core //compatibility	//gl_ModelViewProjectionMatrix
// varying vec4 vColor;  declare both here and in frag shader to pass to frag shader...
// uniform vec3 model_space_pos; same if you were to call in vec3 model_space_pos;
// in - linkage into shader from previous stage
// out - linkage out of a shader to next stage
// attribute - same as in for vertex shader...
// varying - same as out for vertex shader...
// unform. just like varying/in, except value remains constant and can use in both fragment and vertex shader...
// http://stackoverflow.com/questions/21980947/replacement-for-gl-position-gl-modelviewprojectionmatrix-gl-vertex

/* GLSL Hacker automatic uniforms:
** uniform mat4 gxl3d_ModelViewProjectionMatrix;
** uniform mat4 gxl3d_ModelViewMatrix;
** uniform mat4 gxl3d_ProjectionMatrix;
** uniform mat4 gxl3d_ViewMatrix;
** uniform mat4 gxl3d_ModelMatrix;
*/

layout(location = 0) in vec3 vertPos;
layout(location = 2) in vec3 vertNorm;

uniform mat4 MMatrix;
uniform mat4 MVPMatrix;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

out vec3 vertColor;

void main(){
	vec3 lightDir = normalize(vec3(1, 1, 1));

	mat4 normalMatrix = transpose(inverse(MMatrix));
	vec3 normal = (normalMatrix * vec4(vertNorm, 0)).xyz;

	float NdotL = max(dot(normal, lightDir), 0.0);

	vertColor = NdotL * ambient;

	gl_Position = MVPMatrix * vec4(vertPos, 1);
}