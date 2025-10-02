#include <render_pass_encoder.h>

#include <glm/glm.hpp>

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
	// std::vector<glm::vec4> processed_vertices(vertex_cnt);
	// auto &buffer = _RenderPassDescriptor._ColorAttachmentVec[0]._Texture->_Buffer._Data;

	// for (u32 i = 0; i < vertex_cnt; i++) {
	// 	// process via vertex shader...

	// 	// culling

	// 	// perspective division

	// 	// viewport transform
	// 	for (int i = 0; i < 3; i++) {
	// 		auto &x = processed_vertices[i].x;
	// 		auto &y = processed_vertices[i].y;
	// 		x = ((x + 1) * static_cast<float>(_RenderPassDescriptor._ViewportWidth) / 2.0f) + _RenderPassDescriptor._ViewportTopLeftX;
	// 		y = ((y + 1) * static_cast<float>(_RenderPassDescriptor._ViewportHeight) / 2.0f) + _RenderPassDescriptor._ViewportTopLeftY;
	// 		// depth range?
	// 	}
	// }

	// // 1. calc AABB
	// float x_min = std::numeric_limits<float>::max();
	// float x_max = std::numeric_limits<float>::min();
	// float y_min = std::numeric_limits<float>::max();
	// float y_max = std::numeric_limits<float>::min();
	// for (size_t i = 0; i < 3; i++) {
	// 	const auto &x = processed_vertices[i].x;
	// 	const auto &y = processed_vertices[i].y;

	// 	x_min = std::min(x_min, x);
	// 	y_min = std::min(y_min, y);
	// 	x_max = std::max(x_max, x);
	// 	y_max = std::max(y_max, y);
	// }
	// x_min = std::floor(x_min);
	// y_min = std::floor(y_min);
	// x_max = std::ceil(x_max);
	// y_max = std::ceil(y_max);

	// // 2. enumerate every pixel within AABB
	// // note that the origin is at the bottom left corner of the window
	// const auto x_begin = static_cast<int>(x_min);
	// const auto x_end = static_cast<int>(x_max);
	// const auto y_begin = static_cast<int>(y_min);
	// const auto y_end = static_cast<int>(y_max);
	// for (int x = x_begin; x <= x_end; x++) {
	// 	for (int y = y_begin; y <= y_end; y++) {
	// 		const float pixel_x = static_cast<float>(x) + 0.5f;
	// 		const float pixel_y = static_cast<float>(y) + 0.5f;

	// 		// test if current pixel is within the triangle
	// 		int check_mask = 0;
	// 		for (int i = 0; i < 3; i++) {
	// 			const auto &p1_x = processed_vertices[i].x;
	// 			const auto &p1_y = processed_vertices[i].y;
	// 			const auto &p2_x = processed_vertices[(i + 1) % 3].x;
	// 			const auto &p2_y = processed_vertices[(i + 1) % 3].y;
	// 			const float v1_x = p1_x - pixel_x;
	// 			const float v1_y = p1_y - pixel_y;
	// 			const float v2_x = p1_x - p2_x;
	// 			const float v2_y = p1_y - p2_y;
	// 			if ((v1_x * v2_y) - (v1_y * v2_x) >= 0.0f) {
	// 				check_mask |= 1 << i;
	// 			}
	// 		}
	// 		if (check_mask == 0 || check_mask == 7) {
	// 			pixels[(((y * WIDTH) + x) * 4) + 0] = 255;
	// 			pixels[(((y * WIDTH) + x) * 4) + 1] = 0;
	// 			pixels[(((y * WIDTH) + x) * 4) + 2] = 0;
	// 		}
	// 	}
	// }
}

void RenderPassEncoder::end() {
}

}  // namespace white
