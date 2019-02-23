#pragma once

#include"NumCpp/DtypeInfo.hpp"
#include"NumCpp/Shape.hpp"
#include"NumCpp/Slice.hpp"
#include"NumCpp/Types.hpp"
#include"NumCpp/Utils.hpp"
#include"NumCpp/Constants.hpp"

#include<algorithm>
#include<cmath>
#include<deque>
#include<functional>
#include<fstream>
#include<initializer_list>
#include<iostream>
#include<numeric>
#include<set>
#include<stdexcept>
#include<string>
#include<utility>
#include<vector>

namespace nc
{
    template<typename dtype>
    class NdArray
    {
    public:

        typedef dtype*			iterator;
        typedef const dtype*	const_iterator;

    private:

        Shape			shape_{ 0, 0 };
        uint32			size_{ 0 };
        Endian          endianess_{ Endian::NATIVE };
        dtype*			array_{ nullptr };

        void deleteArray() noexcept
        {
            if (array_ != nullptr)
            {
                delete[] array_;
                array_ = nullptr;
                shape_ = Shape(0, 0);
                size_ = 0;
            }
        }

        void newArray(const Shape& inShape)
        {
            deleteArray();

            shape_ = inShape;
            size_ = inShape.size();
            endianess_ = Endian::NATIVE;
            array_ = new dtype[size_];
        }

    public:

        NdArray() = default;

        explicit NdArray(uint32 inSquareSize) :
            shape_(inSquareSize, inSquareSize),
            size_(inSquareSize * inSquareSize),
            array_(new dtype[size_])
        {};

        NdArray(uint32 inNumRows, uint32 inNumCols) :
            shape_(inNumRows, inNumCols),
            size_(inNumRows * inNumCols),
            array_(new dtype[size_])
        {};

        explicit NdArray(const Shape& inShape) :
            shape_(inShape),
            size_(shape_.size()),
            array_(new dtype[size_])
        {};

        NdArray(const std::initializer_list<dtype>& inList) :
            shape_(1, static_cast<uint32>(inList.size())),
            size_(shape_.size()),
            array_(new dtype[size_])
        {
            std::copy(inList.begin(), inList.end(), array_);
        }

        NdArray(const std::initializer_list<std::initializer_list<dtype> >& inList) :
            shape_(static_cast<uint32>(inList.size()), 0)
        {
            for (auto& list : inList)
            {
                size_ += static_cast<uint32>(list.size());

                if (shape_.cols == 0)
                {
                    shape_.cols = static_cast<uint32>(list.size());
                }
                else if (list.size() != shape_.cols)
                {
                    std::string errStr = "ERROR: NdArray::Constructor: All rows of the initializer list needs to have the same number of elements";
                    std::cerr << errStr << std::endl;
                    throw std::invalid_argument(errStr);
                }
            }

            array_ = new dtype[size_];
            uint32 row = 0;
            for (auto& list : inList)
            {
                std::copy(list.begin(), list.end(), array_ + row * shape_.cols);
                ++row;
            }
        }

        explicit NdArray(const std::vector<dtype>& inVector) :
            shape_(1, static_cast<uint32>(inVector.size())),
            size_(shape_.size()),
            array_(new dtype[size_])
        {
            std::copy(inVector.begin(), inVector.end(), array_);
        }

        explicit NdArray(const std::deque<dtype>& inDeque) :
            shape_(1, static_cast<uint32>(inDeque.size())),
            size_(shape_.size()),
            array_(new dtype[size_])
        {
            std::copy(inDeque.begin(), inDeque.end(), array_);
        }

        explicit NdArray(const std::set<dtype>& inSet) :
            shape_(1, static_cast<uint32>(inSet.size())),
            size_(shape_.size()),
            array_(new dtype[size_])
        {
            std::copy(inSet.begin(), inSet.end(), array_);
        }

        explicit NdArray(const_iterator inFirst, const_iterator inLast) :
            shape_(1, static_cast<uint32>(inLast - inFirst)),
            size_(shape_.size()),
            array_(new dtype[size_])
        {
            std::copy(inFirst, inLast, array_);
        }

        NdArray(const dtype* inBeginning, uint32 inNumBytes) :
            shape_(1, inNumBytes / sizeof(dtype)),
            size_(shape_.size()),
            array_(new dtype[size_])
        {
            for (uint32 i = 0; i < size_; ++i)
            {
                array_[i] = *(inBeginning + i);
            }
        }

        NdArray(const NdArray<dtype>& inOtherArray) :
            shape_(inOtherArray.shape_),
            size_(inOtherArray.size_),
            endianess_(inOtherArray.endianess_),
            array_(new dtype[inOtherArray.size_])
        {
            std::copy(inOtherArray.cbegin(), inOtherArray.cend(), begin());
        }

        NdArray(NdArray<dtype>&& inOtherArray) noexcept :
            shape_(inOtherArray.shape_),
            size_(inOtherArray.size_),
            endianess_(inOtherArray.endianess_),
            array_(inOtherArray.array_)
        {
            inOtherArray.shape_.rows = inOtherArray.shape_.cols = inOtherArray.size_ = 0;
            inOtherArray.array_ = nullptr;
        }

        ~NdArray()
        {
            deleteArray();
        }

        NdArray<dtype>& operator=(const NdArray<dtype>& inOtherArray)
        {
            newArray(inOtherArray.shape_);
            endianess_ = inOtherArray.endianess_;

            std::copy(inOtherArray.cbegin(), inOtherArray.cend(), begin());

            return *this;
        }

        NdArray<dtype>& operator=(dtype inValue)
        {
            std::fill(begin(), end(), inValue);

            return *this;
        }

        NdArray<dtype>& operator=(NdArray<dtype>&& inOtherArray) noexcept
        {
            if (&inOtherArray != this)
            {
                deleteArray();
                shape_ = inOtherArray.shape_;
                size_ = inOtherArray.size_;
                endianess_ = inOtherArray.endianess_;
                array_ = inOtherArray.array_;

                inOtherArray.shape_.rows = inOtherArray.shape_.cols = inOtherArray.size_ = 0;
                inOtherArray.array_ = nullptr;
            }

            return *this;
        }

        dtype& operator[](int32 inIndex) noexcept
        {
            if (inIndex < 0)
            {
                inIndex += size_;
            }

            return array_[inIndex];
        }

        const dtype& operator[](int32 inIndex) const noexcept
        {
            if (inIndex < 0)
            {
                inIndex += size_;
            }

            return array_[inIndex];
        }

        dtype& operator()(int32 inRowIndex, int32 inColIndex) noexcept
        {
            if (inRowIndex < 0)
            {
                inRowIndex += shape_.rows;
            }

            if (inColIndex < 0)
            {
                inColIndex += shape_.cols;
            }

            return array_[inRowIndex * shape_.cols + inColIndex];
        }

        const dtype& operator()(int32 inRowIndex, int32 inColIndex) const noexcept
        {
            if (inRowIndex < 0)
            {
                inRowIndex += shape_.rows;
            }

            if (inColIndex < 0)
            {
                inColIndex += shape_.cols;
            }

            return array_[inRowIndex * shape_.cols + inColIndex];
        }

        NdArray<dtype> operator[](const Slice& inSlice) const
        {
            Slice inSliceCopy(inSlice);

            uint32 counter = 0;
            NdArray<dtype> returnArray(1, inSliceCopy.numElements(size_));
            for (int32 i = inSliceCopy.start; i < inSliceCopy.stop; i += inSliceCopy.step)
            {
                returnArray[counter++] = at(i);
            }

            return std::move(returnArray);
        }

        NdArray<dtype> operator[](const NdArray<bool> inMask) const
        {
            if (inMask.shape() != shape_)
            {
                std::string errStr = "ERROR: operator[]: input inMask must have the same shape as the NdArray it will be masking.";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }

            auto indices = inMask.nonzero();
            auto outArray = NdArray<dtype>(1, indices.size());
            for (uint32 i = 0; i < indices.size(); ++i)
            {
                outArray[i] = this->operator[](indices[i]);
            }

            return std::move(outArray);
        }

        NdArray<dtype> operator()(const Slice& inRowSlice, const Slice& inColSlice) const
        {
            Slice inRowSliceCopy(inRowSlice);
            Slice inColSliceCopy(inColSlice);

            NdArray<dtype> returnArray(inRowSliceCopy.numElements(shape_.rows), inColSliceCopy.numElements(shape_.cols));

            uint32 rowCounter = 0;
            uint32 colCounter = 0;
            for (int32 row = inRowSliceCopy.start; row < inRowSliceCopy.stop; row += inRowSliceCopy.step)
            {
                for (int32 col = inColSliceCopy.start; col < inColSliceCopy.stop; col += inColSliceCopy.step)
                {
                    returnArray(rowCounter, colCounter++) = at(row, col);
                }
                colCounter = 0;
                ++rowCounter;
            }

            return std::move(returnArray);
        }

        NdArray<dtype> operator()(const Slice& inRowSlice, int32 inColIndex) const
        {
            Slice inRowSliceCopy(inRowSlice);

            NdArray<dtype> returnArray(inRowSliceCopy.numElements(shape_.rows), 1);

            uint32 rowCounter = 0;
            for (int32 row = inRowSliceCopy.start; row < inRowSliceCopy.stop; row += inRowSliceCopy.step)
            {
                returnArray(rowCounter++, 0) = at(row, inColIndex);
            }

            return std::move(returnArray);
        }

        NdArray<dtype> operator()(int32 inRowIndex, const Slice& inColSlice) const
        {
            Slice inColSliceCopy(inColSlice);

            NdArray<dtype> returnArray(1, inColSliceCopy.numElements(shape_.cols));

            uint32 colCounter = 0;
            for (int32 col = inColSliceCopy.start; col < inColSliceCopy.stop; col += inColSliceCopy.step)
            {
                returnArray(0, colCounter++) = at(inRowIndex, col);
            }

            return std::move(returnArray);
        }


        iterator begin() noexcept
        {
            return array_;
        }

        iterator begin(uint32 inRow)
        {
            if (inRow >= shape_.rows)
            {
                std::string errStr = "ERROR: NdArray::begin: input row is greater than the number of rows in the array.";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }

            return array_ + inRow * shape_.cols;
        }

        const_iterator begin() const noexcept
        {
            return cbegin();
        }

        const_iterator begin(uint32 inRow) const
        {
            return cbegin(inRow);
        }

        iterator end() noexcept
        {
            return array_ + size_;
        }

        iterator end(uint32 inRow)
        {
            if (inRow >= shape_.rows)
            {
                std::string errStr = "ERROR: NdArray::begin: input row is greater than the number of rows in the array.";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }

            return array_ + inRow * shape_.cols + shape_.cols;
        }

        const_iterator end() const noexcept
        {
            return cend();
        }

        const_iterator end(uint32 inRow) const
        {
            return cend(inRow);
        }

        const_iterator cbegin() const noexcept
        {
            return array_;
        }

        const_iterator cbegin(uint32 inRow) const
        {
            if (inRow >= shape_.rows)
            {
                std::string errStr = "ERROR: NdArray::begin: input row is greater than the number of rows in the array.";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }

            return array_ + inRow * shape_.cols;
        }

        const_iterator cend() const noexcept
        {
            return array_ + size_;
        }

        const_iterator cend(uint32 inRow) const
        {
            if (inRow >= shape_.rows)
            {
                std::string errStr = "ERROR: NdArray::begin: input row is greater than the number of rows in the array.";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }
            return array_ + inRow * shape_.cols + shape_.cols;
        }

        NdArray<bool> all(Axis inAxis = Axis::NONE) const
        {
            switch (inAxis)
            {
                case Axis::NONE:
                {
                    NdArray<bool> returnArray = { std::all_of(cbegin(), cend(),
                        [](dtype i) noexcept -> bool {return i != static_cast<dtype>(0); }) };
                    return std::move(returnArray);
                }
                case Axis::COL:
                {
                    NdArray<bool> returnArray(1, shape_.rows);
                    for (uint32 row = 0; row < shape_.rows; ++row)
                    {
                        returnArray(0, row) = std::all_of(cbegin(row), cend(row),
                            [](dtype i) noexcept -> bool {return i != static_cast<dtype>(0); });
                    }
                    return std::move(returnArray);
                }
                case Axis::ROW:
                {
                    NdArray<dtype> arrayTransposed = transpose();
                    NdArray<bool> returnArray(1, arrayTransposed.shape_.rows);
                    for (uint32 row = 0; row < arrayTransposed.shape_.rows; ++row)
                    {
                        returnArray(0, row) = std::all_of(arrayTransposed.cbegin(row), arrayTransposed.cend(row),
                            [](dtype i) noexcept -> bool {return i != static_cast<dtype>(0); });
                    }
                    return std::move(returnArray);
                }
                default:
                {
                    // this isn't actually possible, just putting this here to get rid
                    // of the compiler warning.
                    return std::move(NdArray<bool>(0));
                }
            }
        }

        NdArray<bool> any(Axis inAxis = Axis::NONE) const
        {
            switch (inAxis)
            {
                case Axis::NONE:
                {
                    NdArray<bool> returnArray = { std::any_of(cbegin(), cend(),
                        [](dtype i) noexcept -> bool {return i != static_cast<dtype>(0); }) };
                    return std::move(returnArray);
                }
                case Axis::COL:
                {
                    NdArray<bool> returnArray(1, shape_.rows);
                    for (uint32 row = 0; row < shape_.rows; ++row)
                    {
                        returnArray(0, row) = std::any_of(cbegin(row), cend(row),
                            [](dtype i) noexcept -> bool {return i != static_cast<dtype>(0); });
                    }
                    return std::move(returnArray);
                }
                case Axis::ROW:
                {
                    NdArray<dtype> arrayTransposed = transpose();
                    NdArray<bool> returnArray(1, arrayTransposed.shape_.rows);
                    for (uint32 row = 0; row < arrayTransposed.shape_.rows; ++row)
                    {
                        returnArray(0, row) = std::any_of(arrayTransposed.cbegin(row), arrayTransposed.cend(row),
                            [](dtype i) noexcept -> bool {return i != static_cast<dtype>(0); });
                    }
                    return std::move(returnArray);
                }
                default:
                {
                    // this isn't actually possible, just putting this here to get rid
                    // of the compiler warning.
                    return std::move(NdArray<bool>(0));
                }
            }
        }

        NdArray<uint32> argmax(Axis inAxis = Axis::NONE) const
        {
            switch (inAxis)
            {
                case Axis::NONE:
                {
                    NdArray<uint32> returnArray = { static_cast<uint32>(std::max_element(cbegin(), cend()) - cbegin()) };
                    return std::move(returnArray);
                }
                case Axis::COL:
                {
                    NdArray<uint32> returnArray(1, shape_.rows);
                    for (uint32 row = 0; row < shape_.rows; ++row)
                    {
                        returnArray(0, row) = static_cast<uint32>(std::max_element(cbegin(row), cend(row)) - cbegin(row));
                    }
                    return std::move(returnArray);;
                }
                case Axis::ROW:
                {
                    NdArray<dtype> arrayTransposed = transpose();
                    NdArray<uint32> returnArray(1, arrayTransposed.shape_.rows);
                    for (uint32 row = 0; row < arrayTransposed.shape_.rows; ++row)
                    {
                        returnArray(0, row) = static_cast<uint32>(std::max_element(arrayTransposed.cbegin(row),
                            arrayTransposed.cend(row)) - arrayTransposed.cbegin(row));
                    }
                    return std::move(returnArray);;
                }
                default:
                {
                    // this isn't actually possible, just putting this here to get rid
                    // of the compiler warning.
                    return std::move(NdArray<uint32>(0));
                }
            }
        }

        NdArray<uint32> argmin(Axis inAxis = Axis::NONE) const
        {
            switch (inAxis)
            {
                case Axis::NONE:
                {
                    NdArray<uint32> returnArray = { static_cast<uint32>(std::min_element(cbegin(), cend()) - cbegin()) };
                    return std::move(returnArray);;
                }
                case Axis::COL:
                {
                    NdArray<uint32> returnArray(1, shape_.rows);
                    for (uint32 row = 0; row < shape_.rows; ++row)
                    {
                        returnArray(0, row) = static_cast<uint32>(std::min_element(cbegin(row), cend(row)) - cbegin(row));
                    }
                    return std::move(returnArray);;
                }
                case Axis::ROW:
                {
                    NdArray<dtype> arrayTransposed = transpose();
                    NdArray<uint32> returnArray(1, arrayTransposed.shape_.rows);
                    for (uint32 row = 0; row < arrayTransposed.shape_.rows; ++row)
                    {
                        returnArray(0, row) = static_cast<uint32>(std::min_element(arrayTransposed.cbegin(row),
                            arrayTransposed.cend(row)) - arrayTransposed.cbegin(row));
                    }
                    return std::move(returnArray);;
                }
                default:
                {
                    // this isn't actually possible, just putting this here to get rid
                    // of the compiler warning.
                    return std::move(NdArray<uint32>(0));
                }
            }
        }

        NdArray<uint32> argsort(Axis inAxis = Axis::NONE) const
        {
            switch (inAxis)
            {
                case Axis::NONE:
                {
                    std::vector<uint32> idx(size_);
                    std::iota(idx.begin(), idx.end(), 0);
                    std::stable_sort(idx.begin(), idx.end(),
                        [this](uint32 i1, uint32 i2) noexcept -> bool {return this->array_[i1] < this->array_[i2]; });
                    return std::move(NdArray<uint32>(idx));
                }
                case Axis::COL:
                {
                    NdArray<uint32> returnArray(shape_);
                    for (uint32 row = 0; row < shape_.rows; ++row)
                    {
                        std::vector<uint32> idx(shape_.cols);
                        std::iota(idx.begin(), idx.end(), 0);
                        std::stable_sort(idx.begin(), idx.end(),
                            [this, row](uint32 i1, uint32 i2) noexcept -> bool
                        {return this->operator()(row, i1) < this->operator()(row, i2); });

                        for (uint32 col = 0; col < shape_.cols; ++col)
                        {
                            returnArray(row, col) = idx[col];
                        }
                    }
                    return std::move(returnArray);;
                }
                case Axis::ROW:
                {
                    NdArray<dtype> arrayTransposed = transpose();
                    NdArray<uint32> returnArray(shape_.cols, shape_.rows);
                    for (uint32 row = 0; row < arrayTransposed.shape_.rows; ++row)
                    {
                        std::vector<uint32> idx(arrayTransposed.shape_.cols);
                        std::iota(idx.begin(), idx.end(), 0);
                        std::stable_sort(idx.begin(), idx.end(),
                            [&arrayTransposed, row](uint32 i1, uint32 i2) noexcept -> bool
                        {return arrayTransposed(row, i1) < arrayTransposed(row, i2); });

                        for (uint32 col = 0; col < arrayTransposed.shape_.cols; ++col)
                        {
                            returnArray(row, col) = idx[col];
                        }
                    }
                    return std::move(returnArray.transpose());
                }
                default:
                {
                    // this isn't actually possible, just putting this here to get rid
                    // of the compiler warning.
                    return std::move(NdArray<uint32>(0));
                }
            }
        }

        NdArray<dtype> copy() const
        {
            return std::move(NdArray<dtype>(*this));
        }

        template<typename dtypeOut>
        NdArray<dtypeOut> dot(const NdArray<dtype>& inOtherArray) const
        {
            if (shape_ == inOtherArray.shape_ && (shape_.rows == 1 || shape_.cols == 1))
            {
                dtypeOut dotProduct = std::inner_product(cbegin(), cend(), inOtherArray.cbegin(), static_cast<dtype>(0));
                NdArray<dtypeOut> returnArray = { dotProduct };
                return std::move(returnArray);
            }
            else if (shape_.cols == inOtherArray.shape_.rows)
            {
                // 2D array, use matrix multiplication
                NdArray<dtypeOut> returnArray(shape_.rows, inOtherArray.shape_.cols);

                for (uint32 i = 0; i < shape_.rows; ++i)
                {
                    for (uint32 j = 0; j < inOtherArray.shape_.cols; ++j)
                    {
                        returnArray(i, j) = 0;
                        for (uint32 k = 0; k < inOtherArray.shape_.rows; ++k)
                        {
                            returnArray(i, j) += static_cast<dtypeOut>(this->operator()(i, k)) *
                                static_cast<dtypeOut>(inOtherArray(k, j));
                        }
                    }
                }

                return std::move(returnArray);
            }
            else
            {
                std::string errStr = "ERROR: NdArray::Array shapes of [" + utils::num2str(shape_.rows) + ", " + utils::num2str(shape_.cols) + "]";
                errStr += " and [" + utils::num2str(inOtherArray.shape_.rows) + ", " + utils::num2str(inOtherArray.shape_.cols) + "]";
                errStr += " are not consistent.";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }
        }


        bool isempty() const
        {
            return size_ == 0;
        }

        dtype item() const
        {
            if (size_ == 1)
            {
                return array_[0];
            }
            else
            {
                std::string errStr = "ERROR: NdArray::item: Can only convert an array of size 1 to a C++ scalar";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }
        }

        NdArray<dtype> max(Axis inAxis = Axis::NONE) const
        {
            switch (inAxis)
            {
                case Axis::NONE:
                {
                    NdArray<dtype> returnArray = { *std::max_element(cbegin(), cend()) };
                    return std::move(returnArray);
                }
                case Axis::COL:
                {
                    NdArray<dtype> returnArray(1, shape_.rows);
                    for (uint32 row = 0; row < shape_.rows; ++row)
                    {
                        returnArray(0, row) = *std::max_element(cbegin(row), cend(row));
                    }

                    return std::move(returnArray);
                }
                case Axis::ROW:
                {
                    NdArray<dtype> transposedArray = transpose();
                    NdArray<dtype> returnArray(1, transposedArray.shape_.rows);
                    for (uint32 row = 0; row < transposedArray.shape_.rows; ++row)
                    {
                        returnArray(0, row) = *std::max_element(transposedArray.cbegin(row), transposedArray.cend(row));
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

        NdArray<dtype> min(Axis inAxis = Axis::NONE) const
        {
            switch (inAxis)
            {
                case Axis::NONE:
                {
                    NdArray<dtype> returnArray = { *std::min_element(cbegin(), cend()) };
                    return std::move(returnArray);
                }
                case Axis::COL:
                {
                    NdArray<dtype> returnArray(1, shape_.rows);
                    for (uint32 row = 0; row < shape_.rows; ++row)
                    {
                        returnArray(0, row) = *std::min_element(cbegin(row), cend(row));
                    }

                    return std::move(returnArray);
                }
                case Axis::ROW:
                {
                    NdArray<dtype> transposedArray = transpose();
                    NdArray<dtype> returnArray(1, transposedArray.shape_.rows);
                    for (uint32 row = 0; row < transposedArray.shape_.rows; ++row)
                    {
                        returnArray(0, row) = *std::min_element(transposedArray.cbegin(row), transposedArray.cend(row));
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

        void nans()
        {
            fill(constants::nan);
        }

        uint64 nbytes() const noexcept
        {
            return static_cast<uint64>(sizeof(dtype) * size_);
        }

        void reshape(uint32 inNumRows, uint32 inNumCols)
        {
            if (inNumRows * inNumCols != size_)
            {
                std::string errStr = "ERROR: NdArray::reshape: Cannot reshape array of size " + utils::num2str(size_) + " into shape ";
                errStr += "[" + utils::num2str(inNumRows) + ", " + utils::num2str(inNumCols) + "]";
                std::cerr << errStr << std::endl;
                throw std::runtime_error(errStr);
            }

            shape_.rows = inNumRows;
            shape_.cols = inNumCols;
        }

        void reshape(const Shape& inShape)
        {
            reshape(inShape.rows, inShape.cols);
        }

        Shape shape() const noexcept
        {
            return shape_;
        }

        uint32 size() const noexcept
        {
            return size_;
        }

        std::string str() const
        {
            std::string out;
            out += "[";
            for (uint32 row = 0; row < shape_.rows; ++row)
            {
                out += "[";
                for (uint32 col = 0; col < shape_.cols; ++col)
                {
                    out += utils::num2str(this->operator()(row, col)) + ", ";
                }

                if (row == shape_.rows - 1)
                {
                    out += "]";
                }
                else
                {
                    out += "]\n";
                }
            }
            out += "]\n";
            return out;
        }

        void zeros()
        {
            fill(0);
        }

        NdArray<dtype> operator+(const NdArray<dtype>& inOtherArray) const
        {
            return std::move(NdArray<dtype>(*this) += inOtherArray);
        }

        NdArray<dtype> operator+(dtype inScalar) const
        {
            return std::move(NdArray<dtype>(*this) += inScalar);
        }

        NdArray<dtype> operator*(const NdArray<dtype>& inOtherArray) const
        {
            return std::move(NdArray<dtype>(*this) *= inOtherArray);
        }

        NdArray<dtype> operator*(dtype inScalar) const
        {
            return std::move(NdArray<dtype>(*this) *= inScalar);
        }

        friend std::ostream& operator<<(std::ostream& inOStream, const NdArray<dtype>& inArray)
        {
            inOStream << inArray.str();
            return inOStream;
        }
};
}
