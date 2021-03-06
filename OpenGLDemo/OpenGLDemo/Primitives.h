#pragma once
#include<vector>
#include "Vertex.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Primitive {
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indicies;


public:
	Primitive() {};
	virtual ~Primitive() {};

	//Functions
	void set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indicies, const unsigned nrOfIndicies) {
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}

		for (size_t i = 0; i < nrOfIndicies; i++)
		{
			this->indicies.push_back(indicies[i]);
		}
	}
	
	inline Vertex* getVertices() { return vertices.data(); }
	inline GLuint* getIndicies() { return indicies.data(); }
	inline const unsigned getnrOfVertices() { return this->vertices.size(); }
	inline const unsigned getnrOfIndicies() { return this->indicies.size(); }

};

class Quad : public Primitive {
public:
	Quad() : Primitive()
	{
		Vertex vertices[] =
		{
			//Position                          //Color                     //TexCoord              //Normals                  
			glm::vec3(-0.5f, 0.5f, 0.f),        glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),       glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),        glm::vec3(0.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.f),         glm::vec3(1.f, 1.f, 0.f),   glm::vec2(1.f, 1.f),    glm::vec3(0.f, 0.f, 1.f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indicies[] =
		{
			0, 1, 2,    //Triangle 1
			0, 2, 3     //Triangle 2
		};

		unsigned nrOfIndicies = sizeof(indicies) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indicies, nrOfIndicies);
	}
};

class Triangle : public Primitive {
public:
	Triangle() : Primitive()
	{
		Vertex vertices[] =
		{
			//Position                          //Color                     //TexCoord              //Normals                  
			glm::vec3(-0.5f, 0.5f, 0.f),        glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),       glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),        glm::vec3(0.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indicies[] =
		{
			0, 1, 2,    //Triangle 1
		};

		unsigned nrOfIndicies = sizeof(indicies) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indicies, nrOfIndicies);
	}
};

class Pyramid : public Primitive
{
public:
	Pyramid()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,	//Triangle 1
			0, 3, 1,
			0, 4, 3,
			0, 2, 4
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Cube : public Primitive 
{
public:
	Cube()
		: Primitive() 
	{
		Vertex vertices[] =
		{
			//Position                          //Color                     //TexCoord              //Normals                  
			glm::vec3(-1.0, -1.0,  1.0),        glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(1.0, -1.0,  1.0),			glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-1.0,  1.0,  1.0),        glm::vec3(0.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(1.0,  1.0,  1.0),         glm::vec3(1.f, 1.f, 0.f),   glm::vec2(1.f, 1.f),    glm::vec3(0.f, 0.f, 1.f),

			glm::vec3(-1.0, -1.0, -1.0),        glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(1.0, -1.0, -1.0),			glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-1.0,  1.0, -1.0),        glm::vec3(0.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(1.0,  1.0, -1.0),			glm::vec3(1.f, 1.f, 0.f),   glm::vec2(1.f, 1.f),    glm::vec3(0.f, 0.f, 1.f)
		};

		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indicies[] =
		{
				0, 2, 1,
				0, 3, 2,

				1,2,6,
				6,5,1,

				4,5,6,
				6,7,4,

				2,3,6,
				6,3,7,

				0,7,3,
				0,4,7,

				0,1,5,
				0,5,4
		};

		unsigned nrOfIndicies = sizeof(indicies) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indicies, nrOfIndicies);
	}

};