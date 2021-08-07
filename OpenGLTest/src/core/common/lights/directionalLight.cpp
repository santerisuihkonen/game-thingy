#include "directionalLight.h"

namespace Core
{
	DirectionalLight::DirectionalLight(glm::vec3 direction)
		: _direction(direction)
	{
	}

	glm::vec3 DirectionalLight::getDirection()
	{
		return this->_direction;
	}

	void DirectionalLight::setDirection(glm::vec3 direction)
	{
		this->_direction = direction;
	}
}