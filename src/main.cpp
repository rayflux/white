#include <render_pass_descriptor.h>
#include <renderer.h>

#include <array>
#include <cstring>
#include <string>
#include <vector>

using namespace white;

int main() {
	Renderer renderer(800, 600);

	constexpr size_t vertices_size_in_bytes = 3 * 2 * 4;  // 3 vertices, 2 comps each, all f32 (4 bytes)
	auto vertices = renderer.create_buffer(vertices_size_in_bytes);
	std::array<f32, 6> vertices_data = {
		0.0f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};
	std::memcpy(vertices->_Data.data(), vertices_data.data(), vertices_size_in_bytes);

	std::vector<BindGroupEntry> bind_group_entry_vec;
	{
		BindGroupEntry entry;
		entry._BindingPoint = 0;
		entry._Buffer = vertices;

		bind_group_entry_vec.push_back(entry);
	}
	auto bind_group = renderer.create_bind_group(bind_group_entry_vec);

	auto shader_module = renderer.create_shader_module("assets/test.whsl");
	auto pipeline = renderer.create_pipeline(PrimitiveType::TRIANGLE, shader_module);

	auto render_pass_descriptor = RenderPassDescriptor{};
	{
		ColorAttachment attachment;
		attachment._Buffer = renderer.get_framebuffer();
		attachment._ClearValue = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		attachment._LoadOp = ColorAttachmentLoadOp::CLEAR;
		render_pass_descriptor._ColorAttachmentVec.push_back(attachment);
	}

	auto render_pass = renderer.begin_render_pass();
	render_pass.set_bind_group(bind_group);
	render_pass.set_pipeline(pipeline);
	render_pass.draw(3);
	render_pass.end();

	renderer.save_framebuffer_to_file("output.png");

	return 0;
}
