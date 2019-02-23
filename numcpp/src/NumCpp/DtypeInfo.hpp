#pragma once

#include<limits>

// 判别值的类型
namespace nc
{
    template<typename dtype>
    class DtypeInfo
    {
    public:

        static constexpr dtype bits()
        {
            return std::numeric_limits<dtype>::digits;
        }

        static constexpr dtype epsilon()
        {
            return std::numeric_limits<dtype>::epsilon();
        }

        static constexpr bool isInteger()
        {
            return std::numeric_limits<dtype>::is_integer;
        }

        static constexpr bool isSigned()
        {
            return std::numeric_limits<dtype>::is_signed;
        }

        static constexpr dtype min()
        {
            return std::numeric_limits<dtype>::min();
        }

        static constexpr dtype max()
        {
            return std::numeric_limits<dtype>::max();
        }
    };
}
