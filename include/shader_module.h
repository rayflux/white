#pragma once

#include <shader_context.h>

namespace white {

class IShaderModule {
public:
	virtual void vertex(ShaderContext &shader_context) = 0;
	virtual void fragment(ShaderContext &shader_context) = 0;
};

}  // namespace white
