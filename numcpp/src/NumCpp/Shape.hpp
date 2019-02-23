#pragma once

#include"NumCpp/Types.hpp"
#include"NumCpp/Utils.hpp"

#include<iostream>
#include<stdexcept>
#include<string>

namespace nc
{

    class Shape
    {
    public:

        uint32	rows{0};
        uint32	cols{0};

        Shape() = default;

        explicit Shape(uint32 inSquareSize) noexcept :
            rows(inSquareSize),
            cols(inSquareSize)
        {};

        Shape(uint32 inRows, uint32 inCols) noexcept :
            rows(inRows),
            cols(inCols)
        {};

        bool operator==(const Shape& inOtherShape) const noexcept
        {
            return rows == inOtherShape.rows && cols == inOtherShape.cols;
        }

        bool operator!=(const Shape& inOtherShape) const noexcept
        {
            return !(*this == inOtherShape);
        }

        uint32 size() const noexcept
        {
            return rows * cols;
        }

        bool isnull() noexcept
        {
            return rows == 0 && cols == 0;
        }

        std::string str() const
        {
            std::string out = "[" + utils::num2str(rows) + ", " + utils::num2str(cols) + "]\n";
            return out;
        }

        void print() const
        {
            std::cout << *this;
        }

        friend std::ostream& operator<<(std::ostream& inOStream, const Shape& inShape)
        {
            inOStream << inShape.str();
            return inOStream;
        }
    };
}
