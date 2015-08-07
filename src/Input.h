//GLFW provides window creation and input control.
#include <glfw3.h>
#include <glm/glm.hpp>
#pragma once

#define EPSILON 0.0005f
#define MOUSE_SPEED 0.2f;

//Look up keys here: http://www.glfw.org/docs/latest/group__keys.html

extern char gKeyA;
extern char gKeyW;
extern char gKeyD;
extern char gKeyS;

extern glm::vec2 gMousePos;
extern glm::vec2 gMouseDelta;
extern float gMouseHorizAngle;
extern float gMouseVertAngle;
extern int gCursMode;

void UpdateKeys(GLFWwindow *window);
void UpdateMouse(GLFWwindow *window, float deltaTime);
