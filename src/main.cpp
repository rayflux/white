#include <cstdio>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <vector>

constexpr size_t WIDTH = 800;
constexpr size_t HEIGHT = 600;

struct Triangle {
	float x[3];
	float y[3];
};

int main() {
	// create buffer and clear with white
	std::vector<uint8_t> pixels(WIDTH * HEIGHT * 4, 255);

	// rasterize a triangle
	std::vector<Triangle> triangles;
	triangles.push_back({ .x = { 0.0f, -0.5f, 0.5f }, .y = { 0.5f, -0.5f, -0.5f } });
	triangles.push_back({ .x = { -1.0f, -1.0f, 0.0f }, .y = { 1.0f, -1.0f, 0.0f } });

	for (const auto &triangle : triangles) {
		std::vector<float> vertices;
		for (int i = 0; i < 3; i++) {
			vertices.push_back(triangle.x[i]);
			vertices.push_back(triangle.y[i]);
			vertices.push_back(0.0f);
		}

		// 0. viewport transform
		for (int i = 0; i < 3; i++) {
			auto &x = vertices[(i * 3) + 0];
			auto &y = vertices[(i * 3) + 1];
			x = (x + 1) * static_cast<float>(WIDTH) / 2.0f;
			y = (y + 1) * static_cast<float>(HEIGHT) / 2.0f;
		}

		// 1. calc AABB
		float x_min = std::numeric_limits<float>::max();
		float x_max = std::numeric_limits<float>::min();
		float y_min = std::numeric_limits<float>::max();
		float y_max = std::numeric_limits<float>::min();
		for (size_t i = 0; i < 3; i++) {
			x_min = std::min(x_min, vertices[(i * 3) + 0]);
			y_min = std::min(y_min, vertices[(i * 3) + 1]);
			x_max = std::max(x_max, vertices[(i * 3) + 0]);
			y_max = std::max(y_max, vertices[(i * 3) + 1]);
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
				const float pixel_x = static_cast<float>(x) + 0.5f;
				const float pixel_y = static_cast<float>(y) + 0.5f;

				// test if current pixel is within the triangle
				int check_mask = 0;
				for (int i = 0; i < 3; i++) {
					const float p1_x = vertices[(i * 3) + 0];
					const float p1_y = vertices[(i * 3) + 1];
					const float p2_x = vertices[((i + 1) % 3 * 3) + 0];
					const float p2_y = vertices[((i + 1) % 3 * 3) + 1];
					const float v1_x = p1_x - pixel_x;
					const float v1_y = p1_y - pixel_y;
					const float v2_x = p1_x - p2_x;
					const float v2_y = p1_y - p2_y;
					if (v1_x * v2_y - v1_y * v2_x >= 0.0f) {
						check_mask |= 1 << i;
					}
				}
				if (check_mask == 0 || check_mask == 7) {
					pixels[(((y * WIDTH) + x) * 4) + 0] = 255;
					pixels[(((y * WIDTH) + x) * 4) + 1] = 0;
					pixels[(((y * WIDTH) + x) * 4) + 2] = 0;
				}
			}
		}
	}

	stbi_flip_vertically_on_write(1);
	stbi_write_png("output.png", WIDTH, HEIGHT, 4, pixels.data(), 0);
	// todo
	// init device
	// X create surface (plain 2d buffer)
	// create bind group (+layout)
	// create shader module
	// create pipeline (+layout)

	// (render loop begins)
	// create command encoder
	// begin render pass
	// set pipeline
	// set bindgroup
	// issue draw call
	// end render pass
	// end command encoder, get command buffer
	// submit to command queue
	// (render loop ends)

	return 0;
}
