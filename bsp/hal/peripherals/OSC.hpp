/**
 * XMEGAAU-OSC (id I6079)
 * Oscillator
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * OSC
 * Oscillator
 * Size: 7 bytes
 */
template <addressType BASE_ADDRESS>
struct OSC_t {

    // Oscillator Frequency Range
    enum class FRQRANGEv : uint8_t {
        _04TO2 = 0x00, // 0.4 - 2 MHz
        _2TO9 = 0x01, // 2 - 9 MHz
        _9TO12 = 0x02, // 9 - 12 MHz
        _12TO16 = 0x03, // 12 - 16 MHz
    };

    // External Oscillator Selection and Startup Time
    enum class XOSCSELv : uint8_t {
        EXTCLK = 0x00, // External Clock - 6 CLK
        _32KHz = 0x02, // 32.768 kHz TOSC - 32K CLK
        XTAL_256CLK = 0x03, // 0.4-16 MHz XTAL - 256 CLK
        XTAL_1KCLK = 0x07, // 0.4-16 MHz XTAL - 1K CLK
        XTAL_16KCLK = 0x0B, // 0.4-16 MHz XTAL - 16K CLK
    };

    // PLL Clock Source
    enum class PLLSRCv : uint8_t {
        RC2M = 0x00, // Internal 2 MHz RC Oscillator
        RC32M = 0x02, // Internal 32 MHz RC Oscillator
        XOSC = 0x03, // External Oscillator
    };

    // 2 MHz DFLL Calibration Reference
    enum class RC2MCREFv : uint8_t {
        RC32K = 0x00, // Internal 32.768 kHz RC Oscillator
        XOSC32K = 0x01, // External 32.768 kHz Crystal Oscillator
    };

    // 32 MHz DFLL Calibration Reference
    enum class RC32MCREFv : uint8_t {
        RC32K = 0x00, // Internal 32.768 kHz RC Oscillator
        XOSC32K = 0x01, // External 32.768 kHz Crystal Oscillator
        USBSOF = 0x02, // USB Start of Frame
    };

    // OSC ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        OSCF = 0, // Oscillator Failure Interrupt (NMI)
    };

    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using PLLEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< PLL Enable
        using XOSCEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x08, 3>;    //< External Oscillator Enable
        using RC32KEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< Internal 32.768 kHz RC Oscillator Enable
        using RC32MEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x02, 1>;    //< Internal 32 MHz RC Oscillator Enable
        using RC2MEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Internal 2 MHz RC Oscillator Enable
    };

    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0001> {
        using PLLRDY = reg_field_t<BASE_ADDRESS + 0x0001, 0x10, 4>;    //< PLL Ready
        using XOSCRDY = reg_field_t<BASE_ADDRESS + 0x0001, 0x08, 3>;    //< External Oscillator Ready
        using RC32KRDY = reg_field_t<BASE_ADDRESS + 0x0001, 0x04, 2>;    //< Internal 32.768 kHz RC Oscillator Ready
        using RC32MRDY = reg_field_t<BASE_ADDRESS + 0x0001, 0x02, 1>;    //< Internal 32 MHz RC Oscillator Ready
        using RC2MRDY = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Internal 2 MHz RC Oscillator Ready
    };

    /// External Oscillator Control Register - 1 bytes
    struct XOSCCTRL : public reg8_t<BASE_ADDRESS + 0x0002> {
        using FRQRANGE = reg_field_t<BASE_ADDRESS + 0x0002, 0xC0, 6, FRQRANGEv>;    //< Frequency Range
        using X32KLPM = reg_field_t<BASE_ADDRESS + 0x0002, 0x20, 5>;    //< 32.768 kHz XTAL OSC Low-power Mode
        using XOSCPWR = reg_field_t<BASE_ADDRESS + 0x0002, 0x10, 4>;    //< 16 MHz Crystal Oscillator High Power mode
        using XOSCSEL = reg_field_t<BASE_ADDRESS + 0x0002, 0x0F, 0, XOSCSELv>;    //< External Oscillator Selection and Startup Time
    };

    /// Oscillator Failure Detection Register - 1 bytes
    struct XOSCFAIL : public reg8_t<BASE_ADDRESS + 0x0003> {
        using PLLFDIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x08, 3>;    //< PLL Failure Detection Interrupt Flag
        using PLLFDEN = reg_field_t<BASE_ADDRESS + 0x0003, 0x04, 2>;    //< PLL Failure Detection Enable
        using XOSCFDIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x02, 1>;    //< XOSC Failure Detection Interrupt Flag
        using XOSCFDEN = reg_field_t<BASE_ADDRESS + 0x0003, 0x01, 0>;    //< XOSC Failure Detection Enable
    };

    /// 32.768 kHz Internal Oscillator Calibration Register - 1 bytes
    struct RC32KCAL : public reg8_t<BASE_ADDRESS + 0x0004> {
    };

    /// PLL Control Register - 1 bytes
    struct PLLCTRL : public reg8_t<BASE_ADDRESS + 0x0005> {
        using PLLSRC = reg_field_t<BASE_ADDRESS + 0x0005, 0xC0, 6, PLLSRCv>;    //< Clock Source
        using PLLDIV = reg_field_t<BASE_ADDRESS + 0x0005, 0x20, 5>;    //< Divide by 2
        using PLLFAC = reg_field_t<BASE_ADDRESS + 0x0005, 0x1F, 0>;    //< Multiplication Factor
    };

    /// DFLL Control Register - 1 bytes
    struct DFLLCTRL : public reg8_t<BASE_ADDRESS + 0x0006> {
        using RC32MCREF = reg_field_t<BASE_ADDRESS + 0x0006, 0x06, 1, RC32MCREFv>;    //< 32 MHz DFLL Calibration Reference
        using RC2MCREF = reg_field_t<BASE_ADDRESS + 0x0006, 0x01, 0, RC2MCREFv>;    //< 2 MHz DFLL Calibration Reference
    };
};

} // namespace device
