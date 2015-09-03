//
//  Material.cpp
//  cg_programming_II
//
//  Created by Branden Oden on 8/16/15.
//  Copyright (c) 2015 Branden Oden. All rights reserved.
//

#include "Material.h"

/*** ToonMaterial ***/

void ToonMaterial::Render(RendData rendData){
    
    if(m_textId > 0){   //Only if we loaded a texture…
        glBindTexture(GL_TEXTURE_2D, m_textId);
    }
    
    //Push the GL attribute bits so that we don't wreck any settings
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    //Enable polygon offsets, and offset filled polygons forward by 2.5
    glEnable( GL_POLYGON_OFFSET_FILL );
    glPolygonOffset( -30.0f, -30.0f );	//TODO: read up on this later...
    
    glCullFace(GL_BACK);
    glUseProgram(m_outlineId);
    
    mat4 modelMatrix = rendData.modelMatrix;
    mat4 MVPMatrix = rendData.projMatrix * rendData.viewMatrix * modelMatrix;
    glUniformMatrix4fv(m_modelViewProjId, 1, GL_FALSE, &MVPMatrix[0][0]);
	glUniformMatrix4fv(m_modelId, 1, GL_FALSE, &modelMatrix[0][0]);
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glLineWidth(10.0f);
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
    
    glUseProgram(m_progId);
	glUniformMatrix4fv(m_modelViewProjOutlineId, 1, GL_FALSE, &MVPMatrix[0][0]);
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
    
    glPopAttrib();
}

/*** StencilOutlineMaterial ***/

void ToonOutlineMaterial::Render(RendData rendData){
    
    if(m_textId > 0){   //Only if we loaded a texture…
        glBindTexture(GL_TEXTURE_2D, m_textId);
    }
    
    glCullFace(GL_BACK);
    glUseProgram(m_progId);
    
    mat4 modelMatrix = rendData.modelMatrix;
	mat4 MVMatrix = rendData.viewMatrix * modelMatrix;
    mat4 MVPMatrix = rendData.projMatrix * MVMatrix;
    glUniformMatrix4fv(m_modelViewProjId, 1, GL_FALSE, &MVPMatrix[0][0]);
    glUniformMatrix4fv(m_modelId, 1, GL_FALSE, &modelMatrix[0][0]);

    vec3 ambientColor = vec3(0.1, 0, 0.2);
    vec3 diffuseColor = vec3(0.3f, 0.03f, 0.4f);
    vec3 specularColor = vec3(0.9f, 0.7f, 0.9f);
    glUniform3f(m_ambientId, ambientColor.x, ambientColor.y, ambientColor.z);
    glUniform3f(m_diffuseId, diffuseColor.x, diffuseColor.y, diffuseColor.z);
    glUniform3f(m_specularId, specularColor.x, specularColor.y, specularColor.z);
    
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);
    
    // Render the mesh into the stencil buffer.
    
    glEnable(GL_STENCIL_TEST);
    
    glStencilFunc(GL_ALWAYS, 1, -1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
    
    // Render the thick wireframe version.
    
    glUseProgram(m_outlineId);
    
    glUniformMatrix4fv(m_modelViewProjOutlineId, 1, GL_FALSE, &MVPMatrix[0][0]);
    
    glStencilFunc(GL_NOTEQUAL, 1, -1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    glLineWidth(10);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
}

/*** OutlineMaterial ***/

OutlineMaterial::OutlineMaterial(GLuint progId, GLuint outlineId) : SpecularMaterial(progId)
{
    m_modelViewProjOutlineId = glGetUniformLocation(outlineId, "MVPMatrix");
    m_outlineId = outlineId;
}

void OutlineMaterial::Render(RendData rendData){
    
    if(m_textId > 0){   //Only if we loaded a texture…
        glBindTexture(GL_TEXTURE_2D, m_textId);
    }
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    
    glUseProgram(m_progId);
    
    mat4 modelMatrix = rendData.modelMatrix;
    mat4 MVPMatrix = rendData.projMatrix * rendData.viewMatrix * modelMatrix;
    glUniformMatrix4fv(m_modelViewProjId, 1, GL_FALSE, &MVPMatrix[0][0]);
    glUniformMatrix4fv(m_modelId, 1, GL_FALSE, &modelMatrix[0][0]);
    
    // Render the mesh into the stencil buffer.
    
    glCullFace(GL_BACK);
    
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
    
    // Render the thick wireframe version.
    
    glUseProgram(m_outlineId);
    
    mat4 scaleMatrix = glm::scale(MVPMatrix, vec3(1.1f));
    glUniformMatrix4fv(m_modelViewProjOutlineId, 1, GL_FALSE, &scaleMatrix[0][0]);
    
    glCullFace(GL_FRONT);
    
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
}

/*** AmbientMaterial ***/

AmbientMaterial::AmbientMaterial(GLuint progId) : LitMaterial(progId) {
    m_ambientId = glGetUniformLocation(progId, "ambient");
}

void AmbientMaterial::Render(RendData rendData){

    if(m_textId > 0){   //Only if we loaded a texture…
        glBindTexture(GL_TEXTURE_2D, m_textId);
    }

    glCullFace(GL_BACK);
    glUseProgram(m_progId);

    mat4 MVPMatrix = rendData.projMatrix * rendData.viewMatrix * rendData.modelMatrix;

    glUniformMatrix4fv(m_modelViewProjId, 1, GL_FALSE, &MVPMatrix[0][0]);
    
    vec3 ambientColor = vec3(1, 0, 0);
    glUniform3fv(m_ambientId, 3, &ambientColor.x);

    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
}

/*** DiffuseMaterial ***/

DiffuseMaterial::DiffuseMaterial(GLuint progId) : AmbientMaterial(progId) {
    m_diffuseId = glGetUniformLocation(progId, "diffuse");
}

void DiffuseMaterial::Render(RendData rendData){
    
    if(m_textId > 0){   //Only if we loaded a texture…
        glBindTexture(GL_TEXTURE_2D, m_textId);
    }
    
    glCullFace(GL_BACK);
    glUseProgram(m_progId);
    
    mat4 MVPMatrix = rendData.projMatrix * rendData.viewMatrix * rendData.modelMatrix;
    
    glUniformMatrix4fv(m_modelViewProjId, 1, GL_FALSE, &MVPMatrix[0][0]);
    
    vec3 ambientColor = vec3(1, 0, 0);
    vec3 diffuseColor = vec3(0.5f, 0.5f, 0.5f);
    glUniform3fv(m_ambientId, 3, &ambientColor.x);
    glUniform3fv(m_diffuseId, 3, &diffuseColor.x);
    
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
}

/*** SpecularMaterial ***/

SpecularMaterial::SpecularMaterial(GLuint progId) : DiffuseMaterial(progId) {
    m_specularId = glGetUniformLocation(progId, "specular");
	m_modelViewId = glGetUniformLocation(progId, "MVMatrix");
    m_normMatId = glGetUniformLocation(progId, "normMatrix");
	m_viewPosId = glGetUniformLocation(progId, "viewPos");
}

void SpecularMaterial::Render(RendData rendData){
    
    if(m_textId > 0){   //Only if we loaded a texture…
        glBindTexture(GL_TEXTURE_2D, m_textId);
    }
    
    glCullFace(GL_BACK);
    glUseProgram(m_progId);
    
	mat4 modelMatrix = rendData.modelMatrix;
	mat4 MVMatrix = rendData.viewMatrix * modelMatrix;
    mat4 MVPMatrix = rendData.projMatrix * MVMatrix;
	mat4 normalMatrix = transpose(inverse(modelMatrix));
    
    glUniformMatrix4fv(m_modelViewProjId, 1, GL_FALSE, &MVPMatrix[0][0]);
	glUniformMatrix4fv(m_modelViewId, 1, GL_FALSE, &MVMatrix[0][0]);
    glUniformMatrix4fv(m_normMatId, 1, GL_FALSE, &normalMatrix[0][0]);

    vec3 ambientColor = vec3(1, 0, 0);
    vec3 diffuseColor = vec3(0.5f, 0.5f, 0.5f);
    vec3 specularColor = vec3(1.0f, 1.0f, 1.0f);
    glUniform3f(m_ambientId, ambientColor.x, ambientColor.y, ambientColor.z);
    glUniform3f(m_diffuseId, diffuseColor.x, diffuseColor.y, diffuseColor.z);
    glUniform3f(m_specularId, specularColor.x, specularColor.y, specularColor.z);
    glUniform3f(m_viewPosId, rendData.cameraPos.x, rendData.cameraPos.y, rendData.cameraPos.z);

    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
}

/*** LitMaterial (abstract) ***/

LitMaterial::LitMaterial(GLuint progId) : Material(progId)
{
    m_modelViewProjId = glGetUniformLocation(progId, "MVPMatrix");
    m_modelId = glGetUniformLocation(progId, "MMatrix");
}

/*** Material (abstract) ***/

GLuint Material::LoadBMP(const char * imagepath){
    // Data read from the header of the BMP file
    unsigned char header[54];	// Each BMP file begins by a 54-bytes header
    unsigned int dataPos;		// Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;		// = width*height*3
    unsigned char * data;		// Actual RGB data
    
    // Open the file
    const char* mode = "rb";
    
    char path[128];
    strcpy (path, RESOURCE_PATH);
    strcat (path, imagepath);
    
#ifdef _WIN32	//keep windows from complaining…
    FILE * file = nullptr;
    if(fopen_s(&file, path, mode)){
        printf("File could not be opened\n");
        return 0;
    }
#else
    FILE * file = fopen(path, mode);
#endif
    
    if (!file){
        printf("Image could not be opened\n");
        return 0;
    }
    
    // If not 54 bytes read : problem
    if(fread(header, 1, 54, file)!=54 ){
        printf("Not a correct BMP file\n");
        return false;
    }
    
    //Checking to see if first two bytes are 'B' and 'M'
    if ( header[0] != 'B' || header[1] != 'M' ){
        printf("Not a correct BMP file\n");
        return 0;
    }
    
    // Read ints from the byte array
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    
    // Some BMP files are misformatted, guess missing information
    if(imageSize==0)
        imageSize=width*height*3;	// 3 : one byte for each Red, Green and Blue component
    if(dataPos==0)
        dataPos=54;					// The BMP header is done that way
    
    // Create a buffer
    data = new unsigned char [imageSize];
    
    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);
    
    //Everything is in memory now, the file can be closed
    fclose(file);
    
    // Create one OpenGL texture
    glGenTextures(1, &m_textId);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, m_textId);
    
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    return m_textId;
}
