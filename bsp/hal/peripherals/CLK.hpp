/**
 * XMEGAAU-CLK (id I6073)
 * Clock System
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * CLK
 * Clock System
 * Size: 5 bytes
 */
template <addressType BASE_ADDRESS>
struct CLK_t {

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


    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using SCLKSEL = reg_field_t<BASE_ADDRESS + 0x0000, 0x07, 0, SCLKSELv>;    //< System Clock Selection
    };

    /// Prescaler Control Register - 1 bytes
    struct PSCTRL : public reg8_t<BASE_ADDRESS + 0x0001> {
        using PSADIV = reg_field_t<BASE_ADDRESS + 0x0001, 0x7C, 2, PSADIVv>;    //< Prescaler A Division Factor
        using PSBCDIV = reg_field_t<BASE_ADDRESS + 0x0001, 0x03, 0, PSBCDIVv>;    //< Prescaler B and C Division factor
    };

    /// Lock register - 1 bytes
    struct LOCK : public reg8_t<BASE_ADDRESS + 0x0002> {
        using LOCKf = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Clock System Lock
    };

    /// RTC Control Register - 1 bytes
    struct RTCCTRL : public reg8_t<BASE_ADDRESS + 0x0003> {
        using RTCSRC = reg_field_t<BASE_ADDRESS + 0x0003, 0x0E, 1, RTCSRCv>;    //< Clock Source
        using RTCEN = reg_field_t<BASE_ADDRESS + 0x0003, 0x01, 0>;    //< Clock Source Enable
    };

    /// USB Control Register - 1 bytes
    struct USBCTRL : public reg8_t<BASE_ADDRESS + 0x0004> {
        using USBPSDIV = reg_field_t<BASE_ADDRESS + 0x0004, 0x38, 3, USBPSDIVv>;    //< Prescaler Division Factor
        using USBSRC = reg_field_t<BASE_ADDRESS + 0x0004, 0x06, 1, USBSRCv>;    //< Clock Source
        using USBSEN = reg_field_t<BASE_ADDRESS + 0x0004, 0x01, 0>;    //< Clock Source Enable
    };
};

} // namespace device
