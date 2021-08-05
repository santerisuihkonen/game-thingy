#pragma once

namespace Core
{
	class IndexBuffer {
	private:
		unsigned int _rendererId;
		unsigned int _count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void set() const;
		void unset() const;

		inline unsigned int getCount() const { return this->_count; }
	};
}
