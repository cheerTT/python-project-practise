#pragma once

#include<limits>

// 判别值的类型
namespace nc
{
    //================================================================================
    ///						Holds info about the dtype
    template<typename dtype>
    class DtypeInfo
    {
    public:
        //============================================================================
        ///						For integer types: number of non-sign bits in the representation.
        ///						For floating types : number of digits(in radix base) in the mantissa
        ///
        /// @return     number of bits
        ///
        static constexpr dtype bits()
        {
            return std::numeric_limits<dtype>::digits;
        }

        //============================================================================
        ///						Machine epsilon (the difference between 1 and the least
        ///						value greater than 1 that is representable).
        ///
        /// @return     dtype
        ///
        static constexpr dtype epsilon()
        {
            return std::numeric_limits<dtype>::epsilon();
        }

        //============================================================================
        ///						True if type is integer.
        ///
        /// @return     bool
        ///
        static constexpr bool isInteger()
        {
            return std::numeric_limits<dtype>::is_integer;
        }

        //============================================================================
        ///						True if type is signed.
        ///
        /// @return     bool
        ///
        static constexpr bool isSigned()
        {
            return std::numeric_limits<dtype>::is_signed;
        }

        //============================================================================
        ///						Returns the minimum value of the dtype
        ///
        /// @return     min value
        ///
        static constexpr dtype min()
        {
            return std::numeric_limits<dtype>::min();
        }

        //============================================================================
        ///						Returns the maximum value of the dtype
        ///
        /// @return     max value
        ///
        static constexpr dtype max()
        {
            return std::numeric_limits<dtype>::max();
        }
    };
}
