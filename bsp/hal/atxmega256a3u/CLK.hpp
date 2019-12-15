/**
 * XMEGAAU-CLK (id I6073)
 * Clock System
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace CLK {

    // System Clock Selection
    enum class SCLKSELv : uint8_t {
        RC2M = 0x00, // Internal 2 MHz RC Oscillator
        RC32M = 0x01, // Internal 32 MHz RC Oscillator
        RC32K = 0x02, // Internal 32.768 kHz RC Oscillator
        XOSC = 0x03, // External Crystal Oscillator or Clock
        PLL = 0x04, // Phase Locked Loop
    };
    // Prescaler A Division Factor
    enum class PSADIVv : uint8_t {
        _1 = 0x00, // Divide by 1
        _2 = 0x01, // Divide by 2
        _4 = 0x03, // Divide by 4
        _8 = 0x05, // Divide by 8
        _16 = 0x07, // Divide by 16
        _32 = 0x09, // Divide by 32
        _64 = 0x0B, // Divide by 64
        _128 = 0x0D, // Divide by 128
        _256 = 0x0F, // Divide by 256
        _512 = 0x11, // Divide by 512
    };
    // Prescaler B and C Division Factor
    enum class PSBCDIVv : uint8_t {
        _1_1 = 0x00, // Divide B by 1 and C by 1
        _1_2 = 0x01, // Divide B by 1 and C by 2
        _4_1 = 0x02, // Divide B by 4 and C by 1
        _2_2 = 0x03, // Divide B by 2 and C by 2
    };
    // RTC Clock Source
    enum class RTCSRCv : uint8_t {
        ULP = 0x00, // 1.024 kHz from internal 32kHz ULP
        TOSC = 0x01, // 1.024 kHz from 32.768 kHz crystal oscillator on TOSC
        RCOSC = 0x02, // 1.024 kHz from internal 32.768 kHz RC oscillator
        TOSC32 = 0x05, // 32.768 kHz from 32.768 kHz crystal oscillator on TOSC
        RCOSC32 = 0x06, // 32.768 kHz from internal 32.768 kHz RC oscillator
        EXTCLK = 0x07, // External Clock from TOSC1
    };
    // USB Prescaler Division Factor
    enum class USBPSDIVv : uint8_t {
        _1 = 0x00, // Divide by 1
        _2 = 0x01, // Divide by 2
        _4 = 0x02, // Divide by 4
        _8 = 0x03, // Divide by 8
        _16 = 0x04, // Divide by 16
        _32 = 0x05, // Divide by 32
    };
    // USB Clock Source
    enum class USBSRCv : uint8_t {
        PLL = 0x00, // PLL
        RC32M = 0x01, // Internal 32 MHz RC Oscillator
    };
}   // namespace CLK

/**
 * CLK
 * Clock System
 * Size: 5 bytes
 */
template <addressType BASE_ADDRESS>
struct CLK_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRL_t, 2, 0, CLK::SCLKSELv> SCLKSEL = {};    //< System Clock Selection
    } CTRL = {};

    /// Prescaler Control Register - 1 bytes
    static constexpr struct PSCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<PSCTRL_t, 6, 2, CLK::PSADIVv> PSADIV = {};    //< Prescaler A Division Factor
        static constexpr bitfield_t<PSCTRL_t, 1, 0, CLK::PSBCDIVv> PSBCDIV = {};    //< Prescaler B and C Division factor
    } PSCTRL = {};

    /// Lock register - 1 bytes
    static constexpr struct LOCK_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<LOCK_t, 0, 0, bool> LOCK = {};    //< Clock System Lock
    } LOCK = {};

    /// RTC Control Register - 1 bytes
    static constexpr struct RTCCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<RTCCTRL_t, 3, 1, CLK::RTCSRCv> RTCSRC = {};    //< Clock Source
        static constexpr bitfield_t<RTCCTRL_t, 0, 0, bool> RTCEN = {};    //< Clock Source Enable
    } RTCCTRL = {};

    /// USB Control Register - 1 bytes
    static constexpr struct USBCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<USBCTRL_t, 5, 3, CLK::USBPSDIVv> USBPSDIV = {};    //< Prescaler Division Factor
        static constexpr bitfield_t<USBCTRL_t, 2, 1, CLK::USBSRCv> USBSRC = {};    //< Clock Source
        static constexpr bitfield_t<USBCTRL_t, 0, 0, bool> USBSEN = {};    //< Clock Source Enable
    } USBCTRL = {};

};

} // namespace sfr
