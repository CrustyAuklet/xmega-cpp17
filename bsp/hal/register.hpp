#pragma once

#include <stdint.h>
using registerType = uint8_t;
using addressType  = uint16_t;

namespace seal::registers {

template<typename reg_t, typename ...bitfield_t>
void set(reg_t reg, bitfield_t... bitfields) {
    // TODO find a way to set many fields at once
    //static_assert((std::is_same_v<reg_t,decltype (bitfields)> & ...),"");
}

template <typename T>
struct bitfield_value_t {
    T value;
    T mask;
    friend inline constexpr auto operator|(const bitfield_value_t& lhs, const bitfield_value_t& rhs) {
        return bitfield_value_t<T>{lhs.value | rhs.value, lhs.mask|rhs.mask};
    }

    friend inline constexpr auto operator|=(const bitfield_value_t& lhs, const bitfield_value_t& rhs) {
        return bitfield_value_t<T>{lhs.value | rhs.value, lhs.mask|rhs.mask};
    }

    friend inline constexpr auto operator|(int lhs, const bitfield_value_t& rhs) {
        return lhs | rhs.value;
    }
};

template <typename T, const uint32_t address>
struct reg_t {
    using type = T;
    static inline volatile T& value() noexcept {
       return *reinterpret_cast<volatile T*>(address);
    }

    inline constexpr reg_t operator=(const T& value) const noexcept {
        reg_t::value() = value;
        return reg_t<T,address>{};
    }

    template<typename U>
    inline constexpr auto operator=(const U& bit_field_value) const noexcept -> decltype (std::declval<U>().value, std::declval<U>().mask, std::declval<reg_t<T,address>>()) {
        reg_t::value() = bit_field_value.value;
        return reg_t<T,address>{};
    }

    template<typename U>
    inline constexpr auto operator|=(const U& bit_field_value) const noexcept -> decltype (std::declval<U>().value, std::declval<U>().mask, std::declval<reg_t<T,address>>()) {
        reg_t::value() = (reg_t::value() & ~bit_field_value.mask) | bit_field_value.value;
        return reg_t<T,address>{};
    }

    inline constexpr reg_t operator|=(const T& value) const noexcept {
        reg_t::value() |= value;
        return reg_t<T,address>{};
    }

    inline constexpr reg_t operator&=(const T& value) const noexcept {
        reg_t::value() &= value;
        return reg_t<T,address>{};
    }

    constexpr operator volatile T&() noexcept { return value(); }
    constexpr operator const volatile T&() const noexcept { return *reinterpret_cast<volatile T*>(address); }
};

namespace details {
    template<typename T,int start, int stop>
    constexpr T compute_mask() {
        constexpr unsigned long long all_one = ~0ull;
        if constexpr(start == stop) {
                return static_cast<T>(1<<stop);
        }
        else {
            return static_cast<T>((all_one<<(stop+1)) xor (all_one<<start));
        }
    }
}  // namespace details

template <typename reg_type, int start_index, int stop_index=start_index, typename value_t=int>
struct bitfield_t {
    using reg_t = reg_type;
    using type = typename reg_t::type;
    static constexpr const int start = std::min(start_index, stop_index);
    static constexpr const int stop = std::max(start_index, stop_index);
    static constexpr const typename reg_t::type mask = details::compute_mask<typename reg_t::type, start, stop>();

    static constexpr bitfield_value_t<type> shift(const value_t value) noexcept {
        return {(static_cast<type>(value)<<start) & mask, mask};
    }

    inline constexpr bitfield_t operator=(const value_t& value) const noexcept {
        typename reg_t::type tmp = shift(value).value;
        reg_t::value() = (reg_t::value() &  ~mask)|tmp;
        return bitfield_t<reg_t,start_index,stop_index,value_t>{};
    }

    constexpr operator value_t() noexcept { return value_t((int(reg_t::value())& mask)>>start); }
    constexpr operator value_t() const noexcept { return value_t((int(reg_t::value())& mask)>>start); }
};

namespace  {
    template <int N>
    inline unsigned long long bitfield_cat(unsigned long long value, unsigned int width) {
        return (value<<(N*width)) | bitfield_cat<N-1>(value, width);
    }

    template <>
    inline unsigned long long bitfield_cat<0>(unsigned long long value, unsigned int width) {
        return value;
    }
}  // namespace anonymous

template <std::size_t start_index, std::size_t width, typename reg_t, std::size_t count, typename value_t=int>
struct bitfield_array_t {
    static constexpr const typename reg_t::type field_mask = details::compute_mask<typename reg_t::type, start_index, start_index + width-1>();
    static constexpr const typename reg_t::type mask = details::compute_mask<typename reg_t::type, start_index, start_index + (width*count)-1>();

    template<std::size_t i>
    using field_t = bitfield_t<reg_t, (i*width)+start_index, ((i+1)*width)+start_index-1, value_t>;

    template<std::size_t i>
    static constexpr auto get() noexcept {
        static_assert ((i>=0)and(i<count), "Bitfield index is out of bounds");
        return field_t<i>{};
    }

    template<typename T>
    inline constexpr bitfield_array_t operator=(const T& value) const noexcept {
        if constexpr(std::is_integral_v<T>) {
            reg_t::value() = mask & (value << start_index);
        }
        else if constexpr(std::conjunction_v<std::is_enum<T>, std::is_same<T,value_t>>) {
            auto v = bitfield_cat<count-1>(static_cast<unsigned long long>(value), width);
            reg_t::value() = mask & (v << start_index);
        }
        return bitfield_array_t<start_index,width,reg_t,count,value_t>{};
    }

    constexpr operator typename reg_t::type() noexcept { return typename reg_t::type((int(reg_t::value())& mask)>>start_index); }
    constexpr operator typename reg_t::type() const noexcept { return typename reg_t::type((int(reg_t::value())& mask)>>start_index); }
};

}   // namespace seal::registers
