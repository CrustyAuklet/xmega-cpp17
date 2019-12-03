/**
 * XMEGAAU-DAC (id I6059)
 * Digital/Analog Converter
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace DAC {

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
}   // namespace DAC

/**
 * DAC
 * Digital-to-Analog Converter
 * Size: 28 bytes
 */
template <addressType BASE_ADDRESS>
struct DAC_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRLA_t, 4, 4, bool> IDOEN = {};    //< Internal Output Enable
        static constexpr bitfield_t<CTRLA_t, 3, 3, bool> CH1EN = {};    //< Channel 1 Output Enable
        static constexpr bitfield_t<CTRLA_t, 2, 2, bool> CH0EN = {};    //< Channel 0 Output Enable
        static constexpr bitfield_t<CTRLA_t, 1, 1, bool> LPMODE = {};    //< Low Power Mode
        static constexpr bitfield_t<CTRLA_t, 0, 0, bool> ENABLE = {};    //< Enable
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<CTRLB_t, 6, 5, DAC::CHSELv> CHSEL = {};    //< Channel Select
        static constexpr bitfield_t<CTRLB_t, 1, 1, bool> CH1TRIG = {};    //< Channel 1 Event Trig Enable
        static constexpr bitfield_t<CTRLB_t, 0, 0, bool> CH0TRIG = {};    //< Channel 0 Event Trig Enable
    } CTRLB = {};

    /// Control Register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<CTRLC_t, 4, 3, DAC::REFSELv> REFSEL = {};    //< Reference Select
        static constexpr bitfield_t<CTRLC_t, 0, 0, bool> LEFTADJ = {};    //< Left-adjust Result
    } CTRLC = {};

    /// Event Input Control - 1 bytes
    static constexpr struct EVCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<EVCTRL_t, 3, 3, bool> EVSPLIT = {};    //< Separate Event Channel Input for Channel 1
        static constexpr bitfield_t<EVCTRL_t, 2, 0, DAC::EVSELv> EVSEL = {};    //< Event Input Selection
    } EVCTRL = {};

    /// Status - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
        static constexpr bitfield_t<STATUS_t, 1, 1, bool> CH1DRE = {};    //< Channel 1 Data Register Empty
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> CH0DRE = {};    //< Channel 0 Data Register Empty
    } STATUS = {};

    /// Gain Calibration - 1 bytes
    static constexpr struct CH0GAINCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0008>::operator=;
        static constexpr bitfield_t<CH0GAINCAL_t, 6, 0> CH0GAINCAL = {};    //< Gain Calibration
    } CH0GAINCAL = {};

    /// Offset Calibration - 1 bytes
    static constexpr struct CH0OFFSETCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0009>::operator=;
        static constexpr bitfield_t<CH0OFFSETCAL_t, 6, 0> CH0OFFSETCAL = {};    //< Offset Calibration
    } CH0OFFSETCAL = {};

    /// Gain Calibration - 1 bytes
    static constexpr struct CH1GAINCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000A>::operator=;
        static constexpr bitfield_t<CH1GAINCAL_t, 6, 0> CH1GAINCAL = {};    //< Gain Calibration
    } CH1GAINCAL = {};

    /// Offset Calibration - 1 bytes
    static constexpr struct CH1OFFSETCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000B>::operator=;
        static constexpr bitfield_t<CH1OFFSETCAL_t, 6, 0> CH1OFFSETCAL = {};    //< Offset Calibration
    } CH1OFFSETCAL = {};

    /// Channel 0 Data - 2 bytes
    static constexpr struct CH0DATA_t : reg_t<uint16_t, BASE_ADDRESS + 0x0018> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0018>::operator=;
    } CH0DATA = {};

    /// Channel 1 Data - 2 bytes
    static constexpr struct CH1DATA_t : reg_t<uint16_t, BASE_ADDRESS + 0x001A> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x001A>::operator=;
    } CH1DATA = {};

};

} // namespace sfr
