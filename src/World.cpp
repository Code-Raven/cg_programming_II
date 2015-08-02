#include "World.h"

//TODO: Add functionality later...
World::World(){
	plane = new Plane(1, 1);
	//plane->SetScale(vec3(0.15f));
	//plane->SetPosition(vec3(-1.0f, -1.0f, 0.0f));

	cube = new Cube();
	cube->SetScale(vec3(0.5f));
	//cube->SetPosition(vec3(-2.0f, -2.0f, 0.0f));

	//GLuint textureID = plane->LoadBMP("test.bmp");
	//GLuint textureID = plane->LoadBMP("dirt.bmp");
	//GLuint textureID = plane->LoadBMP("world.bmp");
}

//TODO: Add functionality later...
World::~World(){
	//delete plane;
	//plane = NULL;

	delete cube;
	cube = NULL;
}

void World::Update(const float& deltaTime){

	//plane->Update(deltaTime);
	cube->Update(deltaTime);
}

void World::Render(const Camera& camera){
	//plane->Render(camera);
	cube->Render(camera);
}