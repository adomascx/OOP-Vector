/**
 * @file vector.hpp
 * @brief Paprasta dinaminio masyvo (vektoriaus) implementacija
 *
 * @tparam T elemento tipas
 */
#pragma once

#if defined _WIN32 || defined __CYGWIN__
    #ifdef BUILDING_VECTOR
        #define VECTOR_API __declspec(dllexport)
    #else
        #define VECTOR_API __declspec(dllimport)
    #endif
#else // Linux / macOS etc.
    #define VECTOR_API __attribute__((visibility("default")))
#endif

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <algorithm>

namespace custm
{

    /**
     * @brief Dinaminio masyvo (vektoriaus) klasė
     *
     * @tparam T elemento tipas
     */
    template <typename T>
    class VECTOR_API vector
    {
    public:
        using size_type = std::size_t;

        /**
         * @brief Default konstruktorius
         */
        vector() noexcept
            : data_(nullptr), size_(0), capacity_(0) {}

        /**
         * @brief Kopijavimo konstruktorius
         * @param other kitas vektorius, kurio duomenys bus nukopijuoti
         */
        vector(const vector &other)
            : data_(nullptr), size_(0), capacity_(0)
        {
            if (other.size_)
            {
                data_ = new T[other.size_];
                std::copy(other.data_, other.data_ + other.size_, data_);
                size_ = capacity_ = other.size_;
            }
        }

        /**
         * @brief Perkėlimo konstruktorius
         * @param other kitas vektorius, kurio duomenys bus perimti
         */
        vector(vector &&other) noexcept
            : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
        {
            other.data_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }

        /**
         * @brief Konstruktorius iš intervalo [first, last]
         * @tparam InputIt iteratoriaus tipas
         * @param first Iteratorius į pirmą intervalo elementą
         * @param last  Iteratorius už paskutinio intervalo elemento
         */
        template <typename InputIt>
        vector(InputIt first, InputIt last)
            : data_(nullptr), size_(0), capacity_(0)
        {
            for (; first != last; ++first)
            {
                push_back(*first);
            }
        }

        /**
         * @brief Kopijavimo priskyrimo operatorius
         * @param other kitas vektorius, kurio duomenys bus nukopijuoti
         * @return Nuoroda į šį vektorių
         */
        vector &operator=(const vector &other)
        {
            if (this != &other)
            {
                vector tmp(other);
                swap(tmp);
            }
            return *this;
        }

        /**
         * @brief Perkėlimo priskyrimo operatorius
         * @param other kitas vektorius, kurio turinys bus perimtas
         * @return Nuoroda į šį vektorių
         */
        vector &operator=(vector &&other) noexcept
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

        /**
         * @brief Destruktorius, atlaisvina atmintį
         */
        ~vector()
        {
            delete[] data_;
        }

        /**
         * @brief Prideda elementą į vektoriaus pabaigą
         * @param value įdedama vertė
         */
        void push_back(const T &value)
        {
            if (size_ >= capacity_)
            {
                grow();
            }
            data_[size_++] = value;
        }

        /**
         * @brief Pašalina paskutinį elementą
         * @throws std::out_of_range jei vektorius yra tuščias
         */
        void pop_back()
        {
            if (size_ == 0)
            {
                throw std::out_of_range("pop_back from empty vector");
            }
            --size_;
        }

        /**
         * @brief Rezervuoja naują (mažiausią) talpą
         * @param new_cap nauja minimalioji talpa
         */
        void reserve(size_type new_cap)
        {
            if (new_cap <= capacity_)
                return;
            T *new_data = new T[new_cap];
            for (size_type i = 0; i < size_; ++i)
            {
                new_data[i] = std::move(data_[i]);
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_cap;
        }

        /**
         * @brief Keičia vektoriaus dydį
         * @param count naujas elementų skaičius
         */
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
                {
                    data_[i] = T();
                }
                size_ = count;
            }
        }

        /**
         * @brief Išvalo visus elementus
         */
        void clear() noexcept
        {
            size_ = 0;
        }

        /**
         * @brief Pašalina elementų intervalą [first, last)
         * @param first Iteratorius į pirmą šalinamą elementą
         * @param last  Iteratorius už paskutinio šalinamo elemento (paskutinis elementas + 1)
         * @return Iteratorius į vietą, kurioje buvo pirmas pašalintas elementas
         */
        T *erase(T *first, T *last)
        {
            size_type start = first - data_;
            size_type count = last - first;
            for (size_type i = start; i + count < size_; ++i)
            {
                data_[i] = std::move(data_[i + count]);
            }
            size_ -= count;
            return data_ + start;
        }

        /**
         * @brief Grąžina elementų skaičių
         * @return Dabartinis dydis
         */
        size_type size() const noexcept { return size_; }

        /**
         * @brief Grąžina talpą
         * @return Dabartinė talpa
         */
        size_type capacity() const noexcept { return capacity_; }

        /**
         * @brief Patikrina, ar vektorius yra tuščias
         * @return `true`, jei tuščias, kitu atveju `false`
         */
        bool empty() const noexcept { return size_ == 0; }

        /**
         * @brief Pasiekia elementą be ribų tikrinimo
         * @param idx Elemento indeksas
         * @return Nuoroda į elementą
         */
        T &operator[](size_type idx) { return data_[idx]; }
        const T &operator[](size_type idx) const noexcept { return data_[idx]; }

        /**
         * @brief Gražina iteratorių į pirmą elementą
         * @return Nuoroda į pirmą elementą
         */
        T *begin() noexcept { return data_; }
        const T *begin() const noexcept { return data_; }

        /**
         * @brief Gražina iteratorių į paskutinį elementą
         * @return Nuoroda į paskutinį elementą
         */
        T *end() noexcept { return data_ + size_; }
        const T *end() const noexcept { return data_ + size_; }

    private:
        /**
         * @brief Padidina vidinį buferį
         */
        void grow()
        {
            size_type new_cap = capacity_ ? capacity_ * 2 : 1;
            reserve(new_cap);
        }

        /**
         * @brief Sukeičia turinį su kitu vektoriumi
         * @param other Kitas vektorius
         */
        void swap(vector &other) noexcept
        {
            std::swap(data_, other.data_);
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
        }

        T *data_;
        size_type size_;
        size_type capacity_;
    };
} // namespace custm