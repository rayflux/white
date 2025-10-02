#pragma once

#include <shader_context.h>

namespace white {

class IShaderModule {
public:
	virtual void vertex(ShaderContext &shader_context) const = 0;
	virtual void fragment(ShaderContext &shader_context) const = 0;
};

}  // namespace white
