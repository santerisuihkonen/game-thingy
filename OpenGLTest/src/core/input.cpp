#include "input.h"

namespace Core
{
    bool Input::keyPressed(KeyCode key)
    {
        auto* window = static_cast<GLFWwindow*>(Application::getWindow().getGlfwWindow());
        auto keyState = glfwGetKey(window, static_cast<int32_t>(key));
        return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
    }

    glm::vec2 Input::getMousePosition()
    {
        auto* window = static_cast<GLFWwindow*>(Application::getWindow().getGlfwWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return { (float)x, (float)y };
    }

    float Input::getMouseX()
    {
        return Input::getMousePosition().x;
    }

    float Input::getMouseY()
    {
        return Input::getMousePosition().y;
    }

}