#pragma once

#include"NumCpp/Types.hpp"
#include"NumCpp/Utils.hpp"

#include<iostream>
#include<stdexcept>
#include<string>

namespace nc
{
    class Slice
    {
    public:
        int32	start{0};
        int32	stop{1};
        int32	step{1};

        Slice() = default;

        explicit Slice(int32 inStop) noexcept :
            stop(inStop)
        {};

        Slice(int32 inStart, int32 inStop) noexcept :
            start(inStart),
            stop(inStop)
        {};

        Slice(int32 inStart, int32 inStop, int32 inStep) noexcept :
            start(inStart),
            stop(inStop),
            step(inStep)
        {};

        std::string str() const
        {
            std::string out = "[" + utils::num2str(start) + ":" + utils::num2str(stop) + ":" + utils::num2str(step) + "]\n";
            return out;
        }

        void print()
        {
            std::cout << *this;
        }

        friend std::ostream& operator<<(std::ostream& inOStream, const Slice& inSlice)
        {
            inOStream << inSlice.str();
            return inOStream;
        }

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
