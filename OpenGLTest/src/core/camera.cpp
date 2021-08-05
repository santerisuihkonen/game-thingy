#include "camera.h"
#include "time.h"
#include "input.h"

namespace Core
{
	void Camera::updateCameraVectors()
	{
		glm::vec3 front(
			cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch)),
			sin(glm::radians(this->_pitch)),
			sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch))
		);

		this->_front = glm::normalize(front);

		this->_right = glm::normalize(glm::cross(this->_front, this->_worldUp));
		this->_up = glm::normalize(glm::cross(this->_right, this->_front));
	}

	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: _front(glm::vec3(0.0f, 0.0f, -1.0f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _fov(FOV)
	{
		this->_position = position;
		this->_worldUp = up;
		this->_yaw = yaw;
		this->_pitch = pitch;

		this->updateCameraVectors();
	}

	Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: _front(glm::vec3(0.0f, 0.0f, -1.0f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _fov(FOV)
	{
		this->_position = glm::vec3(posX, posY, posZ);
		this->_worldUp = glm::vec3(upX, upY, upZ);
		this->_yaw = yaw;
		this->_pitch = pitch;

		this->updateCameraVectors();
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return glm::lookAt(this->_position, this->_position + this->_front, this->_up);
	}

	glm::vec3 Camera::getPosition() const
	{
		return this->_position;
	}

	void Camera::update()
	{
		this->processMovement();
		this->processMouseLook();
		this->updateCameraVectors();
	}

	void Camera::processMovement()
	{
		float velocity = this->_movementSpeed * TimeManager::getDeltaTime();

		if (Input::keyPressed(Key::W))
			this->_position += this->_front * velocity;
		if (Input::keyPressed(Key::S))
			this->_position -= this->_front * velocity;
		if (Input::keyPressed(Key::A))
			this->_position -= this->_right * velocity;
		if (Input::keyPressed(Key::D))
			this->_position += this->_right * velocity;

	}

	void Camera::processMouseLook()
	{
		glm::vec2 mousePosition = Core::Input::getMousePosition();

		if (!this->_mouseInitialized) {
			this->_lastMousePosition = mousePosition;
			this->_mouseInitialized = true;
		}

		float xoffset = mousePosition.x - this->_lastMousePosition.x;
		float yoffset = this->_lastMousePosition.y - mousePosition.y;

		this->_lastMousePosition = mousePosition;

		xoffset *= this->_mouseSensitivity * Core::TimeManager::getDeltaTime();
		yoffset *= this->_mouseSensitivity * Core::TimeManager::getDeltaTime();

		this->_yaw += xoffset;
		this->_pitch += yoffset;


		if (this->_pitch > 89.0f)
			this->_pitch = 89.0f;
		if (this->_pitch < -89.0f)
			this->_pitch = -89.0f;
	}
}
