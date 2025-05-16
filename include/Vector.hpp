#pragma once

#include "export.h"
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <algorithm>

template <typename T>
class VECTOR_API Vector
{
public:
    using size_type = std::size_t;

    // default konstruktorius
    Vector() noexcept
        : data_(nullptr), size_(0), capacity_(0) {}

    // destruktorius
    ~Vector()
    {
        delete[] data_;
    }

private:
    T *data_;
    size_type size_;
    size_type capacity_;
};

#ifdef BUILDING_VECTOR
#include "Vector-inl.hpp"
#endif