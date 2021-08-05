#pragma once

namespace Core
{
	class VertexBuffer {
	private:
		unsigned int _rendererId;

	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void set() const;
		void unset() const;
	};
}
