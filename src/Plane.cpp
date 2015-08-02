#include "Plane.h"

Plane::Plane(GLuint width, GLuint height) : Object(){
	BuildTriangles(this->width = width, this->height = height);
}

Plane::~Plane(){
	
}

void Plane::BuildTriangles(const GLuint& perRow, const GLuint& perColumn){
	int numValuesPerRow = 18 * perRow;
	int numValues = 18 * perRow * perColumn;

	GLfloat *vertices = new GLfloat[numValues];
	for(int i = 0, x = 0, y = 0; i < numValues; ++x){
		vertices[i] = x + 0.0f;		vertices[++i] = y + 1.0f;	vertices[++i] = 0.0f;
		vertices[++i] = x + 0.0f;	vertices[++i] = y + 0.0f;	vertices[++i] = 0.0f;
		vertices[++i] = x + 1.0f;	vertices[++i] = y + 1.0f;	vertices[++i] = 0.0f;
		
		vertices[++i] = x + 1.0f;	vertices[++i] = y + 0.0f;	vertices[++i] = 0.0f;
		vertices[++i] = x + 1.0f;	vertices[++i] = y + 1.0f;	vertices[++i] = 0.0f;
		vertices[++i] = x + 0.0f;	vertices[++i] = y + 0.0f;	vertices[++i] = 0.0f;

		if(++i % numValuesPerRow == 0){
			x = -1; --y;
		}
	}

	int numUvValuesPerRow = 12 * perRow;
	int numUvValues = 12 * perRow * perColumn;

	GLfloat *uvs = new GLfloat[numUvValues];
	for(int i = 0, u = 0, v = 0; i < numUvValues; ++u){
		uvs[i] = u + 0.625f;		uvs[++i] = -v - 0.9166f;
		uvs[++i] = u + 0.625f;		uvs[++i] = -v - 1.0f;
		uvs[++i] = u + 0.6875f;		uvs[++i] = -v - 0.9166f;
		
		uvs[++i] = u + 0.6875f;		uvs[++i] = -v - 1.0f;
		uvs[++i] = u + 0.6875f;		uvs[++i] = -v - 0.9166f;
		uvs[++i] = u + 0.625f;		uvs[++i] = -v - 1.0f;

		if(++i % numUvValuesPerRow == 0){
			u = -1; ++v;
		}
	}	

	numUVs = numUvValues/2;
	numIndices = numValues/3;
	this->renderMode = GL_TRIANGLES;
	LoadTriangles(vertices, uvs);
}

void Plane::LoadTriangles(GLfloat *vertices, GLfloat *uvs){
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, numIndices * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &uvID);
	glBindBuffer(GL_ARRAY_BUFFER, uvID);
	glBufferData(GL_ARRAY_BUFFER, numUVs * 2 * sizeof(GLfloat), uvs, GL_STATIC_DRAW);
}