/**
 * XMEGAAU-ADC (id I6099)
 * Analog/Digital Converter
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace ADC {

    // Positive input multiplexer selection
    enum class CH_MUXPOSv : uint8_t {
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
    enum class CH_MUXINTv : uint8_t {
        TEMP = 0x00, // Temperature Reference
        BANDGAP = 0x01, // Bandgap Reference
        SCALEDVCC = 0x02, // 1/10 scaled VCC
        DAC = 0x03, // DAC output
    };
    // Negative input multiplexer selection
    enum class CH_MUXNEGv : uint8_t {
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
    enum class CH_INPUTMODEv : uint8_t {
        INTERNAL = 0x00, // Internal inputs, no gain
        SINGLEENDED = 0x01, // Single-ended input, no gain
        DIFF = 0x02, // Differential input, no gain
        DIFFWGAIN = 0x03, // Differential input, with gain
    };
    // Gain factor
    enum class CH_GAINv : uint8_t {
        _1X = 0x00, // 1x gain
        _2X = 0x01, // 2x gain
        _4X = 0x02, // 4x gain
        _8X = 0x03, // 8x gain
        _16X = 0x04, // 16x gain
        _32X = 0x05, // 32x gain
        _64X = 0x06, // 64x gain
        DIV2 = 0x07, // x/2 gain
    };
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
    // Interupt mode
    enum class CH_INTMODEv : uint8_t {
        COMPLETE = 0x00, // Interrupt on conversion complete
        BELOW = 0x01, // Interrupt on result below compare value
        ABOVE = 0x03, // Interrupt on result above compare value
    };
    // Interrupt level
    enum class CH_INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low level
        MED = 0x02, // Medium level
        HI = 0x03, // High level
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
}   // namespace ADC

/**
 * ADC_CH
 * ADC Channel
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct ADC_CH_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRL_t, 7, 7, bool> START = {};    //< Channel Start Conversion
        static constexpr bitfield_t<CTRL_t, 4, 2, ADC::CH_GAINv> GAIN = {};    //< Gain Factor
        static constexpr bitfield_t<CTRL_t, 1, 0, ADC::CH_INPUTMODEv> INPUTMODE = {};    //< Input Mode Select
    } CTRL = {};

    /// MUX Control - 1 bytes
    static constexpr struct MUXCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<MUXCTRL_t, 6, 3, ADC::CH_MUXPOSv> MUXPOS = {};    //< MUX selection on Positive ADC input
        static constexpr bitfield_t<MUXCTRL_t, 6, 3, ADC::CH_MUXINTv> MUXINT = {};    //< MUX selection on Internal ADC input
        static constexpr bitfield_t<MUXCTRL_t, 2, 0, ADC::CH_MUXNEGv> MUXNEG = {};    //< MUX selection on Negative ADC input
    } MUXCTRL = {};

    /// Channel Interrupt Control Register - 1 bytes
    static constexpr struct INTCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<INTCTRL_t, 3, 2, ADC::CH_INTMODEv> INTMODE = {};    //< Interrupt Mode
        static constexpr bitfield_t<INTCTRL_t, 1, 0, ADC::CH_INTLVLv> INTLVL = {};    //< Interrupt Level
    } INTCTRL = {};

    /// Interrupt Flags - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<INTFLAGS_t, 0, 0, bool> CHIF = {};    //< Channel Interrupt Flag
    } INTFLAGS = {};

    /// Channel Result - 2 bytes
    static constexpr struct RES_t : reg_t<uint16_t, BASE_ADDRESS + 0x0004> {
    } RES = {};

    /// Input Channel Scan - 1 bytes
    static constexpr struct SCAN_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        static constexpr bitfield_t<SCAN_t, 7, 4> OFFSET = {};    //< Positive MUX setting offset
        static constexpr bitfield_t<SCAN_t, 3, 0> SCANNUM = {};    //< Number of Channels included in scan
    } SCAN = {};

};

/**
 * ADC
 * Analog-to-Digital Converter
 * Size: 64 bytes
 */
template <addressType BASE_ADDRESS>
struct ADC_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRLA_t, 7, 6, ADC::DMASELv> DMASEL = {};    //< DMA Selection
        static constexpr bitfield_t<CTRLA_t, 5, 5, bool> CH3START = {};    //< Channel 3 Start Conversion
        static constexpr bitfield_t<CTRLA_t, 4, 4, bool> CH2START = {};    //< Channel 2 Start Conversion
        static constexpr bitfield_t<CTRLA_t, 3, 3, bool> CH1START = {};    //< Channel 1 Start Conversion
        static constexpr bitfield_t<CTRLA_t, 2, 2, bool> CH0START = {};    //< Channel 0 Start Conversion
        static constexpr bitfield_t<CTRLA_t, 1, 1, bool> FLUSH = {};    //< Flush Pipeline
        static constexpr bitfield_t<CTRLA_t, 0, 0, bool> ENABLE = {};    //< Enable ADC
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<CTRLB_t, 7, 7, bool> IMPMODE = {};    //< Gain Stage Impedance Mode
        static constexpr bitfield_t<CTRLB_t, 6, 5, ADC::CURRLIMITv> CURRLIMIT = {};    //< Current Limitation
        static constexpr bitfield_t<CTRLB_t, 4, 4, bool> CONMODE = {};    //< Conversion Mode
        static constexpr bitfield_t<CTRLB_t, 3, 3, bool> FREERUN = {};    //< Free Running Mode Enable
        static constexpr bitfield_t<CTRLB_t, 2, 1, ADC::RESOLUTIONv> RESOLUTION = {};    //< Result Resolution
    } CTRLB = {};

    /// Reference Control - 1 bytes
    static constexpr struct REFCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<REFCTRL_t, 6, 4, ADC::REFSELv> REFSEL = {};    //< Reference Selection
        static constexpr bitfield_t<REFCTRL_t, 1, 1, bool> BANDGAP = {};    //< Bandgap enable
        static constexpr bitfield_t<REFCTRL_t, 0, 0, bool> TEMPREF = {};    //< Temperature Reference Enable
    } REFCTRL = {};

    /// Event Control - 1 bytes
    static constexpr struct EVCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<EVCTRL_t, 7, 6, ADC::SWEEPv> SWEEP = {};    //< Channel Sweep Selection
        static constexpr bitfield_t<EVCTRL_t, 5, 3, ADC::EVSELv> EVSEL = {};    //< Event Input Select
        static constexpr bitfield_t<EVCTRL_t, 2, 0, ADC::EVACTv> EVACT = {};    //< Event Action Select
    } EVCTRL = {};

    /// Clock Prescaler - 1 bytes
    static constexpr struct PRESCALER_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        static constexpr bitfield_t<PRESCALER_t, 2, 0, ADC::PRESCALERv> PRESCALER = {};    //< Clock Prescaler Selection
    } PRESCALER = {};

    /// Interrupt Flags - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        static constexpr bitfield_t<INTFLAGS_t, 3, 3, bool> CH3IF = {};    //< Channel 3 Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 2, 2, bool> CH2IF = {};    //< Channel 2 Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 1, 1, bool> CH1IF = {};    //< Channel 1 Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0, 0, bool> CH0IF = {};    //< Channel 0 Interrupt Flag
    } INTFLAGS = {};

    /// Temporary Register - 1 bytes
    static constexpr struct TEMP_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
    } TEMP = {};

    /// Calibration Value - 2 bytes
    static constexpr struct CAL_t : reg_t<uint16_t, BASE_ADDRESS + 0x000C> {
    } CAL = {};

    /// Channel 0 Result - 2 bytes
    static constexpr struct CH0RES_t : reg_t<uint16_t, BASE_ADDRESS + 0x0010> {
    } CH0RES = {};

    /// Channel 1 Result - 2 bytes
    static constexpr struct CH1RES_t : reg_t<uint16_t, BASE_ADDRESS + 0x0012> {
    } CH1RES = {};

    /// Channel 2 Result - 2 bytes
    static constexpr struct CH2RES_t : reg_t<uint16_t, BASE_ADDRESS + 0x0014> {
    } CH2RES = {};

    /// Channel 3 Result - 2 bytes
    static constexpr struct CH3RES_t : reg_t<uint16_t, BASE_ADDRESS + 0x0016> {
    } CH3RES = {};

    /// Compare Value - 2 bytes
    static constexpr struct CMP_t : reg_t<uint16_t, BASE_ADDRESS + 0x0018> {
    } CMP = {};

    /// ADC Channel 0
    static constexpr ADC_CH_t<BASE_ADDRESS + 0x0020> CH0 = {};

    /// ADC Channel 1
    static constexpr ADC_CH_t<BASE_ADDRESS + 0x0028> CH1 = {};

    /// ADC Channel 2
    static constexpr ADC_CH_t<BASE_ADDRESS + 0x0030> CH2 = {};

    /// ADC Channel 3
    static constexpr ADC_CH_t<BASE_ADDRESS + 0x0038> CH3 = {};

    // ADC ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        CH0 = 0, // Interrupt 0
        CH1 = 1, // Interrupt 1
        CH2 = 2, // Interrupt 2
        CH3 = 3, // Interrupt 3
    };
};

} // namespace sfr
