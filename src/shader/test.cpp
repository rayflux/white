#include <shader/test.h>

#include <glm/glm.hpp>

namespace white::shader {

// binding point = 0, vertices, vec2

void TestShader::vertex(ShaderContext &shader_context) {
	auto &bound_buffer_vec = shader_context._BoundBufferVec;
	auto &input_vertices = bound_buffer_vec[0];
	shader_context._BuiltinPosition.x = input_vertices->get_f32(shader_context._BuiltinVertexID * 2 * sizeof(f32));
	shader_context._BuiltinPosition.y = input_vertices->get_f32((shader_context._BuiltinVertexID * 2 + 1) * sizeof(f32));
	shader_context._BuiltinPosition.z = 0.0f;
	shader_context._BuiltinPosition.w = 1.0f;
}

void TestShader::fragment(ShaderContext &shader_context) {
	shader_context._BuiltinFragColor = glm::vec4(shader_context._BuiltinPosition.x / 800.0f,
	                                             shader_context._BuiltinPosition.y / 600.0f,
	                                             0.0f,
	                                             1.0f);
}

}  // namespace white::shader
