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

layout(location = 0)
in vec3 model_space_pos;

uniform mat4 MVP;

void main(){
	gl_Position = MVP * vec4(model_space_pos, 1);
}