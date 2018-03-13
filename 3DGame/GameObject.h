#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
	glm::vec3 Position;
	//glm::vec3 Normal;
	//glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class GameObject
{
	public:
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
		unsigned int VAO;

		GameObject() {

		}

		GameObject(vector<Vertex> vertices, vector<unsigned int> indices)
		{
			this->vertices = vertices;
			this->indices = indices;
			//this->textures = textures;

			setupDrawParams();
		}

		void draw(Shader shader)
		{
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			unsigned int normalNr = 1;
			unsigned int heightNr = 1;
			shader.use();
			/*
			for (unsigned int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);

				string number;
				string name = textures[i].type;
				if (name == "texture_diffuse")
					number = std::to_string(diffuseNr++);
				else if (name == "texture_specular")
					number = std::to_string(specularNr++); // transfer unsigned int to stream
				else if (name == "texture_normal")
					number = std::to_string(normalNr++); // transfer unsigned int to stream
				else if (name == "texture_height")
					number = std::to_string(heightNr++); // transfer unsigned int to stream

				shader.setInt((name + number).c_str(), i);
				//glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
				glBindTexture(GL_TEXTURE_2D, textures[i].id);
			}
			*/

			//draw mesh
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			//glBindVertexArray(0);

			//glActiveTexture(GL_TEXTURE0);
		}
	private:
		unsigned int VBO, EBO;
		void setupDrawParams() 
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
			
			//set vertex attribute pointers
			//vertex positions
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			//vertex normals
			//glEnableVertexAttribArray(1);
			//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
			// vertex texture coords
			//glEnableVertexAttribArray(2);
			//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		
			//glBindVertexArray(0);
		}
};

#endif