#pragma once

#include <memory>

#include "../primitives/cube.h"

namespace Core {
	class PrimitiveFactory {
	public:
		inline std::unique_ptr<Cube> createCube() const { return std::make_unique<Cube>(); }
	};
}
