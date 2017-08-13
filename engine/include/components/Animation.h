#ifndef SE_ANIMATION_H
#define SE_ANIMATION_H

///STL includes:
#include <vector>
#include <initializer_list>

///SE includes:
#include <utility/Typedefs.h>
#include <utility/Math.h>

namespace se
{
namespace priv
{
struct AnimationFrame
{
	explicit AnimationFrame::AnimationFrame(SEint _x, SEint _y, SEint _width, SEint _heigth, SEfloat _duration, SEint _order_number)
		: x(_x)
		, y(_y)
		, width(_width)
		, heigth(_heigth)
		, ord_num(_order_number)
		, duration(_duration)
		, time(0)
	{}

	SEint x;
	SEint y;
	SEint width;
	SEint heigth;
	SEint ord_num;
	SEfloat duration;	//In seconds
	SEfloat time;			//In seconds
};

class Animation
{
public:
	explicit Animation(const std::string& animation_name, std::vector<AnimationFrame>& animation_frames);
		
	void Update(SEfloat deltaTime);

	std::string name;
	std::vector<AnimationFrame> frames;
	SEint current_frame_index;
};

}//namespace priv
}//namespace se

#endif