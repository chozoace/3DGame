#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include "Shader.h"

#include <time.h>

class GameController
{
	public:
		GameController();
		~GameController();
		bool initialize();
		void update(float timeElapsed);
		void handleInput();
		void render();
		GLFWwindow* getWindow() {
			return window;
		}
	private:
		GLFWwindow* window;
		GameObject player;

};

