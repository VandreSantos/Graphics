#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Directions
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

float sensitivity{ 0.1f };
float speed{ 10.0f };

class Camera {
public:
	glm::vec3 cameraPosition{};
	glm::vec3 cameraDirection{};
	glm::vec3 cameraUp{};
	glm::vec3 sideMovement{};

	float cameraSpeed{};
	float zoom{ 45.0f };
	float fixedY{};
	float yaw{};
	float pitch{};

	Camera(glm::vec3 camPosition = glm::vec3(0.0f, 0.0f, 0.0f), float initPitch = 0.0f, float initYaw = -90.0f, glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f)) : yaw{initYaw}, pitch{ initPitch }
	{
		fixedY = camPosition.y;
		cameraPosition = camPosition;
		cameraUp = camUp;
		cameraSpeed = speed;

		setDirection();
	}

	glm::mat4 getView()
	{
		glm::mat4 view{ glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp) };
		return view;
	}

	void setMovement(Directions direction, float deltaTime)
	{
		float camSpeed = cameraSpeed * deltaTime;
		if (direction == FORWARD)
		{
			cameraPosition += camSpeed * cameraDirection;
		}
		else if (direction == BACKWARD)
		{
			cameraPosition -= camSpeed * cameraDirection;
		}
		else if (direction == RIGHT)
		{
			cameraPosition -= camSpeed * sideMovement;
		}
		else if (direction == LEFT)
		{
			cameraPosition += camSpeed * sideMovement;
		}
		cameraPosition.y = fixedY;
	}

	void setDirection(float xoffset, float yoffset, bool restrainPitch = true)
	{
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (restrainPitch)
		{
			if (pitch > 89.0f)
			{
				pitch = 89.0f;
			}
			else if (pitch < -89.0f)
			{
				pitch = -89.0f;
			}
		}
		setDirection();
	}

	void setFov(float yoffset, float zoomSens = 2.0f)
	{
		zoom += yoffset * zoomSens;
		if (zoom > 90.0f)
		{
			zoom = 90.0f;
		}
		else if (zoom < 30.0f)
		{
			zoom = 30.0f;
		}
	}
private:
	void setDirection()
	{
		glm::vec3 direction{};
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraDirection = glm::normalize(direction);

		sideMovement = glm::normalize(glm::cross(cameraUp, cameraDirection));
	}
};

#endif 
