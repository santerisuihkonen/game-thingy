#pragma once

#include "vertex-buffer.h"
#include "vertex-buffer-layout.h"

namespace Core
{
	class VertexArray {
	private:
		unsigned int _rendererId;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void set() const;
		void unset() const;
	};
}
