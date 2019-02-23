#pragma once

#include"NumCpp/Constants.hpp"
#include"NumCpp/DtypeInfo.hpp"
#include"NumCpp/NdArray.hpp"
#include"NumCpp/Polynomial.hpp"
#include"NumCpp/Types.hpp"

#include<algorithm>
#include<bitset>
#include<cmath>
#include<fstream>
#include<functional>
#include<initializer_list>
#include<iostream>
#include<set>
#include<sstream>
#include<stdexcept>
#include<string>
#include<utility>
#include<vector>

namespace nc
{
    template<typename dtype>
    dtype abs(dtype inValue) noexcept;

    template<typename dtype>
    NdArray<dtype> abs(const NdArray<dtype>& inArray);

    template<typename dtypeOut, typename dtype>
    NdArray<dtypeOut> add(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2);

    template<typename dtype>
    NdArray<bool> all(const NdArray<dtype>& inArray, Axis inAxis = Axis::NONE);

    template<typename dtype>
    NdArray<dtype> amax(const NdArray<dtype>& inArray, Axis inAxis = Axis::NONE);

    template<typename dtype>
    NdArray<dtype> amin(const NdArray<dtype>& inArray, Axis inAxis = Axis::NONE);

    template<typename dtype>
    NdArray<bool> any(const NdArray<dtype>& inArray, Axis inAxis = Axis::NONE);

    template<typename dtype>
    NdArray<dtype> append(const NdArray<dtype>& inArray, const NdArray<dtype>& inAppendValues, Axis inAxis = Axis::NONE);

    template<typename dtype>
    NdArray<dtype> arange(dtype inStart, dtype inStop, dtype inStep = 1);

    template<typename dtype>
    NdArray<dtype> arange(dtype inStop);

    template<typename dtype>
    NdArray<dtype> arange(const Slice& inSlice);

    template<typename dtype>
    NdArray<uint32> argmax(const NdArray<dtype>& inArray, Axis inAxis = Axis::NONE);

    template<typename dtype>
    NdArray<uint32> argmin(const NdArray<dtype>& inArray, Axis inAxis = Axis::NONE);

    template<typename dtype>
    NdArray<uint32> argsort(const NdArray<dtype>& inArray, Axis inAxis = Axis::NONE);

    template<typename dtype>
    NdArray<dtype> copy(const NdArray<dtype>& inArray);

    template<typename dtypeOut, typename dtype>
    NdArray<dtypeOut> dot(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2);

    template<typename dtypeOut = double, typename dtype>
    NdArray<dtypeOut> dot(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return std::move(inArray1.template dot<dtypeOut>(inArray2));
    }

    template<typename dtype>
    NdArray<double> sin(const NdArray<dtype>& inArray)
    {
        NdArray<double> returnArray(inArray.shape());
        std::transform(inArray.cbegin(), inArray.cend(), returnArray.begin(),
                       [](dtype inValue) noexcept -> double { return sin(inValue); });

        return std::move(returnArray);
    }

    template<typename dtype>
    NdArray<dtype> copy(const NdArray<dtype>& inArray)
    {
        return std::move(NdArray<dtype>(inArray));
    }

    template<typename dtype>
    dtype abs(dtype inValue) noexcept
    {
        return std::abs(inValue);
    }

    template<typename dtype>
    NdArray<dtype> abs(const NdArray<dtype>& inArray)
    {
        NdArray<dtype> returnArray(inArray.shape());
        std::transform(inArray.cbegin(), inArray.cend(), returnArray.begin(),
                       [](dtype inValue) noexcept -> dtype { return std::abs(inValue); });

        return std::move(returnArray);
    }

    template<typename dtypeOut = double, typename dtype>
    NdArray<dtypeOut> add(const NdArray<dtype>& inArray1, const NdArray<dtype>& inArray2)
    {
        return std::move(inArray1.template astype<dtypeOut>() + inArray2.template astype<dtypeOut>());
    }

    template<typename dtype>
    NdArray<bool> all(const NdArray<dtype>& inArray, Axis inAxis)
    {
        return std::move(inArray.all(inAxis));
    }

    template<typename dtype>
    NdArray<dtype> amax(const NdArray<dtype>& inArray, Axis inAxis)
    {
        return std::move(inArray.max(inAxis));
    }

    template<typename dtype>
    NdArray<dtype> amin(const NdArray<dtype>& inArray, Axis inAxis)
    {
        return std::move(inArray.min(inAxis));
    }

    template<typename dtype>
    NdArray<bool> any(const NdArray<dtype>& inArray, Axis inAxis)
    {
        return std::move(inArray.any(inAxis));
    }

    template<typename dtype>
    NdArray<dtype> append(const NdArray<dtype>& inArray, const NdArray<dtype>& inAppendValues, Axis inAxis)
    {
        switch (inAxis)
        {
            case Axis::NONE:
            {
                NdArray<dtype> returnArray(1, inArray.size() + inAppendValues.size());
                std::copy(inArray.cbegin(), inArray.cend(), returnArray.begin());
                std::copy(inAppendValues.cbegin(), inAppendValues.cend(), returnArray.begin() + inArray.size());

                return std::move(returnArray);
            }
            case Axis::ROW:
            {
                const Shape inShape = inArray.shape();
                const Shape appendShape = inAppendValues.shape();
                if (inShape.cols != appendShape.cols)
                {
                    std::string errStr = "ERROR: append: all the input array dimensions except for the concatenation axis must match exactly";
                    std::cerr << errStr << std::endl;
                    throw std::invalid_argument(errStr);
                }

                NdArray<dtype> returnArray(inShape.rows + appendShape.rows, inShape.cols);
                std::copy(inArray.cbegin(), inArray.cend(), returnArray.begin());
                std::copy(inAppendValues.cbegin(), inAppendValues.cend(), returnArray.begin() + inArray.size());

                return std::move(returnArray);
            }
            case Axis::COL:
            {
                Shape inShape = inArray.shape();
                const Shape appendShape = inAppendValues.shape();
                if (inShape.rows != appendShape.rows)
                {
                    std::string errStr = "ERROR: append: all the input array dimensions except for the concatenation axis must match exactly";
                    std::cerr << errStr << std::endl;
                    throw std::invalid_argument(errStr);
                }

                NdArray<dtype> returnArray(inShape.rows, inShape.cols + appendShape.cols);
                for (uint32 row = 0; row < returnArray.shape().rows; ++row)
                {
                    std::copy(inArray.cbegin(row), inArray.cend(row), returnArray.begin(row));
                    std::copy(inAppendValues.cbegin(row), inAppendValues.cend(row), returnArray.begin(row) + inShape.cols);
                }

                return std::move(returnArray);
            }
            default:
            {
                // this isn't actually possible, just putting this here to get rid
                // of the compiler warning.
                return std::move(NdArray<dtype>(0));
            }
        }
    }

    template<typename dtype>
    NdArray<dtype> arange(dtype inStart, dtype inStop, dtype inStep)
    {
        if (inStep > 0 && inStop < inStart)
        {
            std::string errStr = "ERROR: arange: stop value must be larger than the start value for positive step.";
            std::cerr << errStr << std::endl;
            throw std::invalid_argument(errStr);
        }

        if (inStep < 0 && inStop > inStart)
        {
            std::string errStr = "ERROR: arange: start value must be larger than the stop value for negative step.";
            std::cerr << errStr << std::endl;
            throw std::invalid_argument(errStr);
        }

        std::vector<dtype> values;

        dtype theValue = inStart;

        if (inStep > 0)
        {
            while (theValue < inStop)
            {
                values.push_back(theValue);
                theValue += inStep;
            }
        }
        else
        {
            while (theValue > inStop)
            {
                values.push_back(theValue);
                theValue += inStep;
            }
        }

        return std::move(NdArray<dtype>(values));
    }

    template<typename dtype>
    NdArray<dtype> arange(dtype inStop)
    {
        if (inStop <= 0)
        {
            std::string errStr = "ERROR: arange: stop value must ge greater than 0.";
            std::cerr << errStr << std::endl;
            throw std::invalid_argument(errStr);
        }

        return std::move(arange<dtype>(0, inStop, 1));
    }

    template<typename dtype>
    NdArray<dtype> arange(const Slice& inSlice)
    {
        return std::move(arange<dtype>(inSlice.start, inSlice.stop, inSlice.step));
    }

    template<typename dtype>
    NdArray<uint32> argmax(const NdArray<dtype>& inArray, Axis inAxis)
    {
        return std::move(inArray.argmax(inAxis));
    }

    template<typename dtype>
    NdArray<uint32> argmin(const NdArray<dtype>& inArray, Axis inAxis)
    {
        return std::move(inArray.argmin(inAxis));
    }

    template<typename dtype>
    NdArray<uint32> argsort(const NdArray<dtype>& inArray, Axis inAxis)
    {
        return std::move(inArray.argsort(inAxis));
    }

}
