#pragma once

#include <object.h>
#include <type.h>

#include <cstdint>
#include <vector>

namespace white {

struct Buffer : Object {
	std::vector<u8> _Data;
};

}  // namespace white
