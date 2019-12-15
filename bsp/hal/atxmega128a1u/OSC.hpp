/**
 * XMEGAAU-OSC (id I6079)
 * Oscillator
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace OSC {

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
}   // namespace OSC

/**
 * OSC
 * Oscillator
 * Size: 7 bytes
 */
template <addressType BASE_ADDRESS>
struct OSC_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRL_t, 4, 4, bool> PLLEN = {};    //< PLL Enable
        static constexpr bitfield_t<CTRL_t, 3, 3, bool> XOSCEN = {};    //< External Oscillator Enable
        static constexpr bitfield_t<CTRL_t, 2, 2, bool> RC32KEN = {};    //< Internal 32.768 kHz RC Oscillator Enable
        static constexpr bitfield_t<CTRL_t, 1, 1, bool> RC32MEN = {};    //< Internal 32 MHz RC Oscillator Enable
        static constexpr bitfield_t<CTRL_t, 0, 0, bool> RC2MEN = {};    //< Internal 2 MHz RC Oscillator Enable
    } CTRL = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<STATUS_t, 4, 4, bool> PLLRDY = {};    //< PLL Ready
        static constexpr bitfield_t<STATUS_t, 3, 3, bool> XOSCRDY = {};    //< External Oscillator Ready
        static constexpr bitfield_t<STATUS_t, 2, 2, bool> RC32KRDY = {};    //< Internal 32.768 kHz RC Oscillator Ready
        static constexpr bitfield_t<STATUS_t, 1, 1, bool> RC32MRDY = {};    //< Internal 32 MHz RC Oscillator Ready
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> RC2MRDY = {};    //< Internal 2 MHz RC Oscillator Ready
    } STATUS = {};

    /// External Oscillator Control Register - 1 bytes
    static constexpr struct XOSCCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<XOSCCTRL_t, 7, 6, OSC::FRQRANGEv> FRQRANGE = {};    //< Frequency Range
        static constexpr bitfield_t<XOSCCTRL_t, 5, 5, bool> X32KLPM = {};    //< 32.768 kHz XTAL OSC Low-power Mode
        static constexpr bitfield_t<XOSCCTRL_t, 4, 4, bool> XOSCPWR = {};    //< 16 MHz Crystal Oscillator High Power mode
        static constexpr bitfield_t<XOSCCTRL_t, 3, 0, OSC::XOSCSELv> XOSCSEL = {};    //< External Oscillator Selection and Startup Time
    } XOSCCTRL = {};

    /// Oscillator Failure Detection Register - 1 bytes
    static constexpr struct XOSCFAIL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<XOSCFAIL_t, 3, 3, bool> PLLFDIF = {};    //< PLL Failure Detection Interrupt Flag
        static constexpr bitfield_t<XOSCFAIL_t, 2, 2, bool> PLLFDEN = {};    //< PLL Failure Detection Enable
        static constexpr bitfield_t<XOSCFAIL_t, 1, 1, bool> XOSCFDIF = {};    //< XOSC Failure Detection Interrupt Flag
        static constexpr bitfield_t<XOSCFAIL_t, 0, 0, bool> XOSCFDEN = {};    //< XOSC Failure Detection Enable
    } XOSCFAIL = {};

    /// 32.768 kHz Internal Oscillator Calibration Register - 1 bytes
    static constexpr struct RC32KCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
    } RC32KCAL = {};

    /// PLL Control Register - 1 bytes
    static constexpr struct PLLCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
        static constexpr bitfield_t<PLLCTRL_t, 7, 6, OSC::PLLSRCv> PLLSRC = {};    //< Clock Source
        static constexpr bitfield_t<PLLCTRL_t, 5, 5, bool> PLLDIV = {};    //< Divide by 2
        static constexpr bitfield_t<PLLCTRL_t, 4, 0> PLLFAC = {};    //< Multiplication Factor
    } PLLCTRL = {};

    /// DFLL Control Register - 1 bytes
    static constexpr struct DFLLCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
        static constexpr bitfield_t<DFLLCTRL_t, 2, 1, OSC::RC32MCREFv> RC32MCREF = {};    //< 32 MHz DFLL Calibration Reference
        static constexpr bitfield_t<DFLLCTRL_t, 0, 0, bool> RC2MCREF = {};    //< 2 MHz DFLL Calibration Reference
    } DFLLCTRL = {};

    // OSC ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        OSCF = 0, // Oscillator Failure Interrupt (NMI)
    };
};

} // namespace sfr
