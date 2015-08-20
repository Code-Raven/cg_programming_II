//
//  Material.cpp
//  cg_programming_II
//
//  Created by Branden Oden on 8/16/15.
//  Copyright (c) 2015 Branden Oden. All rights reserved.
//

#include "Material.h"

/*** custom material definitions ***/

void BasicMaterial::Render(RendData rendData){
    
    if(m_textId > 0){   //Only if we loaded a texture…
        glBindTexture(GL_TEXTURE_2D, m_textId);
    }
    
    glCullFace(GL_BACK);
    glUseProgram(m_progIds[0]);
    
    mat4 MVPMatrix = rendData.projMatrix * rendData.viewMatrix * rendData.modelMatrix;
    
    glUniformMatrix4fv(m_modelViewProjIds[0], 1, GL_FALSE, &MVPMatrix[0][0]);
    
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
}

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
    glUseProgram(m_progIds[0]);
    
    mat4 MVPMatrix = rendData.projMatrix * rendData.viewMatrix * rendData.modelMatrix;
    glUniformMatrix4fv(m_modelViewProjIds[0], 1, GL_FALSE, &MVPMatrix[0][0]);
	glUniformMatrix4fv(m_modelIds[0], 1, GL_FALSE, &rendData.modelMatrix[0][0]);
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glLineWidth(10.0f);
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
    
    glUseProgram(m_progIds[2]);
	glUniformMatrix4fv(m_modelViewProjIds[2], 1, GL_FALSE, &MVPMatrix[0][0]);
	glUniformMatrix4fv(m_modelIds[2], 1, GL_FALSE, &rendData.modelMatrix[0][0]);
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
    
    glPopAttrib();
}

void OutlineMaterial::Render(RendData rendData){
    
    if(m_textId > 0){   //Only if we loaded a texture…
        glBindTexture(GL_TEXTURE_2D, m_textId);
    }
    
    glCullFace(GL_BACK);
    glUseProgram(m_progIds[0]);
    
    mat4 MVPMatrix = rendData.projMatrix * rendData.viewMatrix * rendData.modelMatrix;
    glUniformMatrix4fv(m_modelViewProjIds[0], 1, GL_FALSE, &MVPMatrix[0][0]);
	glUniformMatrix4fv(m_modelIds[0], 1, GL_FALSE, &rendData.modelMatrix[0][0]);
    
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);
    
    // Render the mesh into the stencil buffer.
    
    glEnable(GL_STENCIL_TEST);
    
    glStencilFunc(GL_ALWAYS, 1, -1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
    
    // Render the thick wireframe version.
    
    glUseProgram(m_progIds[2]);
    
    glUniformMatrix4fv(m_modelViewProjIds[2], 1, GL_FALSE, &MVPMatrix[0][0]);
	//glUniformMatrix4fv(m_modelIds[2], 1, GL_FALSE, &rendData.modelMatrix[0][0]);
    
    glStencilFunc(GL_NOTEQUAL, 1, -1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    glLineWidth(10);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glDrawArrays(rendData.rendMode, 0, rendData.numIndices);
}

/*** material definitions ***/

Material::Material() :
	m_progIds(nullptr), m_textId(0), m_numIds(0),
	m_modelIds(nullptr), m_modelViewIds(nullptr),
	m_modelViewProjIds(nullptr){}

void Material::SetProgIds(GLuint *progIds, GLuint numIds){
    m_progIds = progIds;
	GLuint progId = 0;

	m_modelIds = new GLuint[numIds];
	m_modelViewIds = new GLuint[numIds];
	m_modelViewProjIds = new GLuint[numIds];

	for(int i = 0; i < numIds; ++i){
		progId = progIds[i];
		m_modelIds[i] = glGetUniformLocation(progId, "MMatrix");
		m_modelViewIds[i] = glGetUniformLocation(progId, "MVMatrix");
		m_modelViewProjIds[i] = glGetUniformLocation(progId, "MVPMatrix");
	}
}

Material::~Material(){
	if(m_modelIds != nullptr) { delete m_modelIds; }
	if(m_modelViewIds != nullptr) { delete m_modelViewIds; }
	if(m_modelViewProjIds != nullptr) { delete m_modelViewProjIds; }
}

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
