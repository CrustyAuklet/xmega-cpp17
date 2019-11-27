/**
 * XMEGAAU-AC (id I6077)
 * Analog Comparator
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace AC {

    // Interrupt mode
    enum class INTMODEv : uint8_t {
        BOTHEDGES = 0x00, // Interrupt on both edges
        FALLING = 0x02, // Interrupt on falling edge
        RISING = 0x03, // Interrupt on rising edge
    };

    // Interrupt level
    enum class INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low level
        MED = 0x02, // Medium level
        HI = 0x03, // High level
    };

    // Hysteresis mode selection
    enum class HYSMODEv : uint8_t {
        NO = 0x00, // No hysteresis
        SMALL = 0x01, // Small hysteresis
        LARGE = 0x02, // Large hysteresis
    };

    // Positive input multiplexer selection
    enum class MUXPOSv : uint8_t {
        PIN0 = 0x00, // Pin 0
        PIN1 = 0x01, // Pin 1
        PIN2 = 0x02, // Pin 2
        PIN3 = 0x03, // Pin 3
        PIN4 = 0x04, // Pin 4
        PIN5 = 0x05, // Pin 5
        PIN6 = 0x06, // Pin 6
        DAC = 0x07, // DAC output
    };

    // Negative input multiplexer selection
    enum class MUXNEGv : uint8_t {
        PIN0 = 0x00, // Pin 0
        PIN1 = 0x01, // Pin 1
        PIN3 = 0x02, // Pin 3
        PIN5 = 0x03, // Pin 5
        PIN7 = 0x04, // Pin 7
        DAC = 0x05, // DAC output
        BANDGAP = 0x06, // Bandgap Reference
        SCALER = 0x07, // Internal voltage scaler
    };

    // Windows interrupt mode
    enum class WINTMODEv : uint8_t {
        ABOVE = 0x00, // Interrupt on above window
        INSIDE = 0x01, // Interrupt on inside window
        BELOW = 0x02, // Interrupt on below window
        OUTSIDE = 0x03, // Interrupt on outside window
    };

    // Window interrupt level
    enum class WINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low priority
        MED = 0x02, // Medium priority
        HI = 0x03, // High priority
    };

    // Window mode state
    enum class WSTATEv : uint8_t {
        ABOVE = 0x00, // Signal above window
        INSIDE = 0x01, // Signal inside window
        BELOW = 0x02, // Signal below window
    };

    // AC ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        AC0 = 0, // AC0 Interrupt
        AC1 = 1, // AC1 Interrupt
        ACW = 2, // ACW Window Mode Interrupt
    };
}   // namespace AC

/**
 * AC
 * Analog Comparator
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct AC_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Analog Comparator 0 Control - 1 bytes
    static constexpr struct AC0CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<AC0CTRL_t, 0xC0, 6, INTMODEv> INTMODE = {};    //< Interrupt Mode
        static constexpr bitfield_t<AC0CTRL_t, 0x30, 4, INTLVLv> INTLVL = {};    //< Interrupt Level
        static constexpr bitfield_t<AC0CTRL_t, 0x08, 3> HSMODE = {};    //< High-speed Mode
        static constexpr bitfield_t<AC0CTRL_t, 0x06, 1, HYSMODEv> HYSMODE = {};    //< Hysteresis Mode
        static constexpr bitfield_t<AC0CTRL_t, 0x01, 0> ENABLE = {};    //< Enable
    } AC0CTRL = {};

    /// Analog Comparator 1 Control - 1 bytes
    static constexpr struct AC1CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<AC1CTRL_t, 0xC0, 6, INTMODEv> INTMODE = {};    //< Interrupt Mode
        static constexpr bitfield_t<AC1CTRL_t, 0x30, 4, INTLVLv> INTLVL = {};    //< Interrupt Level
        static constexpr bitfield_t<AC1CTRL_t, 0x08, 3> HSMODE = {};    //< High-speed Mode
        static constexpr bitfield_t<AC1CTRL_t, 0x06, 1, HYSMODEv> HYSMODE = {};    //< Hysteresis Mode
        static constexpr bitfield_t<AC1CTRL_t, 0x01, 0> ENABLE = {};    //< Enable
    } AC1CTRL = {};

    /// Analog Comparator 0 MUX Control - 1 bytes
    static constexpr struct AC0MUXCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<AC0MUXCTRL_t, 0x38, 3, MUXPOSv> MUXPOS = {};    //< MUX Positive Input
        static constexpr bitfield_t<AC0MUXCTRL_t, 0x07, 0, MUXNEGv> MUXNEG = {};    //< MUX Negative Input
    } AC0MUXCTRL = {};

    /// Analog Comparator 1 MUX Control - 1 bytes
    static constexpr struct AC1MUXCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<AC1MUXCTRL_t, 0x38, 3, MUXPOSv> MUXPOS = {};    //< MUX Positive Input
        static constexpr bitfield_t<AC1MUXCTRL_t, 0x07, 0, MUXNEGv> MUXNEG = {};    //< MUX Negative Input
    } AC1MUXCTRL = {};

    /// Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        static constexpr bitfield_t<CTRLA_t, 0x02, 1> AC1OUT = {};    //< Analog Comparator 1 Output Enable
        static constexpr bitfield_t<CTRLA_t, 0x01, 0> AC0OUT = {};    //< Analog Comparator 0 Output Enable
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        static constexpr bitfield_t<CTRLB_t, 0x3F, 0> SCALEFAC = {};    //< VCC Voltage Scaler Factor
    } CTRLB = {};

    /// Window Mode Control - 1 bytes
    static constexpr struct WINCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        static constexpr bitfield_t<WINCTRL_t, 0x10, 4> WEN = {};    //< Window Mode Enable
        static constexpr bitfield_t<WINCTRL_t, 0x0C, 2, WINTMODEv> WINTMODE = {};    //< Window Interrupt Mode
        static constexpr bitfield_t<WINCTRL_t, 0x03, 0, WINTLVLv> WINTLVL = {};    //< Window Interrupt Level
    } WINCTRL = {};

    /// Status - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        static constexpr bitfield_t<STATUS_t, 0xC0, 6, WSTATEv> WSTATE = {};    //< Window Mode State
        static constexpr bitfield_t<STATUS_t, 0x20, 5> AC1STATE = {};    //< Analog Comparator 1 State
        static constexpr bitfield_t<STATUS_t, 0x10, 4> AC0STATE = {};    //< Analog Comparator 0 State
        static constexpr bitfield_t<STATUS_t, 0x04, 2> WIF = {};    //< Window Mode Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 0x02, 1> AC1IF = {};    //< Analog Comparator 1 Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 0x01, 0> AC0IF = {};    //< Analog Comparator 0 Interrupt Flag
    } STATUS = {};

    /// Current Source Control - 1 bytes
    static constexpr struct CURRCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        static constexpr bitfield_t<CURRCTRL_t, 0x80, 7> CURRENT = {};    //< Current Source Enable
        static constexpr bitfield_t<CURRCTRL_t, 0x40, 6> CURRMODE = {};    //< Current Mode
        static constexpr bitfield_t<CURRCTRL_t, 0x02, 1> AC1CURR = {};    //< AC1 Current Source Output Enable
        static constexpr bitfield_t<CURRCTRL_t, 0x01, 0> AC0CURR = {};    //< AC0 Current Source Output Enable
    } CURRCTRL = {};

    /// Current Source Calibration - 1 bytes
    static constexpr struct CURRCALIB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        static constexpr bitfield_t<CURRCALIB_t, 0x0F, 0> CALIB = {};    //< Current Source Calibration
    } CURRCALIB = {};

};

} // namespace device
