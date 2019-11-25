/**
 * XMEGAAU-AC (id I6077)
 * Analog Comparator
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * AC
 * Analog Comparator
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct AC_t {

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

    /// Analog Comparator 0 Control - 1 bytes
    struct AC0CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using INTMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0xC0, 6, INTMODEv>;    //< Interrupt Mode
        using INTLVL = reg_field_t<BASE_ADDRESS + 0x0000, 0x30, 4, INTLVLv>;    //< Interrupt Level
        using HSMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x08, 3>;    //< High-speed Mode
        using HYSMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x06, 1, HYSMODEv>;    //< Hysteresis Mode
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Enable
    };

    /// Analog Comparator 1 Control - 1 bytes
    struct AC1CTRL : public reg8_t<BASE_ADDRESS + 0x0001> {
        using INTMODE = reg_field_t<BASE_ADDRESS + 0x0001, 0xC0, 6, INTMODEv>;    //< Interrupt Mode
        using INTLVL = reg_field_t<BASE_ADDRESS + 0x0001, 0x30, 4, INTLVLv>;    //< Interrupt Level
        using HSMODE = reg_field_t<BASE_ADDRESS + 0x0001, 0x08, 3>;    //< High-speed Mode
        using HYSMODE = reg_field_t<BASE_ADDRESS + 0x0001, 0x06, 1, HYSMODEv>;    //< Hysteresis Mode
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Enable
    };

    /// Analog Comparator 0 MUX Control - 1 bytes
    struct AC0MUXCTRL : public reg8_t<BASE_ADDRESS + 0x0002> {
        using MUXPOS = reg_field_t<BASE_ADDRESS + 0x0002, 0x38, 3, MUXPOSv>;    //< MUX Positive Input
        using MUXNEG = reg_field_t<BASE_ADDRESS + 0x0002, 0x07, 0, MUXNEGv>;    //< MUX Negative Input
    };

    /// Analog Comparator 1 MUX Control - 1 bytes
    struct AC1MUXCTRL : public reg8_t<BASE_ADDRESS + 0x0003> {
        using MUXPOS = reg_field_t<BASE_ADDRESS + 0x0003, 0x38, 3, MUXPOSv>;    //< MUX Positive Input
        using MUXNEG = reg_field_t<BASE_ADDRESS + 0x0003, 0x07, 0, MUXNEGv>;    //< MUX Negative Input
    };

    /// Control Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0004> {
        using AC1OUT = reg_field_t<BASE_ADDRESS + 0x0004, 0x02, 1>;    //< Analog Comparator 1 Output Enable
        using AC0OUT = reg_field_t<BASE_ADDRESS + 0x0004, 0x01, 0>;    //< Analog Comparator 0 Output Enable
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0005> {
        using SCALEFAC = reg_field_t<BASE_ADDRESS + 0x0005, 0x3F, 0>;    //< VCC Voltage Scaler Factor
    };

    /// Window Mode Control - 1 bytes
    struct WINCTRL : public reg8_t<BASE_ADDRESS + 0x0006> {
        using WEN = reg_field_t<BASE_ADDRESS + 0x0006, 0x10, 4>;    //< Window Mode Enable
        using WINTMODE = reg_field_t<BASE_ADDRESS + 0x0006, 0x0C, 2, WINTMODEv>;    //< Window Interrupt Mode
        using WINTLVL = reg_field_t<BASE_ADDRESS + 0x0006, 0x03, 0, WINTLVLv>;    //< Window Interrupt Level
    };

    /// Status - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0007> {
        using WSTATE = reg_field_t<BASE_ADDRESS + 0x0007, 0xC0, 6, WSTATEv>;    //< Window Mode State
        using AC1STATE = reg_field_t<BASE_ADDRESS + 0x0007, 0x20, 5>;    //< Analog Comparator 1 State
        using AC0STATE = reg_field_t<BASE_ADDRESS + 0x0007, 0x10, 4>;    //< Analog Comparator 0 State
        using WIF = reg_field_t<BASE_ADDRESS + 0x0007, 0x04, 2>;    //< Window Mode Interrupt Flag
        using AC1IF = reg_field_t<BASE_ADDRESS + 0x0007, 0x02, 1>;    //< Analog Comparator 1 Interrupt Flag
        using AC0IF = reg_field_t<BASE_ADDRESS + 0x0007, 0x01, 0>;    //< Analog Comparator 0 Interrupt Flag
    };

    /// Current Source Control - 1 bytes
    struct CURRCTRL : public reg8_t<BASE_ADDRESS + 0x0008> {
        using CURRENT = reg_field_t<BASE_ADDRESS + 0x0008, 0x80, 7>;    //< Current Source Enable
        using CURRMODE = reg_field_t<BASE_ADDRESS + 0x0008, 0x40, 6>;    //< Current Mode
        using AC1CURR = reg_field_t<BASE_ADDRESS + 0x0008, 0x02, 1>;    //< AC1 Current Source Output Enable
        using AC0CURR = reg_field_t<BASE_ADDRESS + 0x0008, 0x01, 0>;    //< AC0 Current Source Output Enable
    };

    /// Current Source Calibration - 1 bytes
    struct CURRCALIB : public reg8_t<BASE_ADDRESS + 0x0009> {
        using CALIB = reg_field_t<BASE_ADDRESS + 0x0009, 0x0F, 0>;    //< Current Source Calibration
    };
};

} // namespace device
