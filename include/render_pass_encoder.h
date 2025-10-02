#pragma once

#include <bind_group.h>
#include <pipeline.h>
#include <type.h>

namespace white {

class RenderPassEncoder {
private:
	std::shared_ptr<BindGroup> _ActiveBindGroup;
	std::shared_ptr<Pipeline> _ActivePipeline;

public:
	void set_bind_group(const std::shared_ptr<BindGroup> &bind_group);
	void set_pipeline(const std::shared_ptr<Pipeline> &pipeline);
	void draw(u32 vertex_cnt);
	void end();
};

}  // namespace white
