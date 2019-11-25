/**
 * XMEGAAU-DAC (id I6059)
 * Digital/Analog Converter
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * DAC
 * Digital-to-Analog Converter
 * Size: 28 bytes
 */
template <addressType BASE_ADDRESS>
struct DAC_t {

    // Output channel selection
    enum class CHSELv : uint8_t {
        SINGLE = 0x00, // Single channel operation (Channel 0 only)
        SINGLE1 = 0x01, // Single channel operation (Channel 1 only)
        DUAL = 0x02, // Dual channel operation (Channel 0 and channel 1)
    };

    // Reference voltage selection
    enum class REFSELv : uint8_t {
        INT1V = 0x00, // Internal 1V
        AVCC = 0x01, // Analog supply voltage
        AREFA = 0x02, // External reference on AREF on PORTA
        AREFB = 0x03, // External reference on AREF on PORTB
    };

    // Event channel selection
    enum class EVSELv : uint8_t {
        _0 = 0x00, // Event Channel 0
        _1 = 0x01, // Event Channel 1
        _2 = 0x02, // Event Channel 2
        _3 = 0x03, // Event Channel 3
        _4 = 0x04, // Event Channel 4
        _5 = 0x05, // Event Channel 5
        _6 = 0x06, // Event Channel 6
        _7 = 0x07, // Event Channel 7
    };


    /// Control Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using IDOEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Internal Output Enable
        using CH1EN = reg_field_t<BASE_ADDRESS + 0x0000, 0x08, 3>;    //< Channel 1 Output Enable
        using CH0EN = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< Channel 0 Output Enable
        using LPMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x02, 1>;    //< Low Power Mode
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Enable
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0001> {
        using CHSEL = reg_field_t<BASE_ADDRESS + 0x0001, 0x60, 5, CHSELv>;    //< Channel Select
        using CH1TRIG = reg_field_t<BASE_ADDRESS + 0x0001, 0x02, 1>;    //< Channel 1 Event Trig Enable
        using CH0TRIG = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Channel 0 Event Trig Enable
    };

    /// Control Register C - 1 bytes
    struct CTRLC : public reg8_t<BASE_ADDRESS + 0x0002> {
        using REFSEL = reg_field_t<BASE_ADDRESS + 0x0002, 0x18, 3, REFSELv>;    //< Reference Select
        using LEFTADJ = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Left-adjust Result
    };

    /// Event Input Control - 1 bytes
    struct EVCTRL : public reg8_t<BASE_ADDRESS + 0x0003> {
        using EVSPLIT = reg_field_t<BASE_ADDRESS + 0x0003, 0x08, 3>;    //< Separate Event Channel Input for Channel 1
        using EVSEL = reg_field_t<BASE_ADDRESS + 0x0003, 0x07, 0, EVSELv>;    //< Event Input Selection
    };

    /// Status - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0005> {
        using CH1DRE = reg_field_t<BASE_ADDRESS + 0x0005, 0x02, 1>;    //< Channel 1 Data Register Empty
        using CH0DRE = reg_field_t<BASE_ADDRESS + 0x0005, 0x01, 0>;    //< Channel 0 Data Register Empty
    };

    /// Gain Calibration - 1 bytes
    struct CH0GAINCAL : public reg8_t<BASE_ADDRESS + 0x0008> {
        using CH0GAINCALf = reg_field_t<BASE_ADDRESS + 0x0008, 0x7F, 0>;    //< Gain Calibration
    };

    /// Offset Calibration - 1 bytes
    struct CH0OFFSETCAL : public reg8_t<BASE_ADDRESS + 0x0009> {
        using CH0OFFSETCALf = reg_field_t<BASE_ADDRESS + 0x0009, 0x7F, 0>;    //< Offset Calibration
    };

    /// Gain Calibration - 1 bytes
    struct CH1GAINCAL : public reg8_t<BASE_ADDRESS + 0x000A> {
        using CH1GAINCALf = reg_field_t<BASE_ADDRESS + 0x000A, 0x7F, 0>;    //< Gain Calibration
    };

    /// Offset Calibration - 1 bytes
    struct CH1OFFSETCAL : public reg8_t<BASE_ADDRESS + 0x000B> {
        using CH1OFFSETCALf = reg_field_t<BASE_ADDRESS + 0x000B, 0x7F, 0>;    //< Offset Calibration
    };

    /// Channel 0 Data - 2 bytes
    struct CH0DATA : public reg16_t<BASE_ADDRESS + 0x0018> {
    };

    /// Channel 1 Data - 2 bytes
    struct CH1DATA : public reg16_t<BASE_ADDRESS + 0x001A> {
    };
};

} // namespace device
