#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "key-codes.h"
#include "application.h"

namespace Core {
	class Input
	{
	public:
		static bool keyPressed(KeyCode key);

		//static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 getMousePosition();
		static float getMouseX();
		static float getMouseY();
	};
}
