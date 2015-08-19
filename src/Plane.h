#include "Application.h"
#include "Object.h"

#pragma once

class Plane : public Object{

	public:
		Plane(){}
		Plane(GLuint width, GLuint height);
		virtual ~Plane();
    
    public:
        void SaveObjectState() override;
        void LoadObjectState() override;
        void Update(const float& deltaTime) override;
    
    public:
        float GetLeftX(){return mLeftX;}
        float GetRightX(){return mRightX;}
        float GetTopY(){return mTopY;}
        float GetBottomY(){return mBottomY;}

        void BuildTriangles(const GLuint& perRow, const GLuint& perColumn);

	private:
		void LoadTriangles(GLfloat *vertices, GLfloat *uvs);

	private:
        float mLeftX, mRightX, mTopY, mBottomY;
		GLuint mWidth, mHeight;
};