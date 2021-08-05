#pragma once

#include "shader.h"
#include "vertex-array.h"
#include "texture.h"

namespace Core {
	class Shader;
	class VertexArray;
	class Texture;

	class RenderableObject {
	public:
		RenderableObject(Shader* shader, VertexArray* vao, Texture* textures, int vertexArrayCount);

		Shader* shader;
		VertexArray* vao;
		Texture* textures;
		int vertexArrayCount;

		void set();
	};
}
