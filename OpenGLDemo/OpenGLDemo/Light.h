#pragma once
#include"libs.h"

class Light {
protected:
	float intensity;
	glm::vec3 color;

	glm::vec3 ambient;
	glm::vec3 diffues;
	glm::vec3 specular;

public:
	Light(float intensity, glm::vec3 color, glm::vec3 ambient = glm::vec3(0.1f), glm::vec3 diffues = glm::vec3(0.8f),
	glm::vec3 specular = glm::vec3(1.f)) 
	{
		this->intensity = intensity;
		this->color = color;
		this->ambient = ambient;
		this->diffues = diffues;
		this->specular = specular;
	}

	~Light() {

	}

	//Functions
	//virtual void sendToShader(Shader& programID) = 0;
};

class DirLight : public Light {
protected:
	glm::vec3 direction;

public:
	DirLight(glm::vec3 direction, glm::vec3 ambient = glm::vec3(0.1f), glm::vec3 diffues = glm::vec3(0.8f),
		glm::vec3 specular = glm::vec3(1.f), float intensity = 1.f, glm::vec3 color = glm::vec3(1.f))
		: Light(intensity, color, ambient, diffues, specular)
	{
		this->direction = direction;
	}

	~DirLight() {

	}

	void setDirection(const glm::vec3 direction) {
		this->direction = direction;
	}

	void sendToShader(Shader& programID) {
		programID.setVec3f(this->direction, "dirLight.direction");
		programID.setVec1f(this->intensity, "dirLight.intensity");
		programID.setVec3f(this->color, "dirLight.color");

		programID.setVec3f(this->color, "dirLight.ambient");
		programID.setVec3f(this->color, "dirLight.diffues");
		programID.setVec3f(this->color, "dirLight.specular");
	}

};

class PointLight : public Light {

protected:
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;


public:
	PointLight(glm::vec3 position, float intensity = 1.f, glm::vec3 color = glm::vec3(1.f), 
		glm::vec3 ambient = glm::vec3(0.1f), glm::vec3 diffues = glm::vec3(0.8f), glm::vec3 specular = glm::vec3(1.f),
		float constant = 1.f, float linear = 0.045f, float quadratic = 0.00075f)
		: Light(intensity, color, ambient, diffues, specular)
	{
		this->position = position;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

	~PointLight() {

	}

	void setPosition(const glm::vec3 position) {
		this->position = position;
	}

	void sendToShader(Shader& programID, string i) {
		string pos = "pointLight[";
		pos += i;
		pos += "].position";
		const GLchar* pos2 = pos.c_str();

		string intensity = "pointLight[";
		intensity += i;
		intensity += "].intensity";
		const GLchar* intensity2 = intensity.c_str();

		string color = "pointLight[";
		color += i;
		color += "].color";
		const GLchar* color2 = color.c_str();

		string constant = "pointLight[";
		constant += i;
		constant += "].constant";
		const GLchar* constant2 = constant.c_str();

		string linear = "pointLight[";
		linear += i;
		linear += "].linear";
		const GLchar* linear2 = linear.c_str();

		string quadratic = "pointLight[";
		quadratic += i;
		quadratic += "].quadratic";
		const GLchar* quadratic2 = quadratic.c_str();

		string ambient = "pointLight[";
		ambient += i;
		ambient += "].ambient";
		const GLchar* ambient2 = ambient.c_str();

		string diffues = "pointLight[";
		diffues += i;
		diffues += "].diffues";
		const GLchar* diffues2 = diffues.c_str();

		string specular = "pointLight[";
		specular += i;
		specular += "].specular";
		const GLchar* specular2 = specular.c_str();

		programID.setVec3f(this->position, pos2);
		programID.setVec1f(this->intensity, intensity2);
		programID.setVec3f(this->color, color2);
		programID.setVec1f(this->constant, constant2);
		programID.setVec1f(this->linear, linear2);
		programID.setVec1f(this->quadratic, quadratic2);
		programID.setVec3f(this->ambient, ambient2);
		programID.setVec3f(this->specular, specular2);
	}
};

class SpotLight : public Light {
protected:
	glm::vec3  position;
	glm::vec3  direction;
	float cutOff;
	float outerCutOff;

public:
	SpotLight(glm::vec3 position, glm::vec3 direction = glm::vec3(1.f), float cutOff = glm::cos(glm::radians(12.5f)), 
		float outerCutOff = glm::cos(glm::radians(17.5f)), float intensity = 4.f, glm::vec3 color = glm::vec3(1.f),
		glm::vec3 ambient = glm::vec3(0.1f), glm::vec3 diffues = glm::vec3(0.8f), glm::vec3 specular = glm::vec3(1.f))
		: Light(intensity, color, ambient, diffues, specular)
	{
		this->position = position;
		this->direction = direction;
		this->cutOff = cutOff;
		this->outerCutOff = outerCutOff;
	}

	~SpotLight() {

	}

	void setPosition(const glm::vec3 position) {
		this->position = position;
	}

	void sendToShader(Shader& programID, string i) {
		string pos = "spotLights[";
		pos += i;
		pos += "].position";
		const GLchar* pos2 = pos.c_str();

		string direction = "spotLights[";
		direction += i;
		direction += "].direction";
		const GLchar* direction2 = direction.c_str();

		string cutOff = "spotLights[";
		cutOff += i;
		cutOff += "].cutOff";
		const GLchar* cutOff2 = cutOff.c_str();

		string outerCutOff = "spotLights[";
		outerCutOff += i;
		outerCutOff += "].outerCutOff";
		const GLchar* outerCutOff2 = outerCutOff.c_str();

		string ambient = "spotLights[";
		ambient += i;
		ambient += "].ambient";
		const GLchar* ambient2 = ambient.c_str();

		programID.setVec3f(this->position, pos2);
		programID.setVec3f(this->direction, direction2);
		programID.setVec1f(this->cutOff, cutOff2);
		programID.setVec1f(this->outerCutOff, outerCutOff2);
		programID.setVec3f(this->ambient, ambient2);
	}
};
