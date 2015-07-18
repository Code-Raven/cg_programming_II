#include "World.h"

World::World(){
	balls = new Ball[numBalls = 1];
	balls[0].SetVelocity(vec3(1.0f, 0.1f, 0.0f));
	balls[0].SetPosition(vec3(0.0f, 0.0f, 0.0f));

	paddles = new Paddle[numPaddles = 4];

	//Will move these paddles via user input...
	paddles[0].SetPosition(vec3(1.5f, 0.0f, 0.0f));
	paddles[1].SetPosition(vec3(-1.5f, 0.0f, 0.0f));

	paddles[0].SetKeys(GLFW_KEY_UP, GLFW_KEY_DOWN); 
	paddles[1].SetKeys(GLFW_KEY_W, GLFW_KEY_S); 

	//Using these paddles to serve as upper and lower walls...
	paddles[2].SetPosition(vec3(0.0f, 1.15f, 0.0f));
	paddles[3].SetPosition(vec3(0.0f, -1.15f, 0.0f));
	paddles[2].SetScale(vec3(1.45f, 0.025f, 1.0f));
	paddles[3].SetScale(vec3(1.45f, 0.025f, 1.0f));

	SaveObjectStates();

	resetKey = GLFW_KEY_SPACE;
}

World::~World(){
	delete[] balls;
	balls = NULL;

	delete[] paddles;
	balls = NULL;
}

void World::LoadObjectStates(){
	for(GLuint i = 0; i < numBalls; ++i){
		balls[i].LoadObjectState("Loaded Ball State!!!");
	}
	for(GLuint i = 0; i < numPaddles; ++i){
		paddles[i].LoadObjectState("Loaded Paddle State!!!");
	}
}

void World::SaveObjectStates(){
	for(GLuint i = 0; i < numBalls; ++i){
		balls[i].SaveObjectState("Saved Ball State!!!");
	}
	for(GLuint i = 0; i < numPaddles; ++i){
		paddles[i].SaveObjectState("Saved Paddle State!!!");
	}
}

void World::ResetWorld(){
	static bool keyPressed = false;

	if(!keyPressed && glfwGetKey(window, resetKey) == GLFW_PRESS){
		LoadObjectStates();
		keyPressed = true;
	}
	else if(keyPressed && glfwGetKey(window, resetKey) == GLFW_RELEASE){
		keyPressed = false;
	}
}

void World::Update(const float& deltaTime){

	ResetWorld();

	for(GLuint i = 0; i < numBalls; ++i){
		balls[i].Update(deltaTime);
	}

	for(GLuint i = 0; i < numPaddles; ++i){
		paddles[i].Update(deltaTime);
		
		//HandleCollision...
		for(GLuint j = 0; j < numBalls; ++j){
			Paddle &paddle = paddles[i];
			Ball &ball = balls[j];
			
			float leftDist = ball.GetRightX() - paddle.GetLeftX();
			float rightDist = paddle.GetRightX() - ball.GetLeftX();
			float topDist = paddle.GetTopY() - ball.GetBottomY();
			float bottomDist = ball.GetTopY() - paddle.GetBottomY();

			//Collision Happens...
			if(rightDist > 0.0f && leftDist > 0.0f && topDist > 0.0f && bottomDist > 0.0f){

				vec3 pushDir;
				float pushDist = 0.0f;

				//Set push-out direction based on which ever distance is smallest...
				if(rightDist < leftDist && rightDist < topDist && rightDist < bottomDist)
					pushDir = vec3(pushDist = rightDist, 0.0f, 0.0f);
				else if(leftDist < rightDist && leftDist < topDist && leftDist < bottomDist)
					pushDir = vec3(-(pushDist = leftDist), 0.0f, 0.0f);
				else if(topDist < leftDist && topDist < rightDist && topDist < bottomDist)
					pushDir = vec3(0.0f, -(pushDist = topDist), 0.0f);
				else if(bottomDist < leftDist && bottomDist < topDist && bottomDist < rightDist)
					pushDir = vec3(0.0f, pushDist = topDist, 0.0f);

				pushDir = glm::normalize(pushDir);
				vec3 ballPos = ball.GetPosition();

				//If we wanted a smooth effect we would simply push back...
				//ballPos += (pushDir * pushDist);	
				//However, we want to reflect off of our last good position, so we will simply revert the velocity...
				vec3 revertedVelocity = ball.GetVelocity() * deltaTime;
				vec3 revertedPos = ballPos - revertedVelocity;

				//Let's also accelerate our velocity on hit...
				float acceleration = 1.01f;	//And of course we apply our reflection math here...
				vec3 reflectedVelocity = ball.GetVelocity() - (pushDir * glm::dot(ball.GetVelocity(), pushDir) * 2.0f);
				vec3 lostVelocity = reflectedVelocity * deltaTime;	//And don't forget to re-apply our lost velocity...

				ball.SetPosition(revertedPos + lostVelocity);
				ball.SetVelocity(reflectedVelocity * acceleration);

				//Let's play a sound :)
				printf("\a");
			}
		}
	}
}

void World::Render(const Camera& camera){
	for(GLuint i = 0; i < numBalls; ++i){
		balls[i].Render(camera);
	}
	for(GLuint i = 0; i < numPaddles; ++i){
		paddles[i].Render(camera);
	}
}