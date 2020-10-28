#pragma once

#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

enum direction {FORWARD = 0, BACKWARD, LEFT, RIGHT, CROUCH, NOTCROUCH, JUMP
};

class Camera {
private:
	glm::mat4 viewMatrix;

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	bool isCrouching = false;

	glm::vec3 OGPos;


	void updateCameraVectors() {
		this->front.x = cos(glm::radians(this->yaw) * cos(glm::radians(this->pitch)));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw) * cos(glm::radians(this->pitch)));

		this->front = glm::normalize(this->front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	};


	bool jumping = false;
	bool falling = false;
	float jumpHeight;
	float jumpSpeed = 1.f;
	float jumpLand;

	void startJump(float height, float land) {
		jumpHeight = height;
		jumpLand = land;
		if (falling == false && jumping == false)
			jumping = true;
	}

	void jump(const float& dt) { // called every frame
		if (jumping) {
			if (this->position.y >= jumpHeight) {
				this->position.y -= jumpSpeed  * dt * 5.f;
			}
			else {
				jumping = false;
				falling = true;
			}
		}
		else if (falling) {
			if (this->position.y <= jumpLand) {
				this->position.y += jumpSpeed * dt * 5.f;
			}
			else {
				jumping = false;
				falling = false;
				isJumping = false;
			}
		}
	}

public:
	Camera(glm::vec3 Position, glm::vec3 direction, glm::vec3 worldUp) {
		this->viewMatrix = glm::mat4(1.f);

		this->movementSpeed = 10.f;
		this->sensitivity = 100.f;

		this->worldUp = worldUp;
		this->position = Position;
		this->right = glm::vec3(0.f);
		this->up = worldUp;

		this->pitch = 0.f;
		this->yaw = -90.f;
		this->roll = 0.f;

		this->updateCameraVectors();
	}

	~Camera() {

	}

	//Accessors
	const glm :: mat4 getViewMatrix() {
		this->updateCameraVectors();
		this->viewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);
			return this->viewMatrix;
	}

	const glm::vec3 getPosition() const {
		return this->position;
	}

	bool isJumping = false;

	//Functions
	void move(const float& dt, const int direction) {
		//Update position vector
		switch (direction)
		{
		case FORWARD:
			this->position += this->front * this->movementSpeed * dt;
			break;
		case BACKWARD:
			this->position -= this->front * this->movementSpeed * dt;
			break;
		case LEFT:
			this->position -= this->right * this->movementSpeed * dt;
			break;
		case RIGHT:
			this->position += this->right * this->movementSpeed * dt;
			break;
		case CROUCH:
			if (isCrouching == false)
			{
				this->position -= glm::vec3(0, 2.f, 0);
				isCrouching = true;
			}
			break;
		case NOTCROUCH:
			if (isCrouching == true)
			{
				this->position += glm::vec3(0, 2.f, 0);
				isCrouching = false;
			}
			break;
		case JUMP:
			if (isJumping == false)
			{
				startJump(0.f, 4.f);
				jump(dt);

			}
			break;
		default:
			break;
		}
	}

	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY) {
		//Update pitch, yaw, and roll
		this->pitch += static_cast<GLfloat>(-offsetY) * this->sensitivity * dt;
		this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;

		if (this->pitch >= 80.f)
		{
			this->pitch = 80.f;
		}
		else if (this->pitch < -80.f)
		{
			this->pitch = -80.f;
		}

		if (this->yaw > 360.f || this->yaw < -360.f)
		{
			this->yaw = 0.f;
		}
	}

	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY) {
		//this->updateKeyboardInout(dt, direction);
		this->updateMouseInput(dt, offsetX, offsetY);
	}

};

