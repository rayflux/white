#pragma once

#include <object.h>

#include <vector>

namespace white {

struct BindGroupEntry {
};

struct BindGroup : public Object {
	std::vector<BindGroupEntry> _BindGroupEntryVec;
};

}  // namespace white
