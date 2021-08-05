#pragma once

#include <memory>

#include "../../renderer/vertex-array.h"

namespace Core {
	class Primitive {
	public:
		inline float* getVertices() const { return this->_vertices; };
		inline VertexArray* getVao() const { return this->_vao; };

	protected:
		float* _vertices;
		VertexArray* _vao;
	};
}
