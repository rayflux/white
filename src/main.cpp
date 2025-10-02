#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#pragma clang diagnostic pop

#include <renderer.h>

#include <array>
#include <cstring>
#include <vector>

using namespace white;

int main() {
	// // create buffer and clear with white
	// std::vector<uint8_t> pixels(WIDTH * HEIGHT * 4, 255);

	// // rasterize a triangle
	// std::vector<Triangle> triangles;
	// triangles.push_back({ .x = { 0.0f, -0.5f, 0.5f }, .y = { 0.5f, -0.5f, -0.5f } });
	// triangles.push_back({ .x = { -1.0f, -1.0f, 0.0f }, .y = { 1.0f, -1.0f, 0.0f } });

	// for (const auto &triangle : triangles) {
	// 	std::vector<float> vertices;
	// 	for (int i = 0; i < 3; i++) {
	// 		vertices.push_back(triangle.x[i]);
	// 		vertices.push_back(triangle.y[i]);
	// 		vertices.push_back(0.0f);
	// 	}

	// 	// 0. viewport transform
	// 	for (int i = 0; i < 3; i++) {
	// 		auto &x = vertices[(i * 3) + 0];
	// 		auto &y = vertices[(i * 3) + 1];
	// 		x = (x + 1) * static_cast<float>(WIDTH) / 2.0f;
	// 		y = (y + 1) * static_cast<float>(HEIGHT) / 2.0f;
	// 	}

	// 	// 1. calc AABB
	// 	float x_min = std::numeric_limits<float>::max();
	// 	float x_max = std::numeric_limits<float>::min();
	// 	float y_min = std::numeric_limits<float>::max();
	// 	float y_max = std::numeric_limits<float>::min();
	// 	for (size_t i = 0; i < 3; i++) {
	// 		x_min = std::min(x_min, vertices[(i * 3) + 0]);
	// 		y_min = std::min(y_min, vertices[(i * 3) + 1]);
	// 		x_max = std::max(x_max, vertices[(i * 3) + 0]);
	// 		y_max = std::max(y_max, vertices[(i * 3) + 1]);
	// 	}
	// 	x_min = std::floor(x_min);
	// 	y_min = std::floor(y_min);
	// 	x_max = std::ceil(x_max);
	// 	y_max = std::ceil(y_max);

	// 	// 2. enumerate every pixel within AABB
	// 	// note that the origin is at the bottom left corner of the window
	// 	const auto x_begin = static_cast<int>(x_min);
	// 	const auto x_end = static_cast<int>(x_max);
	// 	const auto y_begin = static_cast<int>(y_min);
	// 	const auto y_end = static_cast<int>(y_max);
	// 	for (int x = x_begin; x <= x_end; x++) {
	// 		for (int y = y_begin; y <= y_end; y++) {
	// 			const float pixel_x = static_cast<float>(x) + 0.5f;
	// 			const float pixel_y = static_cast<float>(y) + 0.5f;

	// 			// test if current pixel is within the triangle
	// 			int check_mask = 0;
	// 			for (int i = 0; i < 3; i++) {
	// 				const float p1_x = vertices[(i * 3) + 0];
	// 				const float p1_y = vertices[(i * 3) + 1];
	// 				const float p2_x = vertices[((i + 1) % 3 * 3) + 0];
	// 				const float p2_y = vertices[((i + 1) % 3 * 3) + 1];
	// 				const float v1_x = p1_x - pixel_x;
	// 				const float v1_y = p1_y - pixel_y;
	// 				const float v2_x = p1_x - p2_x;
	// 				const float v2_y = p1_y - p2_y;
	// 				if (v1_x * v2_y - v1_y * v2_x >= 0.0f) {
	// 					check_mask |= 1 << i;
	// 				}
	// 			}
	// 			if (check_mask == 0 || check_mask == 7) {
	// 				pixels[(((y * WIDTH) + x) * 4) + 0] = 255;
	// 				pixels[(((y * WIDTH) + x) * 4) + 1] = 0;
	// 				pixels[(((y * WIDTH) + x) * 4) + 2] = 0;
	// 			}
	// 		}
	// 	}
	// }

	// stbi_flip_vertically_on_write(1);
	// stbi_write_png("output.png", WIDTH, HEIGHT, 4, pixels.data(), 0);

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
	auto command_encoder = renderer.create_command_encoder();

	auto render_pass = command_encoder->begin_render_pass();
	render_pass.set_bind_group(bind_group);
	render_pass.set_pipeline(pipeline);
	render_pass.draw(3);
	render_pass.end();

	auto command_buffer = command_encoder->finish();
	renderer.submit(command_buffer);

	return 0;
}
