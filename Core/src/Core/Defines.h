#pragma once
#include <cstdint>

#include "Logger.h"

#ifdef _MSC_VER
#define DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
#define DEBUG_BREAK() __builtin_trap()
#else
#define DEBUG_BREAK() std::abort()
#endif

#ifdef NDEBUG
#define ASSERT(x, msg)
#else
#define ASSERT(x, msg)                                                                             \
    if (!(x))                                                                                      \
    {                                                                                              \
		trace::Logger::error("ASSERT FAILED: {}\nFile: {}\nLine: {}\n", msg, __FILE__, __LINE__); \
        DEBUG_BREAK();                                                                             \
    }
#endif

// -- Types ----------------------------------------------------------------------------------------
namespace trace
{
	using U8 = uint8_t;
	using U16 = uint16_t;
	using U32 = uint32_t;
	using U64 = uint64_t;
	using S8 = int8_t;
	using S16 = int16_t;
	using S32 = int32_t;
	using S64 = int64_t;
	using F32 = float;
	using F64 = double;
}