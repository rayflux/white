#pragma once

#include <buffer.h>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace white {

enum class ColorAttachmentLoadOp {
	CLEAR,
	LOAD,
};

struct ColorAttachment {
	std::shared_ptr<Buffer> _Buffer;
	ColorAttachmentLoadOp _LoadOp;
	glm::vec4 _ClearValue;
};

struct RenderPassDescriptor {
	std::vector<ColorAttachment> _ColorAttachmentVec;
};

}  // namespace white
