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
    
    GLuint activeProgramId = programIds[1];
    glUseProgram(activeProgramId);

	Camera camera(0.0f, 0.0f, -6.0f, 6.0f /*move speed*/);
	float aspectRatio = SCREEN_WIDTH/(float)SCREEN_HEIGHT;
	camera.MVPMatrixID = glGetUniformLocation(activeProgramId, "MVP");
	camera.projectionMatrix = perspective(FIELD_OF_VIEW, aspectRatio, Z_NEAR, Z_FAR);

	World world;

	/*	//Keep this around for reference...
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );			//Render lines...
		glEnable( GL_TEXTURE_2D );								//Forgot what this does :P
		glEnable(GL_CULL_FACE);									//Enables polygon culling...
		glCullFace(GL_BACK);									//Cull back face...
		glEnable(GL_DEPTH_TEST);								//Fixes rendering order issues...
		glEnable(GL_BLEND);										//Allows transparency. Blends forground and background colors...
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );	//How you want blending to happen...
	*/

	//Fixes issue with rendering order...
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	do{
		//Getting delta time...
		float deltaTime = (float)getDeltaTime();

		UpdateKeys(window);	//Camera vertical and horizontal transition...
		UpdateMouse(window, deltaTime);
		//camera.xPos += deltaTime * camera.moveSpeed * gKeyA;
		//camera.xPos -= deltaTime * camera.moveSpeed * gKeyD;
		//camera.zPos -= deltaTime * camera.moveSpeed * gKeyS;
		//camera.zPos += deltaTime * camera.moveSpeed * gKeyW;

		//// Camera matrix
		//camera.viewMatrix = lookAt(
		//	vec3(camera.xPos, camera.yPos, camera.zPos), // Camera position in World Space
		//	vec3(camera.xPos, camera.yPos, camera.zPos + 1), // and looks at the origin
		//	vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		//);
		// Direction : Spherical coordinates to Cartesian coordinates conversion
		glm::vec3 forward(
			cos(gMouseVertAngle) * sin(gMouseHorizAngle),
			0,
			sin(gMouseVertAngle) * cos(gMouseHorizAngle)
		);

		//glm::vec3 forward(
		//	cos(gMouseVertAngle),
		//	0,
		//	sin(gMouseVertAngle)
		//);

		//// Right vector
		glm::vec3 right(
			sin(gMouseHorizAngle - HALF_PI),
			0,
			cos(gMouseHorizAngle - HALF_PI)
		);

		//glm::vec3 up = vec3(0, 1, 0);

		//glm::vec3 right = glm::cross(up, forward);

		glm::vec3 up = glm::cross(right, forward);


		camera.Update(forward, right, up, deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world.Update(deltaTime);
		world.Render(camera);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	return EXIT_WITH_SUCCESS;
}