#include "Application.h"

#pragma once

class Object{

    //Methods…
	public:
		Object();

		virtual ~Object();
		virtual void Update(const float& deltaTime);
		virtual void Render(const Camera& camera);

		void SetPosition(vec3 position);
		void SetScale(vec3 scale);

		vec3 GetPosition();
		float GetLeftX();
		float GetRightX();
		float GetTopY();
		float GetBottomY();

		void SaveObjectState(char *message = (char*)"Saved Object State");
		void LoadObjectState(char *message = (char*)"Loaded Object State");
		GLuint LoadBMP(const char * imagepath);

	protected:
		void BuildCube();
    
    //Members…
    protected:
		Object* objectState;
		vec3 position, scale;

	protected:
		float leftX, rightX, topY, bottomY;
		float rotSpeed, rotAngle;
		mat4 Render();
		GLuint textureID, uvID;
		GLuint numIndices, numUVs, vertexBufferID, renderMode;
};