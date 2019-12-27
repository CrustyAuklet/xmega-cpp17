/**
 * This header allows for expressive access to variables in program memory. This is necessary because the
 * AVR processor is a harvard architecture, and so program and data memory are in different address spaces. Newer
 * AVR processors can adapt to this with a special 24-bit pointer, but then you must deal with a variety of different
 * pointer types which can get messy in C++ with objects.
 *
 * Some code size benchmarks using different styles of storing constant data:
 * text	   data	    bss	    dec
 * 4106	    114	     26	   4246 std::array
 * 4106	    114	     26	   4246 constexpr std::array
 * 4206	     14	     26	   4246 constexpr std::array in FLASH
 * 4310	     14	     26	   4350 constexpr std::array in FLASH from init function using CTAD
 * 4206	     14	     26	   4246 constexpr std::array in FLASH from init function with explicit type
 * 4206	     14	     26	   4246 constexpr std::array in FLASH using auto and factory function
 *
 * Constant data can be generated dynamically at compile time using constexpr functions and some misdirection
 * Example:
 *      #include <array>
 *      #include "nonstd/static_vector.hpp"
 *
 *      constexpr auto make_table_impl() noexcept {
 *          constexpr int size = 10;
 *          std::experimental::fixed_capacity_vector<uint8_t, 1024> v{};
 *          for(int i = 0; i < size; ++i) {
 *              v.push_back(i*2);
 *          }
 *          return v;
 *      }
 *
 *      constexpr auto make_table() noexcept {
 *          constexpr auto data = make_table_impl();
 *          std::array<uint8_t, data.size() > table{};
 *          for(unsigned i = 0; i < data.size(); ++i) {
 *              table[i] = data[i];
 *          }
 *          return table;
 *      }
 *
 *      [[gnu::progmem]] constexpr auto test = make_table();
 */

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

    /**
     * Flash variable wrapper to allow passing of flash variables to normal functions
     * example:
     *     [[gnu::progmem]] constexpr auto test = make_table();
     *     for(const auto& n : test) {
     *         printf("%d, ", flash(n));
     *     }
     */
    template <typename T>
    class flash {
        uint16_t addr;
    public:
        static constexpr bool in_flash = true;
        constexpr flash (const T& data) noexcept : addr(reinterpret_cast<uint16_t>(&data)) {}
        operator T() const noexcept {
            if constexpr (sizeof(T) == 1) { return pgm_read_byte(addr); }
            if constexpr (sizeof(T) == 2) { return pgm_read_word(addr); }
            if constexpr (sizeof(T) == 4) { return pgm_read_dword(addr); }
        }
    };

    ///from: https://www.avrfreaks.net/forum/how-distinguish-between-sram-and-progmem-run-time
    /**
     * Flash object that owns it's storage. This requires a macro for proper declaration.
     * example:
     *     FLASH<uint8_t> data[] = { 0x13, 0x54, 0x14, 0xff };
     *
     *     //overload functions based on flash memory
     *     template<typename T>
     *     void do_something(FLASH<T>* data) { code... }
     *
     *     template<typename T>
     *     void do_something(const T* data) { code... }
     */
    #define FLASH const PROGMEM flash
    template <typename T>
    class flashvar {
    private:
        const T data;
    public:
        static constexpr bool in_flash = true;
        constexpr flashvar (T _data) noexcept : data(_data) {}
        constexpr flashvar () noexcept : data(0) {}

        operator T() const noexcept {
            if constexpr (sizeof(T) == 1) { return pgm_read_byte(&data); }
            if constexpr (sizeof(T) == 2) { return pgm_read_word(&data); }
            if constexpr (sizeof(T) == 4) { return pgm_read_dword(&data); }
        }
    };

    /**
     * this class provides a wrapper for a flash based string. THis allows function overloading
     * and easy declaration with GNU extensions
     */
    template<char... C>
    struct flash_string {
        static constexpr bool in_flash = true;
        static constexpr char value[sizeof...(C) + 1] [[gnu::progmem]] = {C..., '\0'};
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