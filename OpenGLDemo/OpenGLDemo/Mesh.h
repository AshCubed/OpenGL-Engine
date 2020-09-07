#pragma once

#include<iostream>
#include<vector>

#include "Primitives.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

class Mesh {
private:
	unsigned nrOfVertices;
	unsigned nrOfIndicies;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 ModelMatrix;
	
	void initVAO(Primitive* primitative) {
		//SET variables
		this->nrOfVertices = primitative->getnrOfVertices();
		this->nrOfIndicies = primitative->getnrOfIndicies();

		//GEN VAO and BIND
		//CREATE VAO
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), primitative->getVertices(), GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndicies * sizeof(GLuint), primitative->getIndicies(), GL_STATIC_DRAW);

		//SET VERTEX POINTERS AND ENABLE (INPUT ASSEMVLY)
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//Texcoord
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		//BIND VAO 0
		glBindVertexArray(0);
	}
	

	void initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndicies) {
		//SET variables
		this->nrOfVertices = nrOfVertices;
		this->nrOfIndicies = nrOfIndicies;

		
		//GEN VAO and BIND
		//CREATE VAO
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndicies* sizeof(GLuint), indexArray, GL_STATIC_DRAW);

		//SET VERTEX POINTERS AND ENABLE (INPUT ASSEMVLY)
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//Texcoord
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		//BIND VAO 0
		glBindVertexArray(0);
	}

	void updateUniforms(Shader* shader) {
		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}

	void updateModelMatrix() {
		this->ModelMatrix = glm::mat4(1.f);
		this->ModelMatrix = glm::translate(ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, glm::vec3(this->scale));
	}


public:
	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndicies, 
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f)) 
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

		this->initVAO(vertexArray, nrOfVertices, indexArray, nrOfIndicies);
		this->updateModelMatrix();
	}

	Mesh(Primitive* primitative, 
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f))
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

		this->initVAO(primitative);
		this->updateModelMatrix();
	}

	~Mesh() {
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}

	//ACCESSORS


	//MODIFIERS
	void setPosition(const glm::vec3 position) {
		this->position = position;
	}
	void setRotation(const glm::vec3 roatation) {
		this->rotation = roatation;
		if (this->rotation.x > 360)
		{
			this -> rotation.x = 0;
		}
	}
	void setScale(const glm::vec3 scale) {
		this->scale = scale;
	}


	//FUNCTIONS
	void move(const glm::vec3 position) {
		this->position += position;
	}
	void rotate(const glm::vec3 rotation) {
		this->rotation += rotation;
	}
	void scaled(const glm::vec3 scale) {
		this->scale += scale;
	}

	void update() {

	};

	void render(Shader* shader) {
		//Update Uniforms
		this->updateModelMatrix();
		this->updateUniforms(shader);

		shader->use();

		//Bind VAO
		glBindVertexArray(this->VAO);
		
		//RENDER
		/*if (this->indicies.empty())
		{
			glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, this->nrOfIndicies, GL_UNSIGNED_INT, 0);
		}*/
		glDrawElements(GL_TRIANGLES, this->nrOfIndicies, GL_UNSIGNED_INT, 0);
	};
};
