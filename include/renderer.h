#pragma once

#include <bind_group.h>
#include <buffer.h>
#include <pipeline.h>
#include <render_pass_encoder.h>
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

	RenderPassEncoder begin_render_pass();

	void save_framebuffer_to_file(const std::string &filename) const;
	[[nodiscard]] std::shared_ptr<Buffer> get_framebuffer();
};

}  // namespace white
