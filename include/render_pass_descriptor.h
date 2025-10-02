#pragma once

#include <texture.h>
#include <type.h>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace white {

enum class ColorAttachmentLoadOp {
	CLEAR,
	LOAD,
};

struct ColorAttachment {
	std::shared_ptr<Texture> _Texture;
	ColorAttachmentLoadOp _LoadOp;
	glm::vec4 _ClearValue;
};

struct RenderPassDescriptor {
	std::vector<ColorAttachment> _ColorAttachmentVec;
	u32 _ViewportWidth;
	u32 _ViewportHeight;
	u32 _ViewportTopLeftX;
	u32 _ViewportTopLeftY;
};

}  // namespace white
