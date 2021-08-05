#pragma once

#include <glm/glm.hpp>
#include "enums/movement-direction.h"
#include <glm/gtc/matrix_transform.hpp>
#include "key-codes.h"

namespace Core
{
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 10.0f;
    const float FOV = 45.0f;

    class Camera {
    private:
        glm::vec3 _position;
        glm::vec3 _front;
        glm::vec3 _up;
        glm::vec3 _right;
        glm::vec3 _worldUp;

        float _yaw;
        float _pitch;

        float _movementSpeed;
        float _mouseSensitivity;
        float _fov;

        bool _mouseInitialized = false;
        glm::vec2 _lastMousePosition;

        void processMovement();
        void processMouseLook();

        void updateCameraVectors();
    public:
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        glm::mat4 getViewMatrix() const;
        glm::vec3 getPosition() const;

        void update();

        inline float getFov() { return this->_fov; }
    };
}
