#include <buffer.h>

namespace white {

size_t Buffer::get_size() const {
	return _Data.size();
}

f32 Buffer::get_f32(size_t offset) const {
	f32 res;
	std::memcpy(&res, _Data.data() + offset, sizeof(f32));
	return res;
}

}  // namespace white
