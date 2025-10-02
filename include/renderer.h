#pragma once

#include <bind_group.h>
#include <buffer.h>
#include <command_buffer.h>
#include <command_encoder.h>
#include <pipeline.h>
#include <shader_module.h>

#include <memory>
#include <string>
#include <vector>

namespace white {

class Renderer {
private:
	u32 _FramebufferWidth;
	u32 _FramebufferHeight;
	std::shared_ptr<Buffer> _Framebuffer;

public:
	Renderer(u32 framebuffer_width, u32 framebuffer_height);

	std::shared_ptr<BindGroup> create_bind_group(const std::vector<BindGroupEntry> &bind_group_entry_vec);
	std::shared_ptr<Buffer> create_buffer(u32 size_in_bytes);
	std::shared_ptr<ShaderModule> create_shader_module(const std::string &shader_src_path);
	std::shared_ptr<Pipeline> create_pipeline(PrimitiveType primitive_type, const std::shared_ptr<ShaderModule> &shader_module);
	std::shared_ptr<CommandEncoder> create_command_encoder();

	void submit(const CommandBuffer &command_buffer);
};

}  // namespace white
