#ifndef SE_TYPEDEFS_H
#define SE_TYPEDEFS_H

//STL includes:
#include <cstdint>

//External includes:
#include <OpenGL/GLES2/gl2.h>



//Create typedefs for data types so that the whole engine uses same types everywhere

//Basic types
typedef bool					SEbool;

typedef char					SEchar;
typedef unsigned char			SEuchar;
typedef char16_t				SEchar16;
typedef char32_t				SEchar32;
typedef wchar_t					SEwchar;

typedef int						SEint;
typedef short int				SEshort;
typedef unsigned short			SEushort;
typedef long int				SElint;
typedef unsigned long int		SEulint;
typedef unsigned int			SEuint;
typedef int32_t					SEint32;
typedef int64_t					SEint64;
typedef unsigned long long		SEuint64;

typedef float					SEfloat;
typedef double					SEdouble;


#endif // !SE_TYPEDEFS_H