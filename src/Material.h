//
//  Material.h
//  cg_programming_II
//
//  Created by Branden Oden on 8/16/15.
//  Copyright (c) 2015 Branden Oden. All rights reserved.
//

#ifndef __cg_programming_II__Material__
#define __cg_programming_II__Material__

#include "Application.h"
//#include "Object.h"

class Material {

public:
    
    struct RendData {
        GLenum rendMode;
        GLint startIndex;
        GLuint numIndices;
        mat4 modelMatrix;
        mat4 viewMatrix;
        mat4 projMatrix;
    };
    
    //TODO: boden, figure uot what to do with texture and shader later…
    Material(GLuint progId) : m_progId(progId), m_textId(0){}
    virtual ~Material(){}
    virtual void Render(RendData rendData) = 0;
    
    GLuint LoadBMP(const char * imagepath);

protected:
    GLuint m_progId, m_textId;
};

class LitMaterial : public Material {
    
public:
    LitMaterial(GLuint progIds);
    virtual ~LitMaterial(){}
    virtual void Render(RendData rendData) = 0;
    GLuint m_modelViewProjId, m_modelId;
};

class AmbientMaterial : public LitMaterial {
    
public:
    AmbientMaterial(GLuint progId);
    virtual ~AmbientMaterial(){}
    virtual void Render(RendData rendData);
    GLuint m_ambientId;
};

class DiffuseMaterial : public AmbientMaterial {
    
public:
    DiffuseMaterial(GLuint progId);
    virtual ~DiffuseMaterial(){}
    virtual void Render(RendData rendData);
    GLuint m_diffuseId;
};
//TODO: Turn this into the basic lighting model later...
class SpecularMaterial : public DiffuseMaterial {
    
public:
    SpecularMaterial(GLuint progId);
    virtual ~SpecularMaterial(){}
    virtual void Render(RendData rendData);
    GLuint m_specularId;			//TODO: remove later...

	GLuint m_modelMatId;			//TODO: add in later...
	GLuint m_modelViewMatId;
	//GLuint m_modelViewProjMatId;	//TODO: add in later...
	GLuint m_normMatId;

	GLuint m_lightPosId;
	GLuint m_emissiveColorId;
	GLuint m_ambientColorId;
	GLuint m_lightColorId;
	GLuint m_objColorId;
	GLuint m_specColorId;
	GLuint m_objShineId;
	GLuint m_objReflectId;
};

class OutlineMaterial : public SpecularMaterial {
    
public:
    OutlineMaterial(GLuint progId, GLuint outlineId);
    virtual ~OutlineMaterial(){}
    virtual void Render(RendData rendData);
    GLuint m_outlineId, m_modelViewProjOutlineId;
};

class ToonOutlineMaterial : public OutlineMaterial {
    
public:
    ToonOutlineMaterial(GLuint progId, GLuint outlineId) : OutlineMaterial(progId, outlineId){}
    virtual ~ToonOutlineMaterial(){}
    virtual void Render(RendData rendData);
};

class ToonMaterial : public OutlineMaterial {
    
public:
    ToonMaterial(GLuint progId, GLuint outlineId) : OutlineMaterial(progId, outlineId){}
    virtual ~ToonMaterial(){}
    virtual void Render(RendData rendData);
};

#endif /* defined(__cg_programming_II__Material__) */
