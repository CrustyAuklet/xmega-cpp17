#pragma once

#include <cstdint>

#ifndef __AVR_HAVE_LPMX__
#    error "No PGMSPACE support for this MCU."
#endif

#define PGMSPACE [[gnu::progmem]]

namespace nonstd::flash {

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

    class uint8_flash_t {
        using address_type = uint16_t;
        const uint8_t& m_ref;
    public:
        constexpr uint8_flash_t(const uint8_t& data) : m_ref(data) {}

        operator uint8_t() const {
            return read(m_ref);
        }

    };

}