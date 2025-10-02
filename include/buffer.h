#pragma once

#include <type.h>

#include <vector>

namespace white {

struct Buffer {
	std::vector<u8> _Data;

	[[nodiscard]] size_t get_size() const;
	[[nodiscard]] f32 get_f32(size_t offset) const;
};

}  // namespace white
