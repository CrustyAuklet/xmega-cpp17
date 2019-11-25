/**
 * None-WDT (id I6078)
 * Watch-Dog Timer
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * WDT
 * Watch-Dog Timer
 * Size: 3 bytes
 */
template <addressType BASE_ADDRESS>
struct WDT_t {

    // Period setting
    enum class PERv : uint8_t {
        _8CLK = 0x00, // 8 cycles (8ms @ 3.3V)
        _16CLK = 0x01, // 16 cycles (16ms @ 3.3V)
        _32CLK = 0x02, // 32 cycles (32ms @ 3.3V)
        _64CLK = 0x03, // 64 cycles (64ms @ 3.3V)
        _128CLK = 0x04, // 128 cycles (0.128s @ 3.3V)
        _256CLK = 0x05, // 256 cycles (0.256s @ 3.3V)
        _512CLK = 0x06, // 512 cycles (0.512s @ 3.3V)
        _1KCLK = 0x07, // 1K cycles (1s @ 3.3V)
        _2KCLK = 0x08, // 2K cycles (2s @ 3.3V)
        _4KCLK = 0x09, // 4K cycles (4s @ 3.3V)
        _8KCLK = 0x0A, // 8K cycles (8s @ 3.3V)
    };

    // Closed window period
    enum class WPERv : uint8_t {
        _8CLK = 0x00, // 8 cycles (8ms @ 3.3V)
        _16CLK = 0x01, // 16 cycles (16ms @ 3.3V)
        _32CLK = 0x02, // 32 cycles (32ms @ 3.3V)
        _64CLK = 0x03, // 64 cycles (64ms @ 3.3V)
        _128CLK = 0x04, // 128 cycles (0.128s @ 3.3V)
        _256CLK = 0x05, // 256 cycles (0.256s @ 3.3V)
        _512CLK = 0x06, // 512 cycles (0.512s @ 3.3V)
        _1KCLK = 0x07, // 1K cycles (1s @ 3.3V)
        _2KCLK = 0x08, // 2K cycles (2s @ 3.3V)
        _4KCLK = 0x09, // 4K cycles (4s @ 3.3V)
        _8KCLK = 0x0A, // 8K cycles (8s @ 3.3V)
    };


    /// Control - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using PER = reg_field_t<BASE_ADDRESS + 0x0000, 0x3C, 2, PERv>;    //< Period
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x02, 1>;    //< Enable
        using CEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Change Enable
    };

    /// Windowed Mode Control - 1 bytes
    struct WINCTRL : public reg8_t<BASE_ADDRESS + 0x0001> {
        using WPER = reg_field_t<BASE_ADDRESS + 0x0001, 0x3C, 2, WPERv>;    //< Windowed Mode Period
        using WEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x02, 1>;    //< Windowed Mode Enable
        using WCEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Windowed Mode Change Enable
    };

    /// Status - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0002> {
        using SYNCBUSY = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Syncronization busy
    };
};

} // namespace device
