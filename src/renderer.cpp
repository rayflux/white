#include <renderer.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#pragma clang diagnostic pop

#include <cstring>

namespace white {

Renderer::Renderer(u32 framebuffer_width, u32 framebuffer_height)
    : _FramebufferWidth(framebuffer_width)
    , _FramebufferHeight(framebuffer_height) {
	const u32 framebuffer_size_in_bytes = _FramebufferWidth * _FramebufferHeight * 4 * sizeof(f32);  // RGBA in f32
	_Framebuffer = create_buffer(framebuffer_size_in_bytes);
}

std::shared_ptr<BindGroup> Renderer::create_bind_group(const std::vector<BindGroupEntry> &bind_group_entry_vec) {
	auto bind_group = std::make_shared<BindGroup>();

	bind_group->_BindGroupEntryVec = bind_group_entry_vec;

	return bind_group;
}

std::shared_ptr<Buffer> Renderer::create_buffer(u32 size_in_bytes) {
	auto buffer = std::make_shared<Buffer>();

	buffer->_Data.resize(size_in_bytes);

	return buffer;
}

std::shared_ptr<ShaderModule> Renderer::create_shader_module(const std::string &shader_src_path [[maybe_unused]]) {
	auto shader_module = std::make_shared<ShaderModule>();

	return shader_module;
}

std::shared_ptr<Pipeline> Renderer::create_pipeline(PrimitiveType primitive_type, const std::shared_ptr<ShaderModule> &shader_module) {
	auto pipeline = std::make_shared<Pipeline>();

	pipeline->_PrimitiveType = primitive_type;
	pipeline->_ShaderModule = shader_module;

	return pipeline;
}

RenderPassEncoder Renderer::begin_render_pass() {
	return {};
}

void Renderer::save_framebuffer_to_file(const std::string &filename) const {
	const auto &framebuffer = _Framebuffer->_Data;

	const u32 framebuffer_quant_size_in_bytes = _FramebufferWidth * _FramebufferHeight * 4;
	std::vector<uint8_t> framebuffer_quant(framebuffer_quant_size_in_bytes);

	for (u32 y = 0; y < _FramebufferHeight; y++) {
		for (u32 x = 0; x < _FramebufferWidth; x++) {
			u32 offset = (x + (y * _FramebufferWidth)) * 4;

			for (u32 c = 0; c < 4; c++) {
				float channel_value = 0.0f;
				std::memcpy(&channel_value, framebuffer.data() + (offset * sizeof(f32)) + c, sizeof(f32));
				framebuffer_quant[offset + c] = static_cast<u8>(channel_value * 255.0f);
			}
		}
	}

	stbi_flip_vertically_on_write(1);
	stbi_write_png(filename.c_str(),
	               static_cast<int>(_FramebufferWidth),
	               static_cast<int>(_FramebufferHeight),
	               4,
	               framebuffer_quant.data(),
	               0);
}

std::shared_ptr<Buffer> Renderer::get_framebuffer() {
	return _Framebuffer;
}

}  // namespace white
