#include "Application.h"
#include "World.h"

using namespace setup;

int main(){
	if(InitWindowFailed() | InitGlewFailed()){
		return EXIT_WITH_ERROR;
	}

	GLuint vertexArrayID = 0;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
    
    stdVecStr vertShaders = ReadFiles(".vert");
    stdVecStr fragShaders = ReadFiles(".frag");
    
    if(vertShaders.size() != fragShaders.size()){
        return EXIT_WITH_ERROR;
    }
    
    size_t numShaders = vertShaders.size();
    GLuint* programIds = (GLuint*)malloc(sizeof(GLuint) * numShaders);
    
    for(size_t i = 0; i < numShaders; ++i){
        programIds[i] = LoadShaders(vertShaders[i].c_str(), fragShaders[i].c_str());
    }
    
    GLuint activeProgramId = programIds[0];
    glUseProgram(activeProgramId);

	Camera camera;
	float aspectRatio = SCREEN_WIDTH/(float)SCREEN_HEIGHT;
	camera.MVPMatrixID = glGetUniformLocation(activeProgramId, "MVP");
	camera.projectionMatrix = perspective(FIELD_OF_VIEW, aspectRatio, Z_NEAR, Z_FAR);

	World world;

	#if 0	//Set to 1 to render lines...
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	#endif

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Getting delta time...
		float deltaTime = (float)getDeltaTime();

		// Camera matrix
		camera.viewMatrix = lookAt(
			vec3(0,0,3), // Camera is at (4,3,3), in World Space
			vec3(0,0,0), // and looks at the origin
			vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

		world.Update(deltaTime);
		world.Render(camera);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	return EXIT_WITH_SUCCESS;
}