#include "Input.h"

//global variables imlicitly get initialized to zero, so no need to set them! :)
char gKeyA, gKeyW, gKeyD, gKeyS;
glm::vec2 gMousePos, gMouseDelta;
float gMouseHorizAngle , gMouseVertAngle;
int gCursMode = GLFW_CURSOR_DISABLED;

static void SetCursor(GLFWwindow *window, glm::vec2 &mousePos, int cursMode){
	if(cursMode = GLFW_CURSOR_DISABLED){
		int winWidth, winHeight;
		glfwGetWindowSize(window, &winWidth, &winHeight);

		mousePos = glm::vec2(winWidth/2.0, winHeight/2.0);

		//Setting cursor back to center of screen...
		glfwSetCursorPos(window, mousePos.x, mousePos.y);
	}

	//showing/hiding mouse, etc.
	glfwSetInputMode(window, GLFW_CURSOR, cursMode);
}

void UpdateKeys(GLFWwindow *window){

	gKeyA = gKeyW = gKeyD = gKeyS = 0;

	//directional keys for translating camera...
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		gKeyA = 1;
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		gKeyW = 1;
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		gKeyD = 1;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		gKeyS = 1;

	//key for switching lookat/selction mode...
	if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		gCursMode = GLFW_CURSOR_NORMAL;
	else if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		gCursMode = GLFW_CURSOR_DISABLED;
}

//call glfwGetMousePos(&xpos, &ypos); and set.
//set void glfwSetCursorPos ( GLFWwindow * window, double xpos, double ypos )
void UpdateMouse(GLFWwindow *window, float deltaTime){

	int winWidth, winHeight;
	double mousePosX, mousePosY;

	glfwGetWindowSize(window, &winWidth, &winHeight);
	glfwGetCursorPos(window, &mousePosX, &mousePosY);

	glm::vec2 newMousePos((float)mousePosX, (float)mousePosY);
	gMouseDelta = newMousePos - gMousePos;
	gMousePos = newMousePos;

	// we ONLY want to compute the new orientation if the cursor is hidden...
	if(gCursMode == GLFW_CURSOR_DISABLED){
		gMouseHorizAngle -= gMouseDelta.y * deltaTime * MOUSE_SPEED;
		gMouseVertAngle  += gMouseDelta.x * deltaTime * MOUSE_SPEED;
	}

	SetCursor(window, gMousePos, gCursMode);
}
