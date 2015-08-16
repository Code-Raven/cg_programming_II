#include "World.h"

//TODO: Add functionality later...
World::World(){
    plane = new Plane[1];
    plane[0].BuildTriangles(1, 1);
	//plane[0].SetScale(vec3(0.15f));
	//plane[0].SetPosition(vec3(-1.0f, -1.0f, 0.0f));

	cube = new Cube[1];
	cube[0].SetScale(vec3(6.0f));
	cube[0].SetPosition(vec3(0.0f, 1.0f, 0.0f));
    cube[0].Rotate(45, vec3(0.0f, 1.0f, 0.0f));
    
    mesh = new Mesh[1];
    
    
    #define BUNNY_LARGE
    
    #ifdef BUNNY
        mesh[0].BuildMesh("bunny.obj");
        (void)mesh[0].LoadBMP("dirt.bmp");
        mesh[0].SetScale(vec3(3.0f));
    #endif
    
    #ifdef BUNNY_LARGE
        mesh[0].BuildMesh("bunny_large.obj");
        (void)mesh[0].LoadBMP("dirt.bmp");
        mesh[0].SetPosition(vec3(0.0f, -3.0f, 0.0f));
        mesh[0].SetScale(vec3(3.0f));
    #endif
    
    #ifdef DIALGA
        mesh[0].BuildMesh("dialga.obj");
        (void)mesh[0].LoadBMP("dialga.bmp");
        mesh[0].SetScale(vec3(0.1f));
    #endif

    
	//mesh[0].BuildMesh("bunny.obj");
	//mesh[0].BuildMesh("head.obj");
	//mesh[0].BuildMesh("helix.obj");
	//mesh[0].BuildMesh("sphere.obj");
	//mesh[0].BuildMesh("arceus.obj");
	//mesh[0].BuildMesh("dialga.obj");
    //mesh[0].BuildMesh("cube.obj");
    //mesh[0].SetPosition(vec3(0.0f, -1.5f, -2.0f));
    mesh[0].RotateOverTime(1.0f, vec3(0, 1, 0));

	//(void)mesh[0].LoadBMP("dialga.bmp");
	//GLuint textureID = plane[0].LoadBMP("test.bmp");
	//GLuint textureID = plane[0].LoadBMP("dirt.bmp");
	//GLuint textureID = plane[0].LoadBMP("world.bmp");
	//GLuint textureID = plane[0].LoadBMP("arceus.bmp");
}

//TODO: Add functionality later...
World::~World(){
	delete[] plane;
	plane = NULL;

	delete[] cube;
	cube = NULL;
    
    delete[] mesh;
    mesh = NULL;
}

void World::Update(const float& deltaTime){

	//plane[0].Update(deltaTime);
	cube[0].Update(deltaTime);
    mesh[0].Update(deltaTime);
}

void World::Render(const Camera& camera){
	//plane[0].Render(camera);
	//glCullFace(GL_FRONT);
	//cube[0].Render(camera);

	/*glUseProgram(g_programIds[0]);
	glCullFace(GL_BACK);
	mesh[0].Render(camera);*/

	glCullFace(GL_BACK);

	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);

	// Render the mesh into the stencil buffer.
	
	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_ALWAYS, 1, -1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	glUseProgram(g_programIds[2]);
	mesh[0].Render(camera);

	// Render the thick wireframe version.

	glStencilFunc(GL_NOTEQUAL, 1, -1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glLineWidth(10);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	
	glUseProgram(g_programIds[0]);
	mesh[0].Render(camera);

	////Push the GL attribute bits so that we don't wreck any settings
	//glPushAttrib( GL_ALL_ATTRIB_BITS );
	////Enable polygon offsets, and offset filled polygons forward by 2.5
	//glEnable( GL_POLYGON_OFFSET_FILL );
	//glPolygonOffset( -30.0f, -30.0f );	//TODO: read up on this later...

	//glCullFace(GL_BACK);

	//glUseProgram(g_programIds[0]);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	//glLineWidth(10.0f);
	//mesh[0].Render(camera);

	//glUseProgram(g_programIds[1]);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	//mesh[0].Render(camera);

	//glPopAttrib();
}