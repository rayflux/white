#pragma once

#include <shader_module.h>

namespace white::shader {

class TestShader : public IShaderModule {
public:
	void vertex(ShaderContext &shader_context) override;
	void fragment(ShaderContext &shader_context) override;
};

}  // namespace white::shader
