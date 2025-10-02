#include <renderer.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#pragma clang diagnostic pop

namespace white {

Renderer::Renderer(u32 framebuffer_width, u32 framebuffer_height)
    : _FramebufferWidth(framebuffer_width)
    , _FramebufferHeight(framebuffer_height) {
	_Framebuffer = create_texture(_FramebufferWidth, _FramebufferHeight, TextureFormat::RGBA32FLOAT);
}

std::shared_ptr<BindGroup> Renderer::create_bind_group(const std::vector<BindGroupEntry> &bind_group_entry_vec) {
	auto bind_group = std::make_shared<BindGroup>();

	// TODO: validate binding points, and possibily reorder it
	bind_group->_BindGroupEntryVec = bind_group_entry_vec;

	return bind_group;
}

std::shared_ptr<Buffer> Renderer::create_buffer(u32 size_in_bytes) {
	auto buffer = std::make_shared<Buffer>();

	buffer->_Data.resize(size_in_bytes);

	return buffer;
}

std::shared_ptr<Texture> Renderer::create_texture(u32 width, u32 height, TextureFormat texture_format) {
	auto texture = std::make_shared<Texture>();

	u32 space_multiplier = 0;
	switch (texture_format) {
	case TextureFormat::RGBA32FLOAT: space_multiplier = 4 * 4; break;
	}

	texture->_Width = width;
	texture->_Height = height;
	texture->_Buffer._Data.resize(width * height * space_multiplier);

	return texture;
}

std::shared_ptr<Pipeline> Renderer::create_pipeline(PrimitiveType primitive_type, const std::shared_ptr<IShaderModule> &shader_module) {
	auto pipeline = std::make_shared<Pipeline>();

	pipeline->_PrimitiveType = primitive_type;
	pipeline->_ShaderModule = shader_module;

	return pipeline;
}

RenderPassEncoder Renderer::begin_render_pass(const RenderPassDescriptor &render_pass_descriptor) {
	return RenderPassEncoder{ render_pass_descriptor };
}

void Renderer::save_framebuffer_to_file(const std::string &filename) const {
	const auto &framebuffer = _Framebuffer->_Buffer._Data;

	const u32 framebuffer_quant_size_in_bytes = _FramebufferWidth * _FramebufferHeight * 4;
	std::vector<uint8_t> framebuffer_quant(framebuffer_quant_size_in_bytes);

	for (u32 y = 0; y < _FramebufferHeight; y++) {
		for (u32 x = 0; x < _FramebufferWidth; x++) {
			u32 offset = (x + (y * _FramebufferWidth)) * 4;

			for (u32 c = 0; c < 4; c++) {
				f32 channel_value = 0.0f;
				std::memcpy(&channel_value, framebuffer.data() + ((offset + c) * sizeof(f32)), sizeof(f32));
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

std::shared_ptr<Texture> Renderer::get_framebuffer() {
	return _Framebuffer;
}

}  // namespace white
