#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <time.h>
#include "GameController.h"

bool initialized = false;
float screenWidth = 800.0f;
float screenHeight = 600.0f;

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

float vertices[] = {
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

Vertex v1, v2, v3, v4;
glm::vec3 vr1(vertices[0], vertices[1], vertices[2]);
glm::vec3 vr2(vertices[3], vertices[4], vertices[5]);
glm::vec3 vr3(vertices[6], vertices[7], vertices[8]);
glm::vec3 vr4(vertices[9], vertices[10], vertices[11]);

GameObject* testObj;
Shader* shader;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GameController::GameController()
{
	if (!initialize())
	{
		printf("Failed to Initialize GameController\n");
	}
	else
	{
		initialized = true;
	}
}

GameController::~GameController()
{
	delete testObj;
	delete shader;

	glfwDestroyWindow(window);
	glfwTerminate();
}

bool GameController::initialize()
{
	bool success = true;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		success = false;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		success = false;
	}
	glViewport(0, 0, screenWidth, screenHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	vector<Vertex> vertexVector;

	v1.Position = vr1;
	v2.Position = vr2;
	v3.Position = vr3;
	v4.Position = vr4;
	vertexVector.push_back(v1);
	vertexVector.push_back(v2);
	vertexVector.push_back(v3);
	vertexVector.push_back(v4);
	vector<unsigned int> indicesVector;
	indicesVector.push_back(indices[0]);
	indicesVector.push_back(indices[1]);
	indicesVector.push_back(indices[2]);
	indicesVector.push_back(indices[3]);
	indicesVector.push_back(indices[4]);
	indicesVector.push_back(indices[5]);

	testObj = new GameObject(vertexVector, indicesVector);
	shader = new Shader("shader.vxs", "shader.frs");

	return success;
}

void GameController::update(float timeElapsed)
{

}

void GameController::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render logic
	testObj->draw(*shader);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void GameController::handleInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		printf("in handle input");
		glfwSetWindowShouldClose(window, true);
	}
}