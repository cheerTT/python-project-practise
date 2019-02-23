#pragma once

#include"NumCpp/DtypeInfo.hpp"

#include<cmath>
#include<string>

namespace nc
{
    namespace utils
    {
        //============================================================================
        /// 判别两个浮点数是否严格的相等
        ///
        /// @param      inValue1
        /// @param      inValue2
        /// @param      inEpsilon
        ///
        /// @return     bool
        ///
        template<typename dtype>
        bool essentiallyEqual(dtype inValue1, dtype inValue2, dtype inEpsilon = DtypeInfo<dtype>::epsilon()) noexcept
        {
            return std::abs(inValue1 - inValue2) <= ((std::abs(inValue1) > std::abs(inValue2) ? 
                std::abs(inValue2) : std::abs(inValue1)) * inEpsilon);
        }

        //============================================================================
        /// 数字转化为字符串
        ///
        /// @param      inNumber
        ///
        /// @return     std::string
        ///
        template<typename dtype>
        static std::string num2str(dtype inNumber)
        {
            return std::to_string(inNumber);
        }

        //============================================================================
        /// 平方
        ///
        /// @param      inValue
        ///
        /// @return     squared value
        ///
        template<typename dtype>
        static dtype sqr(dtype inValue) noexcept
        {
            return inValue * inValue;
        }

        //============================================================================
        /// 输入值立方
        ///
        /// @param      inValue
        ///
        /// @return     cubed value
        ///
        template<typename dtype>
        static dtype cube(dtype inValue) noexcept
        {
            return inValue * inValue * inValue;
        }

        //============================================================================
        /// 指数运算
        ///
        /// @param      inValue
        /// @param      inPower
        ///
        /// @return     inValue raised to inPower
        ///
        template<typename dtype>
        static dtype power(dtype inValue, uint8 inPower) noexcept
        {
            if (inPower == 0)
            {
                return static_cast<dtype>(1);
            }

            dtype returnVal = inValue;
            for (uint8 exponent = 1; exponent < inPower; ++exponent)
            {
                returnVal *= inValue;
            }
            return returnVal;
        }

        //============================================================================
        /// 返回两点之间的线性插值
        ///
        /// @param      inValue1
        /// @param      inValue2
        /// @param      inPercent
        ///
        /// @return     linear interpolated point
        ///
        template<typename dtype>
        static double interp(dtype inValue1, dtype inValue2, double inPercent) noexcept
        {
            return static_cast<double>(inValue1) * (1.0 - inPercent) + static_cast<double>(inValue2) * inPercent;
        }
    }
}
