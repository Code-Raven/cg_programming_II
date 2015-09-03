#include "Object.h"

Object::Object() :
	m_savedObject(nullptr), m_material(nullptr),
	mRenderMode(GL_TRIANGLES), mVertexBufferID(0),
    mUvID(0), mNormID(0), mNumIndices(6), mPosition(0),
    mScale(1), mRotAxis(0, 1, 0), mNumUVs(0),
    mRotSpeed(0), mRotAngle(0)
{}

Object::~Object(){
    if(m_material != nullptr) { delete m_material; }
    if(m_savedObject != nullptr) { delete m_savedObject; }
    
    m_material = nullptr;
    m_savedObject = nullptr;
}

void Object::Copy(Object *source){
    //shallow copy…
    this->m_modelMatrix = source->m_modelMatrix;
    this->mPosition = source->mPosition;
    this->mScale = source->mScale;
    this->mRotAxis = source->mRotAxis;
    this->mRotSpeed = source->mRotSpeed;
    this->mRotAngle = source->mRotAngle;
    this->mVertexBufferID = source->mVertexBufferID;
    this->mUvID = source->mUvID;
    this->mNormID = source->mNormID;
    this->mNumIndices = source->mNumIndices;
    this->mNumUVs = source->mNumUVs;
    this->mRenderMode = source->mRenderMode;
    
    //For now we will just share materials…
    this->m_material = source->m_material;
}


void Object::SetMaterial(Material* material){
    m_material = material;
}

void Object::SetPosition(vec3 position){
	mPosition = position;
}

void Object::SetScale(vec3 scale){
	mScale = scale;
}

void Object::Rotate(float rotAngle, vec3 rotAxis){
    mRotAngle = rotAngle;
    mRotAxis = rotAxis;
}

void Object::RotateOverTime(float rotSpeed, vec3 rotAxis){
    mRotSpeed = rotSpeed;
    mRotAxis = rotAxis;
}

vec3 Object::GetPosition(){
	return mPosition;
}

void Object::Update(const float& deltaTime){
	mRotAngle += mRotSpeed * deltaTime;
}

void Object::Render(const Camera& camera){
    
    BeforeRender();
    
    typedef Material::RendData RendData;

	RendData data = {
		mRenderMode, 0,
        mNumIndices,
        m_modelMatrix,
        camera.viewMatrix,
        camera.projectionMatrix,
		camera.position
	};
    
    m_material->Render(data);
    
    //after render…
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Object::BeforeRender(){
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);

	//Setting up vertices...
	glVertexAttribPointer(
		0,			//attribute layout
		3,			//Elements in array
		GL_FLOAT,	//Each element is of type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array buffer offset...
	);

	if(mUvID > 0){
		//Setting up uvs...
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, mUvID);

		glVertexAttribPointer(
			1,			//attribute layout
			2,			//Elements in array
			GL_FLOAT,	//Each element is of type float
			GL_FALSE,	//Normalized?
			0,			//Stride...
			(void*)0	//Array buffer offset...
		);
	}

	if(mNormID > 0){
		//Setting up normals...
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, mNormID);

		glVertexAttribPointer(
			2,			//attribute layout
			3,			//Elements in array
			GL_FLOAT,	//Each element is of type float
			GL_FALSE,	//Normalized?
			0,			//Stride...
			(void*)0	//Array buffer offset...
		);
	}

	mat4 identityMatrix = mat4(1.0f);	//model in object space
	mat4 scaleMatrix = glm::scale(identityMatrix, mScale);

	mat4 translateMatrix = glm::translate(identityMatrix, mPosition);
	mat4 rotationMatrix = glm::rotate(identityMatrix, mRotAngle, mRotAxis);
    
	m_modelMatrix = translateMatrix * rotationMatrix * scaleMatrix * identityMatrix;
}