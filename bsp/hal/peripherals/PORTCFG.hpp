/**
 * XMEGAAU-PORTCFG (id I6075)
 * Port Configuration
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * PORTCFG
 * I/O port Configuration
 * Size: 7 bytes
 */
template <addressType BASE_ADDRESS>
struct PORTCFG_t {

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


    /// Multi-pin Configuration Mask - 1 bytes
    struct MPCMASK : public reg8_t<BASE_ADDRESS + 0x0000> {
    };

    /// Virtual Port Control Register A - 1 bytes
    struct VPCTRLA : public reg8_t<BASE_ADDRESS + 0x0002> {
        using VP1MAP = reg_field_t<BASE_ADDRESS + 0x0002, 0xF0, 4, VP13MAPv>;    //< Virtual Port 1 Mapping
        using VP0MAP = reg_field_t<BASE_ADDRESS + 0x0002, 0x0F, 0, VP02MAPv>;    //< Virtual Port 0 Mapping
    };

    /// Virtual Port Control Register B - 1 bytes
    struct VPCTRLB : public reg8_t<BASE_ADDRESS + 0x0003> {
        using VP3MAP = reg_field_t<BASE_ADDRESS + 0x0003, 0xF0, 4, VP13MAPv>;    //< Virtual Port 3 Mapping
        using VP2MAP = reg_field_t<BASE_ADDRESS + 0x0003, 0x0F, 0, VP02MAPv>;    //< Virtual Port 2 Mapping
    };

    /// Clock and Event Out Register - 1 bytes
    struct CLKEVOUT : public reg8_t<BASE_ADDRESS + 0x0004> {
        using CLKOUT = reg_field_t<BASE_ADDRESS + 0x0004, 0x03, 0, CLKOUTv>;    //< Peripheral Clock Output Port
        using CLKOUTSEL = reg_field_t<BASE_ADDRESS + 0x0004, 0x0C, 2, CLKOUTSELv>;    //< Peripheral Clock Output Select
        using EVOUT = reg_field_t<BASE_ADDRESS + 0x0004, 0x30, 4, EVOUTv>;    //< Event Output Port
        using RTCOUT = reg_field_t<BASE_ADDRESS + 0x0004, 0x40, 6>;    //< RTC Clock Output
        using CLKEVPIN = reg_field_t<BASE_ADDRESS + 0x0004, 0x80, 7, CLKEVPINv>;    //< Peripheral Clock and Event Output pin Select
    };

    /// EBI Output register - 1 bytes
    struct EBIOUT : public reg8_t<BASE_ADDRESS + 0x0005> {
        using EBICSOUT = reg_field_t<BASE_ADDRESS + 0x0005, 0x03, 0, EBICSOUTv>;    //< EBI Chip Select Output
        using EBIADROUT = reg_field_t<BASE_ADDRESS + 0x0005, 0x0C, 2, EBIADROUTv>;    //< EBI Address Output
    };

    /// Event Output Select - 1 bytes
    struct EVOUTSEL : public reg8_t<BASE_ADDRESS + 0x0006> {
        using EVOUTSELf = reg_field_t<BASE_ADDRESS + 0x0006, 0x07, 0, EVOUTSELv>;    //< Event Output Select
    };
};

} // namespace device
