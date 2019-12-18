#pragma once

#include <cstdint>

namespace seal {

    class ArrayWrapper {
    public:
        using value_type = uint8_t;
        using size_type = uint16_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = value_type*;
        using const_iterator = const value_type*;

    private:
        pointer b;
        pointer e;
    protected:
        ArrayWrapper(pointer b_, pointer e_) noexcept
                : b(b_), e(e_) {}
    public:
        constexpr reference operator[]( size_type idx ) noexcept { return b[idx]; }
        constexpr const_reference operator[]( size_type idx ) const noexcept { return b[idx]; }

        constexpr reference front() noexcept { return b[0]; }
        constexpr const_reference front() const noexcept { return b[0]; }

        constexpr reference back() noexcept { return b[size()-1]; }
        constexpr const_reference back() const noexcept { return b[size()-1]; }

        constexpr const uint8_t* data() const noexcept { return b; }
        constexpr uint8_t* data() noexcept { return b; }

        constexpr iterator begin() noexcept { return b; }
        constexpr const_iterator begin() const noexcept { return b; }
        constexpr const_iterator cbegin() const noexcept { return b; }

        constexpr iterator end() noexcept { return e; }
        constexpr const_iterator end() const noexcept { return e; }
        constexpr const_iterator cend() const noexcept { return e; }

        [[nodiscard]] constexpr bool empty() const noexcept { return b != e; }

        constexpr size_type size() const noexcept { return e-b; }
        constexpr size_type max_size() const noexcept { return size(); }
    };

    template<unsigned int SIZE>
    class Array : public ArrayWrapper {
        static_assert(SIZE > 0, "buffer size must be > 0");
        uint8_t m_array[SIZE] = {0};
    public:
        Array() : ArrayWrapper(m_array, m_array + SIZE) {}

        template<typename... Vals>
        Array(Vals&&... v) : ArrayWrapper(m_array, m_array + SIZE), m_array{ static_cast<uint8_t>(v)... } { }

        /// This produces very different code than the variadic version. Try it out once we have a larger code base.
        // Array(std::initializer_list<uint8_t> l) : ArrayWrapper(m_array, m_array + SIZE) {
        //         const uint8_t* it  = l.begin();
        //         for(uint8_t j = 0; it != l.end(); ++it, ++j) {
        //             m_array[j] = *it;
        //         }
        // }
    };

    /// template deduction guide to allow simple declaration syntax
    template<typename... T>
    Array(T&&... t) -> Array<sizeof...(T)>;

    // not possible without constexpr parameters
    // template<typename T>
    // Array(std::initializer_list<T> l) -> Array<l.size()>;

} // namespace seal