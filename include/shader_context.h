#pragma once

#include <buffer.h>
#include <type.h>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace white {

struct ShaderContext {
	glm::vec4 _BuiltinPosition;
	glm::vec4 _BuiltinFragColor;
	u32 _BuiltinVertexID;

	std::vector<std::shared_ptr<Buffer>> _BoundBufferVec;
};

}  // namespace white
