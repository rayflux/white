#pragma once

#include <command_buffer.h>
#include <render_pass_encoder.h>

namespace white {

class CommandEncoder {
private:
public:
	[[nodiscard]] RenderPassEncoder begin_render_pass();
	[[nodiscard]] CommandBuffer finish();
};

}  // namespace white
