#ifndef SE_TYPEDEFS_H
#define SE_TYPEDEFS_H

//STL includes:
#include <cstdint>
#include <limits>

//External includes:
#include <nlohmann_json/json.hpp>

//Rename current nlohmann::json::iterator. This can be changed if we ever decide to try different file format for serializing/deserializing data!
using Dataformat_itr = nlohmann::json::iterator;


//Create typedefs for data types so that the whole engine uses same types everywhere

//Basic types and their maximum and minimum values
typedef bool					SEbool;

typedef char					SEchar;
constexpr  SEchar					SEchar_max = std::numeric_limits<SEchar>::max();
constexpr SEchar					SEchar_min = std::numeric_limits<SEchar>::min();

typedef unsigned char			SEuchar;
constexpr SEuchar				SEuchar_max = std::numeric_limits<SEuchar>::max();
constexpr SEuchar				SEuchar_min = std::numeric_limits<SEuchar>::min();

typedef char16_t				SEchar16;
typedef char32_t				SEchar32;
typedef wchar_t					SEwchar;

typedef int						SEint;
constexpr SEint					SEint_max = std::numeric_limits<SEint>::max();
constexpr SEint					SEint_min = std::numeric_limits<SEint>::min();

typedef short int				SEshort;
constexpr SEshort				SEshort_max = std::numeric_limits<SEshort>::max();
constexpr SEshort				SEshort_min = std::numeric_limits<SEshort>::min();

typedef unsigned short			SEushort;
constexpr SEushort				SEushort_max = std::numeric_limits<SEushort>::max();
constexpr SEushort				SEushort_min = std::numeric_limits<SEushort>::min();

typedef long int				SElint;
constexpr SElint				SElint_max = std::numeric_limits<SElint>::max();
constexpr SElint				SElint_min = std::numeric_limits<SElint>::min();

typedef unsigned long int		SEulint;
constexpr SEulint				SEulint_max = std::numeric_limits<SEulint>::max();
constexpr SEulint				SEulint_min = std::numeric_limits<SEulint>::min();

typedef unsigned int			SEuint;
constexpr SEuint				SEuint_max = std::numeric_limits<SEuint>::max();
constexpr SEuint				SEuint_min = std::numeric_limits<SEuint>::min();

typedef uint8_t					SEuint8;
constexpr SEuint8				SEuint8_max = std::numeric_limits<SEuint8>::max();
constexpr SEuint8				SEuint8_min = std::numeric_limits<SEuint8>::min();

typedef uint16_t				SEuint16;
constexpr SEuint16				SEuint16_max = std::numeric_limits<SEuint16>::max();
constexpr SEuint16				SEuint16_min = std::numeric_limits<SEuint16>::min();

typedef int32_t					SEint32;
constexpr SEint32				SEint32_max = std::numeric_limits<SEint32>::max();
constexpr SEint32				SEint32_min = std::numeric_limits<SEint32>::min();

typedef int64_t					SEint64;
constexpr SEint64				SEint64_max = std::numeric_limits<SEint64>::max();
constexpr SEint64				SEint64_min = std::numeric_limits<SEint64>::min();

typedef unsigned long long		SEuint64;
constexpr SEuint64				SEuint64_max = std::numeric_limits<SEuint64>::max();
constexpr SEuint64				SEuint64_min = std::numeric_limits<SEuint64>::min();

typedef float					SEfloat;
constexpr SEfloat				SEfloat_max = std::numeric_limits<SEfloat>::max();
constexpr SEfloat				SEfloat_min = std::numeric_limits<SEfloat>::min();

typedef double					SEdouble;
constexpr SEdouble				SEdouble_max = std::numeric_limits<SEdouble>::max();
constexpr SEdouble				SEdouble_min = std::numeric_limits<SEdouble>::min();


#endif // !SE_TYPEDEFS_H