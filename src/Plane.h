#include "Application.h"
#include "Object.h"

#pragma once

class Plane : public Object{

	public:
		Plane(GLuint width, GLuint height);
		virtual ~Plane();

	private:
		void BuildTriangles(const GLuint& perRow, const GLuint& perColumn);
		void LoadTriangles(GLfloat *vertices, GLfloat *uvs);

	private:
		GLuint width, height;
};