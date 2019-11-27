/**
 * None-WDT (id I6078)
 * Watch-Dog Timer
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace WDT {

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

}   // namespace WDT

/**
 * WDT
 * Watch-Dog Timer
 * Size: 3 bytes
 */
template <addressType BASE_ADDRESS>
struct WDT_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRL_t, 0x3C, 2, PERv> PER = {};    //< Period
        static constexpr bitfield_t<CTRL_t, 0x02, 1> ENABLE = {};    //< Enable
        static constexpr bitfield_t<CTRL_t, 0x01, 0> CEN = {};    //< Change Enable
    } CTRL = {};

    /// Windowed Mode Control - 1 bytes
    static constexpr struct WINCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<WINCTRL_t, 0x3C, 2, WPERv> WPER = {};    //< Windowed Mode Period
        static constexpr bitfield_t<WINCTRL_t, 0x02, 1> WEN = {};    //< Windowed Mode Enable
        static constexpr bitfield_t<WINCTRL_t, 0x01, 0> WCEN = {};    //< Windowed Mode Change Enable
    } WINCTRL = {};

    /// Status - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<STATUS_t, 0x01, 0> SYNCBUSY = {};    //< Syncronization busy
    } STATUS = {};

};

} // namespace device
