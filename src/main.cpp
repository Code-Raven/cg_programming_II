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
    
    GLuint activeProgramId = programIds[2];
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
    
    //HACK: so that we are not looking up in the air…
    gMouseHorizAngle = HALF_PI;
    gMouseVertAngle = HALF_PI;

	do{
		//Getting delta time...
		float deltaTime = (float)getDeltaTime();

		UpdateKeys(window);	//Camera vertical and horizontal transition...
		UpdateMouse(window, deltaTime);
            
        //Let's keep gimblelock from happening…
        gMouseVertAngle = glm::clamp(gMouseVertAngle, 0.1f, PI - 0.1f);
        
        //Spherical coordinates to cartesian coordinates conversion
        glm::vec3 forward(
            sin(gMouseVertAngle) * cos(gMouseHorizAngle),
            cos(gMouseVertAngle),
            sin(gMouseVertAngle) * sin(gMouseHorizAngle)
        );
        
        //Subtracting 90 degrees in radians to create the up vector…
        glm::vec3 up(
            sin(gMouseVertAngle - HALF_PI) * cos(gMouseHorizAngle),
            cos(gMouseVertAngle - HALF_PI),
            sin(gMouseVertAngle - HALF_PI) * sin(gMouseHorizAngle)
        );
        
        //And of course we need our right vector…
        glm::vec3 right = glm::cross(up, forward);
        
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