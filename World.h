#include "Object.h"
#include "Ball.h"
#include "Paddle.h"

class World{

	public:
		World();
		~World();

		void SaveObjectStates();
		void LoadObjectStates();
		void ResetWorld();
		void Update(const float& deltaTime);
		void Render(const Camera& camera);
		
	private:
		int resetKey;
		GLuint numBalls, numPaddles;
		Ball* balls;
		Paddle* paddles;
};