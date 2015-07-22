#include "Application.h"
#include "Object.h"

#pragma once

class Plane : public Object{

	public:
		Plane(GLuint width, GLuint height);
		virtual ~Plane();

	private:
		void Plane::BuildTriangles(const GLuint& perRow, const GLuint& perColumn);
		void Plane::LoadTriangles(GLfloat *vertices, GLfloat *uvs);

	private:
		GLuint width, height;
};