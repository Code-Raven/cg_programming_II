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
        BasicMaterial* material = new BasicMaterial();
        material->SetProgId(g_programIds[0]);
        material->LoadBMP("dirt.bmp");
    
        mesh[0].BuildMesh("bunny.obj");
        mesh[0].SetMaterial(material);
        mesh[0].SetScale(vec3(3.0f));
    #endif
    
    #ifdef BUNNY_LARGE
        BasicMaterial* material = new BasicMaterial();
        material->SetProgId(g_programIds[0]);
        material->LoadBMP("dirt.bmp");
    
        mesh[0].BuildMesh("bunny_large.obj");
        mesh[0].SetMaterial(material);
        mesh[0].SetPosition(vec3(0.0f, -3.0f, 0.0f));
        mesh[0].SetScale(vec3(3.0f));
    #endif
    
    #ifdef DIALGA
        BasicMaterial* material = new BasicMaterial();
        material->SetProgId(g_programIds[0]);
        material->LoadBMP("dialga.bmp");
    
        mesh[0].BuildMesh("dialga.obj");
        mesh[0].SetMaterial(material);
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
	//cube[0].Update(deltaTime);
    mesh[0].Update(deltaTime);
}

void World::Render(const Camera& camera){
	//plane[0].Render(camera);
	//cube[0].Render(camera);
	mesh[0].Render(camera);
}