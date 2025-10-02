#pragma once

#include <primitive_type.h>
#include <shader_module.h>
#include <type.h>

#include <memory>

namespace white {

struct Pipeline {
	std::shared_ptr<IShaderModule> _ShaderModule;
	PrimitiveType _PrimitiveType;
};

}  // namespace white
