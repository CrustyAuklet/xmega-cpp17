/**
 * XMEGAAU-ADC (id I6099)
 * Analog/Digital Converter
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * ADC_CH
 * ADC Channel
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct ADC_CH_t {
    // Positive input multiplexer selection
    enum class MUXPOSv : uint8_t {
        PIN0 = 0x00, // Input pin 0
        PIN1 = 0x01, // Input pin 1
        PIN2 = 0x02, // Input pin 2
        PIN3 = 0x03, // Input pin 3
        PIN4 = 0x04, // Input pin 4
        PIN5 = 0x05, // Input pin 5
        PIN6 = 0x06, // Input pin 6
        PIN7 = 0x07, // Input pin 7
        PIN8 = 0x08, // Input pin 8
        PIN9 = 0x09, // Input pin 9
        PIN10 = 0x0A, // Input pin 10
        PIN11 = 0x0B, // Input pin 11
        PIN12 = 0x0C, // Input pin 12
        PIN13 = 0x0D, // Input pin 13
        PIN14 = 0x0E, // Input pin 14
        PIN15 = 0x0F, // Input pin 15
    };

    // Internal input multiplexer selections
    enum class MUXINTv : uint8_t {
        TEMP = 0x00, // Temperature Reference
        BANDGAP = 0x01, // Bandgap Reference
        SCALEDVCC = 0x02, // 1/10 scaled VCC
        DAC = 0x03, // DAC output
    };

    // Negative input multiplexer selection
    enum class MUXNEGv : uint8_t {
        PIN0 = 0x00, // Input pin 0 (Input Mode = 2)
        PIN1 = 0x01, // Input pin 1 (Input Mode = 2)
        PIN2 = 0x02, // Input pin 2 (Input Mode = 2)
        PIN3 = 0x03, // Input pin 3 (Input Mode = 2)
        PIN4 = 0x00, // Input pin 4 (Input Mode = 3)
        PIN5 = 0x01, // Input pin 5 (Input Mode = 3)
        PIN6 = 0x02, // Input pin 6 (Input Mode = 3)
        PIN7 = 0x03, // Input pin 7 (Input Mode = 3)
        GND_MODE3 = 0x05, // PAD Ground (Input Mode = 2)
        INTGND_MODE3 = 0x07, // Internal Ground (Input Mode = 2)
        INTGND_MODE4 = 0x04, // Internal Ground (Input Mode = 3)
        GND_MODE4 = 0x07, // PAD Ground (Input Mode = 3)
    };

    // Input mode
    enum class INPUTMODEv : uint8_t {
        INTERNAL = 0x00, // Internal inputs, no gain
        SINGLEENDED = 0x01, // Single-ended input, no gain
        DIFF = 0x02, // Differential input, no gain
        DIFFWGAIN = 0x03, // Differential input, with gain
    };

    // Gain factor
    enum class GAINv : uint8_t {
        _1X = 0x00, // 1x gain
        _2X = 0x01, // 2x gain
        _4X = 0x02, // 4x gain
        _8X = 0x03, // 8x gain
        _16X = 0x04, // 16x gain
        _32X = 0x05, // 32x gain
        _64X = 0x06, // 64x gain
        DIV2 = 0x07, // x/2 gain
    };

    // Interupt mode
    enum class INTMODEv : uint8_t {
        COMPLETE = 0x00, // Interrupt on conversion complete
        BELOW = 0x01, // Interrupt on result below compare value
        ABOVE = 0x03, // Interrupt on result above compare value
    };

    // Interrupt level
    enum class INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low level
        MED = 0x02, // Medium level
        HI = 0x03, // High level
    };

    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using START = reg_field_t<BASE_ADDRESS + 0x0000, 0x80, 7>;    //< Channel Start Conversion
        using GAIN = reg_field_t<BASE_ADDRESS + 0x0000, 0x1C, 2, GAINv>;    //< Gain Factor
        using INPUTMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x03, 0, INPUTMODEv>;    //< Input Mode Select
    };

    /// MUX Control - 1 bytes
    struct MUXCTRL : public reg8_t<BASE_ADDRESS + 0x0001> {
        using MUXPOS = reg_field_t<BASE_ADDRESS + 0x0001, 0x78, 3, MUXPOSv>;    //< MUX selection on Positive ADC input
        using MUXINT = reg_field_t<BASE_ADDRESS + 0x0001, 0x78, 3, MUXINTv>;    //< MUX selection on Internal ADC input
        using MUXNEG = reg_field_t<BASE_ADDRESS + 0x0001, 0x07, 0, MUXNEGv>;    //< MUX selection on Negative ADC input
    };

    /// Channel Interrupt Control Register - 1 bytes
    struct INTCTRL : public reg8_t<BASE_ADDRESS + 0x0002> {
        using INTMODE = reg_field_t<BASE_ADDRESS + 0x0002, 0x0C, 2, INTMODEv>;    //< Interrupt Mode
        using INTLVL = reg_field_t<BASE_ADDRESS + 0x0002, 0x03, 0, INTLVLv>;    //< Interrupt Level
    };

    /// Interrupt Flags - 1 bytes
    struct INTFLAGS : public reg8_t<BASE_ADDRESS + 0x0003> {
        using CHIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x01, 0>;    //< Channel Interrupt Flag
    };

    /// Channel Result - 2 bytes
    struct RES : public reg16_t<BASE_ADDRESS + 0x0004> {
    };

    /// Input Channel Scan - 1 bytes
    struct SCAN : public reg8_t<BASE_ADDRESS + 0x0006> {
        using OFFSET = reg_field_t<BASE_ADDRESS + 0x0006, 0xF0, 4>;    //< Positive MUX setting offset
        using SCANNUM = reg_field_t<BASE_ADDRESS + 0x0006, 0x0F, 0>;    //< Number of Channels included in scan
    };
};

/**
 * ADC
 * Analog-to-Digital Converter
 * Size: 64 bytes
 */
template <addressType BASE_ADDRESS>
struct ADC_t {
    // Conversion result resolution
    enum class RESOLUTIONv : uint8_t {
        _12BIT = 0x00, // 12-bit right-adjusted result
        _8BIT = 0x02, // 8-bit right-adjusted result
        LEFT12BIT = 0x03, // 12-bit left-adjusted result
    };

    // Current Limitation Mode
    enum class CURRLIMITv : uint8_t {
        NO = 0x00, // No limit
        LOW = 0x01, // Low current limit, max. sampling rate 1.5MSPS
        MED = 0x02, // Medium current limit, max. sampling rate 1MSPS
        HIGH = 0x03, // High current limit, max. sampling rate 0.5MSPS
    };

    // Voltage reference selection
    enum class REFSELv : uint8_t {
        INT1V = 0x00, // Internal 1V
        INTVCC = 0x01, // Internal VCC / 1.6
        AREFA = 0x02, // External reference on PORT A
        AREFB = 0x03, // External reference on PORT B
        INTVCC2 = 0x04, // Internal VCC / 2
    };

    // Channel sweep selection
    enum class SWEEPv : uint8_t {
        _0 = 0x00, // ADC Channel 0
        _01 = 0x01, // ADC Channel 0,1
        _012 = 0x02, // ADC Channel 0,1,2
        _0123 = 0x03, // ADC Channel 0,1,2,3
    };

    // Event channel input selection
    enum class EVSELv : uint8_t {
        _0123 = 0x00, // Event Channel 0,1,2,3
        _1234 = 0x01, // Event Channel 1,2,3,4
        _2345 = 0x02, // Event Channel 2,3,4,5
        _3456 = 0x03, // Event Channel 3,4,5,6
        _4567 = 0x04, // Event Channel 4,5,6,7
        _567 = 0x05, // Event Channel 5,6,7
        _67 = 0x06, // Event Channel 6,7
        _7 = 0x07, // Event Channel 7
    };

    // Event action selection
    enum class EVACTv : uint8_t {
        NONE = 0x00, // No event action
        CH0 = 0x01, // First event triggers channel 0
        CH01 = 0x02, // First two events trigger channel 0,1
        CH012 = 0x03, // First three events trigger channel 0,1,2
        CH0123 = 0x04, // Events trigger channel 0,1,2,3
        SWEEP = 0x05, // First event triggers sweep
        SYNCSWEEP = 0x06, // The ADC is flushed and restarted for accurate timing
    };

    // DMA request selection
    enum class DMASELv : uint8_t {
        OFF = 0x00, // Combined DMA request OFF
        CH01 = 0x01, // ADC Channel 0 or 1
        CH012 = 0x02, // ADC Channel 0 or 1 or 2
        CH0123 = 0x03, // ADC Channel 0 or 1 or 2 or 3
    };

    // Clock prescaler
    enum class PRESCALERv : uint8_t {
        DIV4 = 0x00, // Divide clock by 4
        DIV8 = 0x01, // Divide clock by 8
        DIV16 = 0x02, // Divide clock by 16
        DIV32 = 0x03, // Divide clock by 32
        DIV64 = 0x04, // Divide clock by 64
        DIV128 = 0x05, // Divide clock by 128
        DIV256 = 0x06, // Divide clock by 256
        DIV512 = 0x07, // Divide clock by 512
    };

    // ADC ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        CH0 = 0, // Interrupt 0
        CH1 = 1, // Interrupt 1
        CH2 = 2, // Interrupt 2
        CH3 = 3, // Interrupt 3
    };

    /// Control Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using DMASEL = reg_field_t<BASE_ADDRESS + 0x0000, 0xC0, 6, DMASELv>;    //< DMA Selection
        using CH3START = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< Channel 3 Start Conversion
        using CH2START = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Channel 2 Start Conversion
        using CH1START = reg_field_t<BASE_ADDRESS + 0x0000, 0x08, 3>;    //< Channel 1 Start Conversion
        using CH0START = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< Channel 0 Start Conversion
        using FLUSH = reg_field_t<BASE_ADDRESS + 0x0000, 0x02, 1>;    //< Flush Pipeline
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Enable ADC
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0001> {
        using IMPMODE = reg_field_t<BASE_ADDRESS + 0x0001, 0x80, 7>;    //< Gain Stage Impedance Mode
        using CURRLIMIT = reg_field_t<BASE_ADDRESS + 0x0001, 0x60, 5, CURRLIMITv>;    //< Current Limitation
        using CONMODE = reg_field_t<BASE_ADDRESS + 0x0001, 0x10, 4>;    //< Conversion Mode
        using FREERUN = reg_field_t<BASE_ADDRESS + 0x0001, 0x08, 3>;    //< Free Running Mode Enable
        using RESOLUTION = reg_field_t<BASE_ADDRESS + 0x0001, 0x06, 1, RESOLUTIONv>;    //< Result Resolution
    };

    /// Reference Control - 1 bytes
    struct REFCTRL : public reg8_t<BASE_ADDRESS + 0x0002> {
        using REFSEL = reg_field_t<BASE_ADDRESS + 0x0002, 0x70, 4, REFSELv>;    //< Reference Selection
        using BANDGAP = reg_field_t<BASE_ADDRESS + 0x0002, 0x02, 1>;    //< Bandgap enable
        using TEMPREF = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Temperature Reference Enable
    };

    /// Event Control - 1 bytes
    struct EVCTRL : public reg8_t<BASE_ADDRESS + 0x0003> {
        using SWEEP = reg_field_t<BASE_ADDRESS + 0x0003, 0xC0, 6, SWEEPv>;    //< Channel Sweep Selection
        using EVSEL = reg_field_t<BASE_ADDRESS + 0x0003, 0x38, 3, EVSELv>;    //< Event Input Select
        using EVACT = reg_field_t<BASE_ADDRESS + 0x0003, 0x07, 0, EVACTv>;    //< Event Action Select
    };

    /// Clock Prescaler - 1 bytes
    struct PRESCALER : public reg8_t<BASE_ADDRESS + 0x0004> {
        using PRESCALERf = reg_field_t<BASE_ADDRESS + 0x0004, 0x07, 0, PRESCALERv>;    //< Clock Prescaler Selection
    };

    /// Interrupt Flags - 1 bytes
    struct INTFLAGS : public reg8_t<BASE_ADDRESS + 0x0006> {
        using CH3IF = reg_field_t<BASE_ADDRESS + 0x0006, 0x08, 3>;    //< Channel 3 Interrupt Flag
        using CH2IF = reg_field_t<BASE_ADDRESS + 0x0006, 0x04, 2>;    //< Channel 2 Interrupt Flag
        using CH1IF = reg_field_t<BASE_ADDRESS + 0x0006, 0x02, 1>;    //< Channel 1 Interrupt Flag
        using CH0IF = reg_field_t<BASE_ADDRESS + 0x0006, 0x01, 0>;    //< Channel 0 Interrupt Flag
    };

    /// Temporary Register - 1 bytes
    struct TEMP : public reg8_t<BASE_ADDRESS + 0x0007> {
    };

    /// Calibration Value - 2 bytes
    struct CAL : public reg16_t<BASE_ADDRESS + 0x000C> {
    };

    /// Channel 0 Result - 2 bytes
    struct CH0RES : public reg16_t<BASE_ADDRESS + 0x0010> {
    };

    /// Channel 1 Result - 2 bytes
    struct CH1RES : public reg16_t<BASE_ADDRESS + 0x0012> {
    };

    /// Channel 2 Result - 2 bytes
    struct CH2RES : public reg16_t<BASE_ADDRESS + 0x0014> {
    };

    /// Channel 3 Result - 2 bytes
    struct CH3RES : public reg16_t<BASE_ADDRESS + 0x0016> {
    };

    /// Compare Value - 2 bytes
    struct CMP : public reg16_t<BASE_ADDRESS + 0x0018> {
    };

    /// ADC Channel 0
    ADC_CH_t<BASE_ADDRESS + 0x0020> CH0;

    /// ADC Channel 1
    ADC_CH_t<BASE_ADDRESS + 0x0028> CH1;

    /// ADC Channel 2
    ADC_CH_t<BASE_ADDRESS + 0x0030> CH2;

    /// ADC Channel 3
    ADC_CH_t<BASE_ADDRESS + 0x0038> CH3;

};

} // namespace device
