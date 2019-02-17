#pragma once

#include"NumCpp/Types.hpp"
#include"NumCpp/Utils.hpp"

#include<iostream>
#include<stdexcept>
#include<string>

namespace nc
{
    //================================================================================
    ///						A Shape Class for NdArrays
    class Shape
    {
    public:
        //====================================Attributes==============================
        uint32	rows{0};
        uint32	cols{0};

        //============================================================================
        ///						Constructor
        ///
        Shape() = default;

        //============================================================================
        ///						Constructor
        ///
        /// @param      inSquareSize
        ///
        explicit Shape(uint32 inSquareSize) noexcept :
            rows(inSquareSize),
            cols(inSquareSize)
        {};

        //============================================================================
        ///						Constructor
        ///
        /// @param      inRows
        /// @param      inCols
        ///
        Shape(uint32 inRows, uint32 inCols) noexcept :
            rows(inRows),
            cols(inCols)
        {};

        //============================================================================
        /// 同一个对象运算
        ///
        /// @param      inOtherShape
        ///
        /// @return     bool
        ///
        bool operator==(const Shape& inOtherShape) const noexcept
        {
            return rows == inOtherShape.rows && cols == inOtherShape.cols;
        }

        //============================================================================
        /// 不是同一个对象的运算
        ///
        /// @param      inOtherShape
        ///
        /// @return     bool
        ///
        bool operator!=(const Shape& inOtherShape) const noexcept
        {
            return !(*this == inOtherShape);
        }

        //============================================================================
        /// 返回形状的大小
        ///
        /// @return     size
        ///
        uint32 size() const noexcept
        {
            return rows * cols;
        }

        //============================================================================
        ///						Returns whether the shape is null (constructed with the
        ///						default constructor).
        /// 判断是否为空
        ///
        /// @return     bool
        ///
        bool isnull() noexcept
        {
            return rows == 0 && cols == 0;
        }

        //============================================================================
        ///						Returns the shape as a string representation
        /// 按照形状输出具体值
        ///
        /// @return     std::string
        ///
        std::string str() const
        {
            std::string out = "[" + utils::num2str(rows) + ", " + utils::num2str(cols) + "]\n";
            return out;
        }

        //============================================================================
        ///						Prints the shape to the console
        /// 把形状在控制台输出
        ///
        void print() const
        {
            std::cout << *this;
        }

        //============================================================================
        ///						IO operator for the Shape class
        /// shape类的IO运算
        ///
        /// @param      inOStream
        /// @param      inShape
        ///
        /// @return     std::ostream
        ///
        friend std::ostream& operator<<(std::ostream& inOStream, const Shape& inShape)
        {
            inOStream << inShape.str();
            return inOStream;
        }
    };
}
