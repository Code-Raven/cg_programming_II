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
		vec3 cameraPos;
    };
    
    //TODO: boden, figure uot what to do with texture and shader later…
    Material(GLuint progId) : m_progId(progId), m_textId(0){}
    virtual ~Material(){}
    virtual void Render(RendData rendData) = 0;
    
    GLuint LoadBMP(const char * imagepath);

protected:
    GLuint m_progId, m_textId;
};

class SpecularMaterial : public Material {
    
public:
    SpecularMaterial(GLuint progId);
    virtual ~SpecularMaterial(){}
    virtual void Render(RendData rendData);
	GLuint m_modelViewId, m_modelViewProjId, m_normMatId;
    GLuint m_emissiveId, m_ambientId, m_diffuseId, m_specularId;
	GLuint m_lightPosId, m_viewPosId, m_objReflId, m_objSpecReflId, m_objShine;
};

class OutlineMaterial : public SpecularMaterial {
    
public:
    OutlineMaterial(GLuint progId, GLuint outlineId);
    virtual ~OutlineMaterial(){}
    virtual void Render(RendData rendData);
    GLuint m_outlineId, m_modelId, m_modelViewProjOutlineId;
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
