#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vertex-array.h"
#include "index-buffer.h"
#include <iostream>
#include <memory>
#include <glm/ext/matrix_transform.hpp>
#include "renderableObject.h"
#include "../camera.h"

namespace Core
{
#define ASSERT(x) if (!(x)) __debugbreak();

	void GLAPIENTRY debugMessageCallback(GLenum source, GLenum type, GLenum id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	class RenderableObject;

	class Renderer {
	public:
		static void init();
		static void clear();

		static void draw(RenderableObject& object, Camera& camera, glm::mat4 modelMatrix);
		////static void drawIndexed(RenderableObject& object, glm::mat4 viewMatrix);

		static void updateViewport(int width, int height);

		static void setShader();
		static void setTexture();

	};
}
