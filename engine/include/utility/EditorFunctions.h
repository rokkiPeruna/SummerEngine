///Brief: EditorFunctions.h contains helper functions to be used in editor
#ifndef SE_EDITORFUNCTIONS_H
#define SE_EDITORFUNCTIONS_H

//STL includes:
#include <vector>

//SE includes:
#include <utility/Typedefs.h>
#include <utility/Math.h>

namespace se
{
namespace util
{
///Calculates normalized Open GL coordinates (-1.0 to 1.0 x,y) from given screen coordinates.
///1.param: Screen coordinate's x value
///2.param: Screen coordinate's y value
///3.param: Window's size as Vec2i(width, heigth)
///4.param: Camera position
///--
///Returns Vec2f containing normalized values ranging from -1.0 to 1.0 in both axis
extern Vec2f ScreenCoordsToNormOpenGLCoords(SEint scr_x, SEint scr_y, Vec2i win_size, Vec3f cam_position);


///Add points to engine's debug draw. .....

extern SEbool AddToDebugLines(const std::vector<Vec2f>& points);

}//namespace util
}//namespace se
#endif