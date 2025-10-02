#pragma once

#include <buffer.h>

#include <glm/glm.hpp>

namespace white {

enum class TextureFormat : u32 {
	RGBA32FLOAT
};

struct Texture {
	void write_RGBA32FLOAT(u32 x, u32 y, const glm::vec4 &val);

	Buffer _Buffer;
	u32 _Width;
	u32 _Height;
	TextureFormat _Format;
};

}  // namespace white
