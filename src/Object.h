#include "Application.h"
#include "Material.h"

#pragma once

class Object{

    //Methods…
	public:
		Object();
		virtual ~Object();
    
        virtual void SaveObjectState() = 0;
        virtual void LoadObjectState() = 0;
    
		virtual void Update(const float& deltaTime);
		virtual void Render(const Camera& camera);
    
        void SetMaterial(Material* material);
		void SetPosition(vec3 position);
		void SetScale(vec3 scale);
        void Rotate(float rotAngle, vec3 rotAxis);
        void RotateOverTime(float rotSpeed, vec3 rotAxis);

		vec3 GetPosition();

	protected:
        void Copy(Object *source);
        void BeforeRender();
    
    //Members…
    protected:
        Material* m_material;
        mat4 m_modelMatrix;
		Object* m_savedObject;
		vec3 mPosition, mScale, mRotAxis;
		float mRotSpeed, mRotAngle;
		GLuint mVertexBufferID, mUvID, mNormID;
		GLuint mNumIndices, mNumUVs, mRenderMode;
};