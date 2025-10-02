#include <renderer.h>

namespace white {

Renderer::Renderer(u32 framebuffer_width, u32 framebuffer_height)
    : _FramebufferWidth(framebuffer_width)
    , _FramebufferHeight(framebuffer_height) {
	_Framebuffer = create_buffer(_FramebufferWidth * _FramebufferHeight);
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

std::shared_ptr<CommandEncoder> Renderer::create_command_encoder() {
	auto command_encoder = std::make_shared<CommandEncoder>();
	return command_encoder;
}

void Renderer::submit(const CommandBuffer &command_buffer [[maybe_unused]]) {
}

}  // namespace white
