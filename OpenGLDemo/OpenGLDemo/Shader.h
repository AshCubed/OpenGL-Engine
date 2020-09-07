#pragma once
#include<iostream>
#include<fstream>
#include<string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include<glm/glm.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/type_ptr.hpp>

using namespace std;

class Shader 
{
private:
	//Member Variables
	GLuint id;
	const int versionMajor;
	const int versionMinor;

	//Private Functions
	std::string loadShaderSource(const char* fileName) {
		string temp = "";
		string src = "";

		ifstream in_file;

		//VertexShader
		in_file.open(fileName);

		if (in_file.is_open())
		{
			while (getline(in_file, temp)) {
				src += temp + "\n";
			}
		}
		else {
			cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << fileName << "\n";
		}

		in_file.close();

		std::string versionNr = to_string(versionMajor) + to_string(versionMinor) + "0";
		src.replace(src.find("#version"), 12, ("#version " + versionNr));

		return src;
	}

	GLuint loadShader(GLenum type, const char* fileName) {
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadShaderSource(fileName).c_str();
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			cout << "ERROR::SHADDER::COULD_NOT_COMPILE_SHADER" << fileName << "\n";
			cout << infoLog << "\n";
		}

		return shader;
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader) {
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);
		if (geometryShader)
		{
			glAttachShader(this->id, geometryShader);
		}
		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << "\n";
			cout << infoLog << "\n";
		}
		glUseProgram(0);
	}


public:
	
	//Constructors/Destructors
	Shader(const int versionMajor, const int versionMinor, const char* vertexFile, const char* fragmentFile, const char* geometryFile = "")
		: versionMajor(versionMajor), versionMinor(versionMinor)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);
		if (geometryFile != "")
		{
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
		}
		
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

		this->linkProgram(vertexShader, geometryShader, fragmentShader);

		//End
		glUseProgram(0);
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

	~Shader() {
		glDeleteProgram(this->id);
	}

	void use() {
		glUseProgram(this->id);
	}

	void unUse() {
		glUseProgram(0);
	}

	void set1i(GLint value, const GLchar* name) {
		this->use();
		glUniform1i(glGetUniformLocation(this->id, name), value);
		this->unUse();
	}

	void setVec1f(GLfloat value, const GLchar* name) {
		this->use();
		glUniform1f(glGetUniformLocation(this->id, name), value);
		this->unUse();
	}

	void setVec2f(glm::fvec2 value, const GLchar* name) {
		this->use();
		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unUse();
	}

	void setVec3f(glm::fvec3 value, const GLchar* name) {
		this->use();
		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unUse();
	}

	void setVec4f(glm::fvec4 value, const GLchar* name) {
		this->use();
		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unUse();
	}

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE) {
		this->use();
		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
		this->unUse();
	}

	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose  = GL_FALSE) {
		this->use();
		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
		this->unUse();
	}



	//Set Uniform Functions


};
