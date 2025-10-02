#pragma once

#include <shader_module.h>

namespace white::shader {

class TestShader : public IShaderModule {
public:
	void vertex(ShaderContext &shader_context) const override;
	void fragment(ShaderContext &shader_context) const override;
};

}  // namespace white::shader
