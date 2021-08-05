#include "gameObject.h"

#include <glm/ext/matrix_transform.hpp>

namespace Core
{
	glm::vec3 GameObject::getPosition() const
	{
		return this->_position;
	}

	void GameObject::setPosition(glm::vec3 position)
	{
		this->_position = position;
	}

	void GameObject::setScale(glm::vec3 scale)
	{
		this->_scale = scale;
	}

	void GameObject::render(Camera& camera)
	{
		if (this->_rendererData) {
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, this->_position);
			modelMatrix = glm::scale(modelMatrix, this->_scale);

			Renderer::draw(*this->_rendererData.get(), camera, modelMatrix);
		}
	}

	void GameObject::setRendererData(RenderableObject object)
	{
		this->_rendererData = std::make_unique<RenderableObject>(object);
	}

	GameObject::GameObject() : _position(DEFAULT_POSITION), _scale(DEFAULT_SCALE)
	{
	}

	GameObject::~GameObject()
	{
	}
}
