#pragma once

#include <cstdint>
#include <avr/pgmspace.h>

#ifndef __AVR_HAVE_LPMX__
#    error "No PGMSPACE support for this MCU."
#endif

#define PGMSPACE [[gnu::progmem]]

namespace flash {

    uint8_t read(const uint8_t& p) {
        const uint16_t addr = reinterpret_cast<uint16_t>(&p);
        uint8_t byte;
        asm(
        "lpm %0, Z \n"
        : "=r"(byte)
        : "z"(addr));
        return byte;
    }

    char read(const char* p) {
        const uint16_t addr = reinterpret_cast<uint16_t>(p);
        char           byte;
        asm(
        "lpm %0, Z \n"
        : "=r"(byte)
        : "z"(addr));
        return byte;
    }

    uint16_t read(const uint16_t& p) {

        uint16_t addr = reinterpret_cast<uint16_t>(&p);
        uint16_t result;
        asm(
        "lpm %A0, Z+ \n"
        "lpm %B0, Z  \n"
        : "=r"(result), "=z"(addr)
        : "1"(addr));
        return result;
    }

    uint32_t read(const uint32_t& p) {
        uint16_t addr = reinterpret_cast<uint16_t>(&p);
        uint32_t result;
        asm("lpm %A0, Z+ \n"
            "lpm %B0, Z+ \n"
            "lpm %C0, Z+ \n"
            "lpm %D0, Z  \n"
        : "=r"(result), "=z"(addr)
        : "1"(addr));
        return result;
    }

    #define FLASH const PROGMEM flash

    template <typename T>
    class flash {
    private:
        const T data;
    public:
        constexpr flash (T _data) noexcept : data(_data) {}
        constexpr flash () noexcept : data(0) {}

        operator T() const noexcept {
            if constexpr (sizeof(T) == 1) { return pgm_read_byte(&data); }
            if constexpr (sizeof(T) == 2) { return pgm_read_word(&data); }
            if constexpr (sizeof(T) == 4) { return pgm_read_dword(&data); }
        }
    };

    /// this class provides a wrapper for a flash based string. THis allows function overloading and easy declaration with
    /// GNU extensions
    template<char... C>
    struct flash_string {
        static constexpr char value[sizeof...(C) + 1] [[gnu::progmem]] = {C..., '\0'};
        static constexpr bool in_flash = true;
        constexpr operator const char*() const { return value; }
    };

    namespace flash_literals {
        // this is a GNU extension! there is no standard conforming method to create flash string with custom operator
        // https://stackoverflow.com/questions/54278201/what-is-c20s-string-literal-operator-template
        // Refer to P0424r2 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0424r2.pdf
        // N3599 http://open-std.org/JTC1/SC22/WG21/docs/papers/2013/n3599.html
        // C++20 experimentation https://godbolt.org/z/83Hgrs
        template <typename CharT, CharT... Cs>
        constexpr flash_string<Cs...> operator ""_fstr() { return {}; }
    }
}