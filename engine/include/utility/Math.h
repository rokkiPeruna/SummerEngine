#ifndef SUMMER_ENGINE_MATH_H
#define SUMMER_ENGINE_MATH_H

//External includes:
#include <glm/glm.hpp>

namespace se
{
//Typedefs for matrices
typedef glm::tmat2x2<float, glm::precision::defaultp>			Mat2f;
typedef glm::tmat2x2<int, glm::precision::defaultp>				Mat2i;
typedef glm::tmat2x2<double, glm::precision::defaultp>			Mat2d;

typedef glm::tmat3x3<float, glm::precision::defaultp>			Mat3f;
typedef glm::tmat3x3<int, glm::precision::defaultp>				Mat3i;
typedef glm::tmat3x3<double, glm::precision::defaultp>			Mat3d;

typedef glm::tmat4x4<float, glm::precision::defaultp>			Mat4f;
typedef glm::tmat4x4<int, glm::precision::defaultp>				Mat4i;
typedef glm::tmat4x4<double, glm::precision::defaultp>			Mat4d;

//Typedefs for vectors
typedef glm::tvec2<int, glm::precision::defaultp>				Vec2i;
typedef glm::tvec2<unsigned int, glm::precision::defaultp>		Vec2u;
typedef glm::tvec2<unsigned short, glm::precision::defaultp>	Vec2us;
typedef glm::tvec2<float, glm::precision::defaultp>				Vec2f;
typedef glm::tvec2<char, glm::precision::defaultp>				Vec2c;
typedef glm::tvec2<bool, glm::precision::defaultp>				Vec2b;

typedef glm::tvec3<int, glm::precision::defaultp>				Vec3i;
typedef glm::tvec3<unsigned int, glm::precision::defaultp>		Vec3u;
typedef glm::tvec3<unsigned short, glm::precision::defaultp>	Vec3us;
typedef glm::tvec3<float, glm::precision::defaultp>				Vec3f;
typedef glm::tvec3<char, glm::precision::defaultp>				Vec3c;
typedef glm::tvec3<bool, glm::precision::defaultp>				Vec3b;

typedef glm::tvec4<int, glm::precision::defaultp>				Vec4i;
typedef glm::tvec4<unsigned int, glm::precision::defaultp>		Vec4u;
typedef glm::tvec4<unsigned short, glm::precision::defaultp>	Vec4us;
typedef glm::tvec4<float, glm::precision::defaultp>				Vec4f;
typedef glm::tvec4<char, glm::precision::defaultp>				Vec4c;
typedef glm::tvec4<bool, glm::precision::defaultp>				Vec4b;


//Typedefs for mathematical functions
//
//Sin funtions
inline double	asin(double x) { return std::asin(x); }
inline double	sin(double x) { return std::sin(x); }
inline float	sinf(float x) { return std::sinf(x); }

//Cosine functions
inline double	acos(double x) { return std::acos(x); }
inline double	cos(double x) { return std::cos(x); }
inline float	cosf(float x) { return std::cosf(x); }

//Tangent functions
inline double	atan(double x) { return std::atan(x); }
inline double	tan(double x) { return std::tan(x); }
inline float	tanf(float x) { return std::tanf(x); }

//Absolute value
inline int		abs(int x) { return std::abs(x); }
inline float	abs(float x) { return std::abs(x); }
inline double	abs(double x) { return std::abs(x); }

}



#endif