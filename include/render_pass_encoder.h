#pragma once

#include <bind_group.h>
#include <pipeline.h>
#include <render_pass_descriptor.h>
#include <type.h>

namespace white {

class RenderPassEncoder {
private:
	RenderPassDescriptor _RenderPassDescriptor;
	std::shared_ptr<BindGroup> _ActiveBindGroup;
	std::shared_ptr<Pipeline> _ActivePipeline;

public:
	explicit RenderPassEncoder(RenderPassDescriptor render_pass_descriptor);

	void set_bind_group(const std::shared_ptr<BindGroup> &bind_group);
	void set_pipeline(const std::shared_ptr<Pipeline> &pipeline);
	void draw(u32 vertex_cnt);
	void end();
};

}  // namespace white
