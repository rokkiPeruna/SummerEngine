#include <components/Animation.h>

namespace se
{
namespace priv
{
Animation::Animation(std::vector<AnimationFrame>& animation_frames)
	: frames{animation_frames}
	, current_frame_index(0)
{
	std::sort(frames.begin(), frames.end(), [&](const AnimationFrame& a, const AnimationFrame& b) {
		return a.ord_num < b.ord_num;
	});
}

void Animation::Update(SEfloat deltaTime)
{
	auto& curr_frame = frames.at(current_frame_index);
	curr_frame.time += deltaTime;
	if (curr_frame.time > curr_frame.duration)
	{
		SEint order_number = curr_frame.ord_num;
		curr_frame.time = 0;
		if (order_number == frames.size() - 1)
			current_frame_index = 0;
		else
			++current_frame_index;
	}
}

}//namespace priv
}//namespace se