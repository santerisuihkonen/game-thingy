#pragma once

#include <glm/glm.hpp>

namespace Core {
	// Probably should inherit gameobject or smth

	class DirectionalLight {
	public:
		DirectionalLight(glm::vec3 direction);

		glm::vec3 getDirection();
		void setDirection(glm::vec3 direction);

	private:
		glm::vec3 _direction;
	};
}