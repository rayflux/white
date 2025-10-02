#include <render_pass_encoder.h>

#include <glm/glm.hpp>

#include <iostream>
#include <limits>

namespace white {

RenderPassEncoder::RenderPassEncoder(RenderPassDescriptor render_pass_descriptor)
    : _RenderPassDescriptor(std::move(render_pass_descriptor)) {
}

void RenderPassEncoder::set_bind_group(const std::shared_ptr<BindGroup> &bind_group) {
	_ActiveBindGroup = bind_group;
}

void RenderPassEncoder::set_pipeline(const std::shared_ptr<Pipeline> &pipeline) {
	_ActivePipeline = pipeline;
}

void RenderPassEncoder::draw(u32 vertex_cnt [[maybe_unused]]) {
	std::vector<glm::vec4> processed_vertices(vertex_cnt);

	auto framebuffer = _RenderPassDescriptor._ColorAttachmentVec[0]._Texture;
	auto shader = _ActivePipeline->_ShaderModule;

	if (_ActivePipeline->_PrimitiveType != PrimitiveType::TRIANGLE) {
		std::cerr << "white: error: currently, only triangle primitive is supported!\n";
		return;
	}

	ShaderContext shader_context;
	for (auto bind_group_entry : _ActiveBindGroup->_BindGroupEntryVec) {
		shader_context._BoundBufferVec.push_back(bind_group_entry._Buffer);
	}

	for (u32 i = 0; i < vertex_cnt; i++) {
		shader_context._BuiltinVertexID = i;

		// process via vertex shader...
		shader->vertex(shader_context);
		processed_vertices[i] = shader_context._BuiltinPosition;

		// culling

		// perspective division

		// viewport transform
		auto &x = processed_vertices[i].x;
		auto &y = processed_vertices[i].y;
		x = ((x + 1) * static_cast<f32>(_RenderPassDescriptor._ViewportWidth) / 2.0f) + _RenderPassDescriptor._ViewportTopLeftX;
		y = ((y + 1) * static_cast<f32>(_RenderPassDescriptor._ViewportHeight) / 2.0f) + _RenderPassDescriptor._ViewportTopLeftY;
		// depth range?
	}

	// 1. calc AABB
	f32 x_min = std::numeric_limits<f32>::max();
	f32 x_max = std::numeric_limits<f32>::min();
	f32 y_min = std::numeric_limits<f32>::max();
	f32 y_max = std::numeric_limits<f32>::min();
	for (size_t i = 0; i < 3; i++) {
		const auto &x = processed_vertices[i].x;
		const auto &y = processed_vertices[i].y;

		x_min = std::min(x_min, x);
		y_min = std::min(y_min, y);
		x_max = std::max(x_max, x);
		y_max = std::max(y_max, y);
	}
	x_min = std::floor(x_min);
	y_min = std::floor(y_min);
	x_max = std::ceil(x_max);
	y_max = std::ceil(y_max);

	// 2. enumerate every pixel within AABB
	// note that the origin is at the bottom left corner of the window
	const auto x_begin = static_cast<int>(x_min);
	const auto x_end = static_cast<int>(x_max);
	const auto y_begin = static_cast<int>(y_min);
	const auto y_end = static_cast<int>(y_max);
	for (int x = x_begin; x <= x_end; x++) {
		for (int y = y_begin; y <= y_end; y++) {
			const f32 pixel_x = static_cast<f32>(x) + 0.5f;
			const f32 pixel_y = static_cast<f32>(y) + 0.5f;

			// test if current pixel is within the triangle
			int check_mask = 0;
			for (int i = 0; i < 3; i++) {
				const auto &p1_x = processed_vertices[i].x;
				const auto &p1_y = processed_vertices[i].y;
				const auto &p2_x = processed_vertices[(i + 1) % 3].x;
				const auto &p2_y = processed_vertices[(i + 1) % 3].y;
				const f32 v1_x = p1_x - pixel_x;
				const f32 v1_y = p1_y - pixel_y;
				const f32 v2_x = p1_x - p2_x;
				const f32 v2_y = p1_y - p2_y;
				if ((v1_x * v2_y) - (v1_y * v2_x) >= 0.0f) {
					check_mask |= 1 << i;
				}
			}
			if (check_mask == 0 || check_mask == 7) {
				shader->fragment(shader_context);
				framebuffer->write_RGBA32FLOAT(x, y, shader_context._BuiltinFragColor);
			}
		}
	}
}

void RenderPassEncoder::end() {
}

}  // namespace white
