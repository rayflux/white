#pragma once

#include <buffer.h>
#include <type.h>

#include <memory>
#include <vector>

namespace white {

struct BindGroupEntry {
	u32 _BindingPoint;
	std::shared_ptr<Buffer> _Buffer;
};

struct BindGroup {
	std::vector<BindGroupEntry> _BindGroupEntryVec;
};

}  // namespace white
