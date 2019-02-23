#pragma once

#include"NumCpp/DtypeInfo.hpp"
#include"NumCpp/Types.hpp"
#include"NumCpp/NdArray.hpp"
#include"NumCpp/Utils.hpp"
#include<algorithm>
#include<iostream>
#include<stdexcept>
#include<string>
#include<vector>

namespace nc
{
    template<typename dtype>
    class Poly1d
    {

    private:
        std::vector<dtype>      coefficients_;

    public:

        Poly1d() = default;

        Poly1d(const NdArray<dtype>& inValues, bool isRoots=false)
        {
            if (inValues.size() > DtypeInfo<uint8>::max())
            {
                std::string errStr = "Error: Poly1d: can only make a polynomial of order " + utils::num2str(DtypeInfo<uint8>::max()) + ".";
                std::cerr << errStr << std::endl;
                throw std::invalid_argument(errStr);
            }

            if (isRoots)
            {
                coefficients_.push_back(1);
                for (auto value : inValues)
                {
                    NdArray<dtype> coeffs = {-(value), static_cast<dtype>(1) };
                    *this *= Poly1d<dtype>(coeffs, !isRoots);
                }
            }
            else
            {
                for (auto value : inValues)
                {
                    coefficients_.push_back(value);
                }
            }
        }

        NdArray<dtype> coefficients() const
        {
            return std::move(NdArray<dtype>(coefficients_));
        }

        uint32 order() const noexcept
        {
            return static_cast<uint32>(coefficients_.size() - 1);
        }

        std::string str() const
        {
            std::string repr = "";
            uint32 power = 0;
            for (auto& coefficient : coefficients_)
            {
                repr += utils::num2str(coefficient) + " x^" + utils::num2str(power++) + " + ";
            }

            return repr;
        }

        void print() const
        {
            std::cout << *this << std::endl;
        }

        dtype operator()(dtype inValue) const noexcept
        {
            dtype polyValue = 0;
            uint8 power = 0;
            for (auto& coefficient : coefficients_)
            {
                polyValue += coefficient * utils::power(inValue, power++);
            }

            return polyValue;
        }

        Poly1d<dtype> operator+(const Poly1d<dtype>& inOtherPoly) const
        {
            return Poly1d<dtype>(*this) += inOtherPoly;
        }

        Poly1d<dtype>& operator+=(const Poly1d<dtype>& inOtherPoly)
        {
            if (this->coefficients_.size() < inOtherPoly.coefficients_.size())
            {
                for (size_t i = 0; i < coefficients_.size(); ++i)
                {
                    coefficients_[i] += inOtherPoly.coefficients_[i];
                }
                for (size_t i = coefficients_.size(); i < inOtherPoly.coefficients_.size(); ++i)
                {
                    coefficients_.push_back(inOtherPoly.coefficients_[i]);
                }
            }
            else
            {
                for (size_t i = 0; i < inOtherPoly.coefficients_.size(); ++i)
                {
                    coefficients_[i] += inOtherPoly.coefficients_[i];
                }
            }

            return *this;
        }

        Poly1d<dtype> operator-(const Poly1d<dtype>& inOtherPoly) const
        {
            return Poly1d<dtype>(*this) -= inOtherPoly;
        }

        Poly1d<dtype>& operator-=(const Poly1d<dtype>& inOtherPoly)
        {
            if (this->coefficients_.size() < inOtherPoly.coefficients_.size())
            {
                for (size_t i = 0; i < coefficients_.size(); ++i)
                {
                    coefficients_[i] -= inOtherPoly.coefficients_[i];
                }
                for (size_t i = coefficients_.size(); i < inOtherPoly.coefficients_.size(); ++i)
                {
                    coefficients_.push_back(-inOtherPoly.coefficients_[i]);
                }
            }
            else
            {
                for (size_t i = 0; i < inOtherPoly.coefficients_.size(); ++i)
                {
                    coefficients_[i] -= inOtherPoly.coefficients_[i];
                }
            }

            return *this;
        }

        Poly1d<dtype> operator*(const Poly1d<dtype>& inOtherPoly) const
        {
            return Poly1d<dtype>(*this) *= inOtherPoly;
        }

        Poly1d<dtype>& operator*=(const Poly1d<dtype>& inOtherPoly)
        {
            const uint32 finalCoefficientsSize = order() + inOtherPoly.order() + 1;
            std::vector<dtype> coeffsA(finalCoefficientsSize, 0);
            std::vector<dtype> coeffsB(finalCoefficientsSize, 0);
            std::copy(coefficients_.begin(), coefficients_.end(), coeffsA.begin());
            std::copy(inOtherPoly.coefficients_.cbegin(), inOtherPoly.coefficients_.cend(), coeffsB.begin());

            // now multiply out the coefficients
            std::vector<dtype> finalCoefficients(finalCoefficientsSize, 0);
            for (uint32 i = 0; i < finalCoefficientsSize; ++i)
            {
                for (uint32 k = 0; k <= i; ++k)
                {
                    finalCoefficients[i] += coeffsA[k] * coeffsB[i - k];
                }
            }

            this->coefficients_ = finalCoefficients;
            return *this;
        }

        Poly1d<dtype> operator^(uint32 inPower) const
        {
            return Poly1d(*this) ^= inPower;
        }

        Poly1d<dtype>& operator^=(uint32 inPower)
        {
            if (inPower == 0)
            {
                coefficients_.clear();
                coefficients_.push_back(1);
                return *this;
            }
            else if (inPower == 1)
            {
                return *this;
            }

            auto thisPoly(*this);
            for (uint32 power = 1; power < inPower; ++power)
            {
                *this *= thisPoly;
            }

            return *this;
        }

        friend std::ostream& operator<<(std::ostream& inOStream, const Poly1d<dtype>& inPoly)
        {
            inOStream << inPoly.str() << std::endl;
            return inOStream;
        }
    };

}
