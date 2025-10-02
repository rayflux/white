#include <texture.h>

namespace white {

void Texture::write_RGBA32FLOAT(u32 x, u32 y, const glm::vec4 &val) {
	const u32 offset = x + (y * _Width);
	auto *dest_addr = _Buffer._Data.data() + (offset * 4 * 4);
	std::memcpy(dest_addr, &val.x, 16);
}

}  // namespace white
