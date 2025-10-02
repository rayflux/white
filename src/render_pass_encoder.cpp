#include <render_pass_encoder.h>

namespace white {

void RenderPassEncoder::set_bind_group(const std::shared_ptr<BindGroup> &bind_group [[maybe_unused]]) {
}

void RenderPassEncoder::set_pipeline(const std::shared_ptr<Pipeline> &pipeline [[maybe_unused]]) {
}

void RenderPassEncoder::draw(u32 vertex_cnt [[maybe_unused]]) {
}

void RenderPassEncoder::end() {
}

}  // namespace white
