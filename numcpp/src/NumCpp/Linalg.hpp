#pragma once

#include"NumCpp/Methods.hpp"
#include"NumCpp/NdArray.hpp"
#include"NumCpp/Shape.hpp"
#include"NumCpp/Types.hpp"

#include<cmath>
#include<iostream>
#include<initializer_list>
#include<limits>
#include<stdexcept>
#include<string>
#include<utility>

namespace nc
{
    //================================Rotations Namespace=============================
    /// Module for basic linear algebra operations
    namespace linalg
    {
        // forward declare all functions
        template<typename dtype>
        dtype det(const NdArray<dtype>& inArray);

        template<typename dtype>
        NdArray<double> inv(const NdArray<dtype>& inArray);


        //============================================================================
        // Method Description:
        ///						matrix determinant.
        ///						NOTE: can get verrrrry slow for large matrices (order > 10)
        ///
        ///                     SciPy Reference: https://docs.scipy.org/doc/scipy/reference/generated/scipy.linalg.det.html#scipy.linalg.det
        ///
        /// @param
        ///				inArray
        /// @return
        ///				matrix determinant
        ///
        template<typename dtype>
        dtype det(const NdArray<dtype>& inArray)
        {
            const Shape inShape = inArray.shape();
            if (inShape.rows != inShape.cols)
            {
                std::string errStr = "ERROR: linalg::determinant: input array must be square with size no larger than 3x3.";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }

            if (inShape.rows == 1)
            {
                return inArray.front();
            }
            else if (inShape.rows == 2)
            {
                return inArray(0, 0) * inArray(1, 1) - inArray(0, 1) * inArray(1, 0);
            }
            else if (inShape.rows == 3)
            {
                dtype aei = inArray(0, 0) * inArray(1, 1) * inArray(2, 2);
                dtype bfg = inArray(0, 1) * inArray(1, 2) * inArray(2, 0);
                dtype cdh = inArray(0, 2) * inArray(1, 0) * inArray(2, 1);
                dtype ceg = inArray(0, 2) * inArray(1, 1) * inArray(2, 0);
                dtype bdi = inArray(0, 1) * inArray(1, 0) * inArray(2, 2);
                dtype afh = inArray(0, 0) * inArray(1, 2) * inArray(2, 1);

                return aei + bfg + cdh - ceg - bdi - afh;
            }
            else
            {
                dtype determinant = 0;
                NdArray<dtype> submat(inShape.rows - 1);

                for (uint32 c = 0; c < inShape.rows; ++c)
                {
                    uint32 subi = 0;
                    for (uint32 i = 1; i < inShape.rows; ++i)
                    {
                        uint32 subj = 0;
                        for (uint32 j = 0; j < inShape.rows; ++j)
                        {
                            if (j == c)
                            {
                                continue;
                            }

                            submat(subi, subj++) = inArray(i, j);
                        }
                        ++subi;
                    }
                    determinant += (static_cast<dtype>(std::pow(-1, c)) * inArray(0, c) * det(submat));
                }

                return determinant;
            }
        }

        //============================================================================
        // Method Description:
        ///						matrix inverse
        ///
        ///                     SciPy Reference: https://docs.scipy.org/doc/scipy/reference/generated/scipy.linalg.inv.html#scipy.linalg.inv
        ///
        /// @param
        ///				inArray
        /// @return
        ///				NdArray
        ///
        template<typename dtype>
        NdArray<double> inv(const NdArray<dtype>& inArray)
        {
            const Shape inShape = inArray.shape();
            if (inShape.rows != inShape.cols)
            {
                std::string errStr = "ERROR: linalg::inv: input array must be square.";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }

            const uint32 order = inShape.rows;

            Shape newShape(inShape);
            newShape.rows *= 2;
            newShape.cols *= 2;

            NdArray<double> tempArray(newShape);
            for (uint32 row = 0; row < order; ++row)
            {
                for (uint32 col = 0; col < order; ++col)
                {
                    tempArray(row, col) = static_cast<double>(inArray(row, col));
                }
            }

            for (uint32 row = 0; row < order; ++row)
            {
                for (uint32 col = order; col < 2 * order; ++col)
                {
                    if (row == col - order)
                    {
                        tempArray(row, col) = 1.0;
                    }
                    else
                    {
                        tempArray(row, col) = 0.0;
                    }
                }
            }

            for (uint32 row = 0; row < order; ++row)
            {
                double t = tempArray(row, row);
                for (uint32 col = row; col < 2 * order; ++col)
                {
                    tempArray(row, col) /= t;
                }

                for (uint32 col = 0; col < order; ++col)
                {
                    if (row != col)
                    {
                        t = tempArray(col, row);
                        for (uint32 k = 0; k < 2 * order; ++k)
                        {
                            tempArray(col, k) -= t * tempArray(row, k);
                        }
                    }
                }
            }

            NdArray<double> returnArray(inShape);
            for (uint32 row = 0; row < order; row++)
            {
                uint32 colCounter = 0;
                for (uint32 col = order; col < 2 * order; ++col)
                {
                    returnArray(row, colCounter++) = tempArray(row, col);
                }
            }

            return std::move(returnArray);
        }

    }
}
