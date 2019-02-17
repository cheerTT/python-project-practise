#pragma once

#include"NumCpp/Types.hpp"
#include"NumCpp/Utils.hpp"

#include<iostream>
#include<stdexcept>
#include<string>

namespace nc
{
    //================================================================================
    ///						A Class for slicing into NdArrays
    /// NdArrays切片类
    class Slice
    {
    public:
        //====================================Attributes==============================
        // 开始 结束 步长
        int32	start{0};
        int32	stop{1};
        int32	step{1};

        //============================================================================
        ///						Constructor
        ///
        Slice() = default;

        //============================================================================
        ///						Constructor
        ///
        /// @param      inStop (index not included)
        ///
        explicit Slice(int32 inStop) noexcept :
            stop(inStop)
        {};

        //============================================================================
        ///						Constructor
        ///
        /// @param          inStart
        /// @param			inStop (index not included)
        ///
        Slice(int32 inStart, int32 inStop) noexcept :
            start(inStart),
            stop(inStop)
        {};

        //============================================================================
        ///						Constructor
        ///
        /// @param      inStart
        /// @param      inStop (not included)
        /// @param      inStep
        ///
        Slice(int32 inStart, int32 inStop, int32 inStep) noexcept :
            start(inStart),
            stop(inStop),
            step(inStep)
        {};

        //============================================================================
        ///						Prints the shape to the console
        /// 切片形状输出到控制台
        ///
        /// @return     std::string
        ///
        std::string str() const
        {
            std::string out = "[" + utils::num2str(start) + ":" + utils::num2str(stop) + ":" + utils::num2str(step) + "]\n";
            return out;
        }

        //============================================================================
        ///						Prints the shape to the console
        ///
        void print()
        {
            std::cout << *this;
        }

        //============================================================================
        ///						IO operator for the Slice class
        /// 切片类的IO运算
        ///
        /// @param      inOStream
        /// @param      inSlice
        ///
        /// @return     std::ostream
        ///
        friend std::ostream& operator<<(std::ostream& inOStream, const Slice& inSlice)
        {
            inOStream << inSlice.str();
            return inOStream;
        }

        //============================================================================
        ///						Make the slice all positive and does some error checking
        /// 使切片输入具有一定的容错性
        ///
        /// @param      inArraySize
        ///
        void makePositiveAndValidate(uint32 inArraySize)
        {
            /// convert the start value
            if (start < 0)
            {
                start += inArraySize;
            }
            if (start > static_cast<int32>(inArraySize - 1))
            {
                std::string errStr = "ERROR: Invalid start value for array of size " + utils::num2str(inArraySize) + ".";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }

            /// convert the stop value
            if (stop < 0)
            {
                stop += inArraySize;
            }
            if (stop > static_cast<int32>(inArraySize))
            {
                std::string errStr = "ERROR: Invalid stop value for array of size " + utils::num2str(inArraySize) + ".";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }

            /// do some error checking
            if (start < stop)
            {
                if (step < 0)
                {
                    std::string errStr = "ERROR: Invalid slice values.";
                    std::cerr << errStr << std::endl;
                    throw std::invalid_argument(errStr);
                }
            }

            if (stop < start)
            {
                if (step > 0)
                {
                    std::string errStr = "ERROR: Invalid slice values.";
                    std::cerr << errStr << std::endl;
                    throw std::invalid_argument(errStr);
                }

                /// otherwise flip things around for my own sanity
                std::swap(start, stop);
                step *= -1;
            }
        }

        //============================================================================
        ///						Returns the number of elements that the slice contains.
        ///						be aware that this method will also make the slice all
        ///						positive!
        /// 返回切片所表示的元素
        ///
        /// @param      inArraySize
        ///
        uint32 numElements(uint32 inArraySize)
        {
            makePositiveAndValidate(inArraySize);

            uint32 num = 0;
            for (int32 i = start; i < stop; i += step)
            {
                ++num;
            }
            return num;
        }
    };
}
