#pragma once

#include <bind_group.h>
#include <buffer.h>
#include <pipeline.h>
#include <render_pass_descriptor.h>
#include <render_pass_encoder.h>
#include <shader_module.h>
#include <texture.h>

#include <memory>
#include <string>
#include <vector>

namespace white {

class Renderer {
private:
	u32 _FramebufferWidth;
	u32 _FramebufferHeight;
	std::shared_ptr<Texture> _Framebuffer;

public:
	Renderer(u32 framebuffer_width, u32 framebuffer_height);

	std::shared_ptr<BindGroup> create_bind_group(const std::vector<BindGroupEntry> &bind_group_entry_vec);
	std::shared_ptr<Buffer> create_buffer(u32 size_in_bytes);
	std::shared_ptr<Texture> create_texture(u32 width, u32 height, TextureFormat texture_format);
	std::shared_ptr<Pipeline> create_pipeline(PrimitiveType primitive_type, const std::shared_ptr<IShaderModule> &shader_module);

	RenderPassEncoder begin_render_pass(const RenderPassDescriptor &render_pass_descriptor);

	void save_framebuffer_to_file(const std::string &filename) const;
	[[nodiscard]] std::shared_ptr<Texture> get_framebuffer();
};

}  // namespace white
