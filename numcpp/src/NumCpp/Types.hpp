#pragma once

#include<cstdint>

namespace nc
{
    typedef int64_t		int64;
    typedef int32_t		int32;
    typedef int16_t		int16;
    typedef int8_t		int8;
    typedef uint64_t	uint64;
    typedef uint32_t	uint32;
    typedef uint16_t	uint16;
    typedef uint8_t		uint8;

    enum class Axis { NONE = 0, ROW, COL };

    enum class Endian { NATIVE = 0, BIG, LITTLE };
}
