#pragma once

#include <glm/ext/matrix_transform.hpp>

#include "../renderer/renderableObject.h"
#include "../camera.h"


namespace Core {
	const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
	const glm::vec3 DEFAULT_SCALE = glm::vec3(1.0f, 1.0f, 1.0f);

	class GameObject {
	private:
		glm::vec3 _position;
		glm::vec3 _scale;

		std::unique_ptr<RenderableObject> _rendererData;

	public:
		glm::vec3 getPosition() const;
		void getRotation() const;

		void setPosition(glm::vec3 position);
		void setScale(glm::vec3 scale);

		void render(Camera& camera);

		void setRendererData(RenderableObject object);

		GameObject();
		~GameObject();
	};
}
