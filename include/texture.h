#pragma once

#include <buffer.h>

namespace white {

enum class TextureFormat : u32 {
	RGBA32FLOAT
};

struct Texture {
	Buffer _Buffer;
	u32 _Width;
	u32 _Height;
	TextureFormat _Format;
};

}  // namespace white
