#pragma once

#include <bind_group.h>
#include <buffer.h>

#include <memory>

namespace white {

class Renderer {
private:
public:
	std::shared_ptr<BindGroup> create_bind_group();
	std::shared_ptr<Buffer> create_buffer();
};

}  // namespace white
