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

    // copy konstruktorius
    Vector(const Vector &other)
        : data_(nullptr), size_(0), capacity_(0)
    {
        if (other.size_)
        {
            data_ = new T[other.size_];
            std::copy(other.data_, other.data_ + other.size_, data_);
            size_ = capacity_ = other.size_;
        }
    }

    // move konstruktorius
    Vector(Vector &&other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }

    // copy operatorius
    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            Vector tmp(other);
            swap(tmp);
        }
        return *this;
    }

    // move operatorius
    Vector &operator=(Vector &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    // destruktorius
    ~Vector()
    {
        delete[] data_;
    }

    // padidinti Vector konteinerio talpa
    void reserve(size_type new_cap)
    {
        if (new_cap <= capacity_)
            return;
        T *new_data = new T[new_cap];
        for (size_type i = 0; i < size_; ++i)
            new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

    // pakeisti konteinerio dydi (sumazinti/padidinti)
    void resize(size_type count)
    {
        if (count < size_)
        {
            size_ = count;
        }
        else if (count > size_)
        {
            reserve(count);
            for (size_type i = size_; i < count; ++i)
                data_[i] = T();
            size_ = count;
        }
    }

    // Istrinti konteinerio duomenis
    void clear() noexcept
    {
        size_ = 0;
    }

private:
    void grow()
    {
        size_type new_cap = capacity_ ? capacity_ * 2 : 1;
        reserve(new_cap);
    }

    void swap(Vector &other) noexcept
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    T *data_;
    size_type size_;
    size_type capacity_;
};