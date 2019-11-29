/**
 * XMEGAAU-PORTCFG (id I6075)
 * Port Configuration
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace PORTCFG {

    // Virtual Port Mapping
    enum class VP02MAPv : uint8_t {
        PORTA = 0x00, // Mapped To PORTA
        PORTB = 0x01, // Mapped To PORTB
        PORTC = 0x02, // Mapped To PORTC
        PORTD = 0x03, // Mapped To PORTD
        PORTE = 0x04, // Mapped To PORTE
        PORTF = 0x05, // Mapped To PORTF
        PORTG = 0x06, // Mapped To PORTG
        PORTH = 0x07, // Mapped To PORTH
        PORTJ = 0x08, // Mapped To PORTJ
        PORTK = 0x09, // Mapped To PORTK
        PORTL = 0x0A, // Mapped To PORTL
        PORTM = 0x0B, // Mapped To PORTM
        PORTN = 0x0C, // Mapped To PORTN
        PORTP = 0x0D, // Mapped To PORTP
        PORTQ = 0x0E, // Mapped To PORTQ
        PORTR = 0x0F, // Mapped To PORTR
    };
    // Virtual Port Mapping
    enum class VP13MAPv : uint8_t {
        PORTA = 0x00, // Mapped To PORTA
        PORTB = 0x01, // Mapped To PORTB
        PORTC = 0x02, // Mapped To PORTC
        PORTD = 0x03, // Mapped To PORTD
        PORTE = 0x04, // Mapped To PORTE
        PORTF = 0x05, // Mapped To PORTF
        PORTG = 0x06, // Mapped To PORTG
        PORTH = 0x07, // Mapped To PORTH
        PORTJ = 0x08, // Mapped To PORTJ
        PORTK = 0x09, // Mapped To PORTK
        PORTL = 0x0A, // Mapped To PORTL
        PORTM = 0x0B, // Mapped To PORTM
        PORTN = 0x0C, // Mapped To PORTN
        PORTP = 0x0D, // Mapped To PORTP
        PORTQ = 0x0E, // Mapped To PORTQ
        PORTR = 0x0F, // Mapped To PORTR
    };
    // System Clock Output Port
    enum class CLKOUTv : uint8_t {
        OFF = 0x00, // System Clock Output Disabled
        PC7 = 0x01, // System Clock Output on Port C pin 7
        PD7 = 0x02, // System Clock Output on Port D pin 7
        PE7 = 0x03, // System Clock Output on Port E pin 7
    };
    // Peripheral Clock Output Select
    enum class CLKOUTSELv : uint8_t {
        CLK1X = 0x00, // 1x Peripheral Clock Output to pin
        CLK2X = 0x01, // 2x Peripheral Clock Output to pin
        CLK4X = 0x02, // 4x Peripheral Clock Output to pin
    };
    // Event Output Port
    enum class EVOUTv : uint8_t {
        OFF = 0x00, // Event Output Disabled
        PC7 = 0x01, // Event Channel 7 Output on Port C pin 7
        PD7 = 0x02, // Event Channel 7 Output on Port D pin 7
        PE7 = 0x03, // Event Channel 7 Output on Port E pin 7
    };
    // Clock and Event Output Port
    enum class CLKEVPINv : uint8_t {
        PIN7 = 0x00, // Clock and Event Ouput on PIN 7
        PIN4 = 0x01, // Clock and Event Ouput on PIN 4
    };
    // EBI Address Output Port
    enum class EBIADROUTv : uint8_t {
        PF = 0x00, // EBI port 3 address output on PORTF pins 0 to 7
        PE = 0x01, // EBI port 3 address output on PORTE pins 0 to 7
        PFH = 0x02, // EBI port 3 address output on PORTF pins 4 to 7
        PEH = 0x03, // EBI port 3 address output on PORTE pins 4 to 7
    };
    // EBI Chip Select Output Port
    enum class EBICSOUTv : uint8_t {
        PH = 0x00, // EBI chip select output to PORTH pin 4 to 7
        PL = 0x01, // EBI chip select output to PORTL pin 4 to 7
        PF = 0x02, // EBI chip select output to PORTF pin 4 to 7
        PE = 0x03, // EBI chip select output to PORTE pin 4 to 7
    };
    // Event Output Select
    enum class EVOUTSELv : uint8_t {
        _0 = 0x00, // Event Channel 0 output to pin
        _1 = 0x01, // Event Channel 1 output to pin
        _2 = 0x02, // Event Channel 2 output to pin
        _3 = 0x03, // Event Channel 3 output to pin
        _4 = 0x04, // Event Channel 4 output to pin
        _5 = 0x05, // Event Channel 5 output to pin
        _6 = 0x06, // Event Channel 6 output to pin
        _7 = 0x07, // Event Channel 7 output to pin
    };
}   // namespace PORTCFG

/**
 * PORTCFG
 * I/O port Configuration
 * Size: 7 bytes
 */
template <addressType BASE_ADDRESS>
struct PORTCFG_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Multi-pin Configuration Mask - 1 bytes
    static constexpr struct MPCMASK_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
    } MPCMASK = {};

    /// Virtual Port Control Register A - 1 bytes
    static constexpr struct VPCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<VPCTRLA_t, 7, 4, PORTCFG::VP13MAPv> VP1MAP = {};    //< Virtual Port 1 Mapping
        static constexpr bitfield_t<VPCTRLA_t, 3, 0, PORTCFG::VP02MAPv> VP0MAP = {};    //< Virtual Port 0 Mapping
    } VPCTRLA = {};

    /// Virtual Port Control Register B - 1 bytes
    static constexpr struct VPCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<VPCTRLB_t, 7, 4, PORTCFG::VP13MAPv> VP3MAP = {};    //< Virtual Port 3 Mapping
        static constexpr bitfield_t<VPCTRLB_t, 3, 0, PORTCFG::VP02MAPv> VP2MAP = {};    //< Virtual Port 2 Mapping
    } VPCTRLB = {};

    /// Clock and Event Out Register - 1 bytes
    static constexpr struct CLKEVOUT_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<CLKEVOUT_t, 1, 0, PORTCFG::CLKOUTv> CLKOUT = {};    //< Peripheral Clock Output Port
        static constexpr bitfield_t<CLKEVOUT_t, 3, 2, PORTCFG::CLKOUTSELv> CLKOUTSEL = {};    //< Peripheral Clock Output Select
        static constexpr bitfield_t<CLKEVOUT_t, 5, 4, PORTCFG::EVOUTv> EVOUT = {};    //< Event Output Port
        static constexpr bitfield_t<CLKEVOUT_t, 6, 6, bool> RTCOUT = {};    //< RTC Clock Output
        static constexpr bitfield_t<CLKEVOUT_t, 7, 7, bool> CLKEVPIN = {};    //< Peripheral Clock and Event Output pin Select
    } CLKEVOUT = {};

    /// EBI Output register - 1 bytes
    static constexpr struct EBIOUT_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
        static constexpr bitfield_t<EBIOUT_t, 1, 0, PORTCFG::EBICSOUTv> EBICSOUT = {};    //< EBI Chip Select Output
        static constexpr bitfield_t<EBIOUT_t, 3, 2, PORTCFG::EBIADROUTv> EBIADROUT = {};    //< EBI Address Output
    } EBIOUT = {};

    /// Event Output Select - 1 bytes
    static constexpr struct EVOUTSEL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
        static constexpr bitfield_t<EVOUTSEL_t, 2, 0, PORTCFG::EVOUTSELv> EVOUTSEL = {};    //< Event Output Select
    } EVOUTSEL = {};

};

} // namespace sfr
