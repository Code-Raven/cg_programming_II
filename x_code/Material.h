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
    Material();
    virtual void Render(RendData rendData) = 0;
    
    GLuint LoadBMP(const char * imagepath);
    
    virtual void SetProgId(GLuint progId);

    //TODO: boden, check to make sure this gets called…
    virtual ~Material(){}

protected:
    GLuint m_progId, m_textId;
    GLuint m_modelId, m_modelViewId, m_modelViewProjId;
    
    //camera.MVPMatrixID = glGetUniformLocation(activeProgramId, "MVP");
    //GLuint MMatrixId, MVMatrixId, MVPMatrixId;
    //mat4 projectionMatrix, viewMatrix;
};

class BasicMaterial : public Material {
    
public:
    virtual void Render(RendData rendData);
};

class ToonMaterial : public Material {
    
public:
    virtual void Render(RendData rendData);
};

class OutlineMaterial : public Material {

public:
    virtual void Render(RendData rendData);
};

#endif /* defined(__cg_programming_II__Material__) */
