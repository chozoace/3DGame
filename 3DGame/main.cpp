#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameController.h"
#include <time.h>

using namespace std;

int main()
{
	int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmpDbgFlag);
	
	bool running = true;
	GameController gameController;
	float lastTime = (float)clock() / CLOCKS_PER_SEC;
	float minTimeStep = 1 / 60;

	while (!glfwWindowShouldClose(gameController.getWindow()))
	{
		float current = (float)clock() / CLOCKS_PER_SEC;
		float elapsed = current - lastTime;

		//handle input
		gameController.handleInput();
		//update game
		gameController.update(elapsed);
		//render
		gameController.render();

		lastTime = current;
		if (elapsed < minTimeStep)
		{
			Sleep((minTimeStep - elapsed) * 1000);
		}
	}
	printf("end game");

	return 0;
}