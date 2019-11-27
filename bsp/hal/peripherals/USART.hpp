/**
 * XMEGAAU-USART (id I6090)
 * Universal Asynchronous Receiver-Transmitter
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace USART {

    // Receive Complete Interrupt level
    enum class RXCINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Transmit Complete Interrupt level
    enum class TXCINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Data Register Empty Interrupt level
    enum class DREINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Character Size
    enum class CHSIZEv : uint8_t {
        _5BIT = 0x00, // Character size: 5 bit
        _6BIT = 0x01, // Character size: 6 bit
        _7BIT = 0x02, // Character size: 7 bit
        _8BIT = 0x03, // Character size: 8 bit
        _9BIT = 0x07, // Character size: 9 bit
    };

    // Communication Mode
    enum class CMODEv : uint8_t {
        ASYNCHRONOUS = 0x00, // Asynchronous Mode
        SYNCHRONOUS = 0x01, // Synchronous Mode
        IRDA = 0x02, // IrDA Mode
        MSPI = 0x03, // Master SPI Mode
    };

    // Parity Mode
    enum class PMODEv : uint8_t {
        DISABLED = 0x00, // No Parity
        EVEN = 0x02, // Even Parity
        ODD = 0x03, // Odd Parity
    };

    // USART ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        RXC = 0, // Reception Complete Interrupt
        DRE = 1, // Data Register Empty Interrupt
        TXC = 2, // Transmission Complete Interrupt
    };
}   // namespace USART

/**
 * USART
 * Universal Synchronous/Asynchronous Receiver/Transmitter
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct USART_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Data Register - 1 bytes
    static constexpr struct DATA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
    } DATA = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<STATUS_t, 0x80, 7> RXCIF = {};    //< Receive Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 0x40, 6> TXCIF = {};    //< Transmit Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 0x20, 5> DREIF = {};    //< Data Register Empty Flag
        static constexpr bitfield_t<STATUS_t, 0x10, 4> FERR = {};    //< Frame Error
        static constexpr bitfield_t<STATUS_t, 0x08, 3> BUFOVF = {};    //< Buffer Overflow
        static constexpr bitfield_t<STATUS_t, 0x04, 2> PERR = {};    //< Parity Error
        static constexpr bitfield_t<STATUS_t, 0x01, 0> RXB8 = {};    //< Receive Bit 8
    } STATUS = {};

    /// Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<CTRLA_t, 0x30, 4, RXCINTLVLv> RXCINTLVL = {};    //< Receive Interrupt Level
        static constexpr bitfield_t<CTRLA_t, 0x0C, 2, TXCINTLVLv> TXCINTLVL = {};    //< Transmit Interrupt Level
        static constexpr bitfield_t<CTRLA_t, 0x03, 0, DREINTLVLv> DREINTLVL = {};    //< Data Register Empty Interrupt Level
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        static constexpr bitfield_t<CTRLB_t, 0x10, 4> RXEN = {};    //< Receiver Enable
        static constexpr bitfield_t<CTRLB_t, 0x08, 3> TXEN = {};    //< Transmitter Enable
        static constexpr bitfield_t<CTRLB_t, 0x04, 2> CLK2X = {};    //< Double transmission speed
        static constexpr bitfield_t<CTRLB_t, 0x02, 1> MPCM = {};    //< Multi-processor Communication Mode
        static constexpr bitfield_t<CTRLB_t, 0x01, 0> TXB8 = {};    //< Transmit bit 8
    } CTRLB = {};

    /// Control Register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        static constexpr bitfield_t<CTRLC_t, 0xC0, 6, CMODEv> CMODE = {};    //< Communication Mode
        static constexpr bitfield_t<CTRLC_t, 0x30, 4, PMODEv> PMODE = {};    //< Parity Mode
        static constexpr bitfield_t<CTRLC_t, 0x08, 3> SBMODE = {};    //< Stop Bit Mode
        static constexpr bitfield_t<CTRLC_t, 0x07, 0, CHSIZEv> CHSIZE = {};    //< Character Size
    } CTRLC = {};

    /// Baud Rate Control Register A - 1 bytes
    static constexpr struct BAUDCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        static constexpr bitfield_t<BAUDCTRLA_t, 0xFF, 0> BSEL = {};    //< Baud Rate Selection Bits [7:0]
    } BAUDCTRLA = {};

    /// Baud Rate Control Register B - 1 bytes
    static constexpr struct BAUDCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        static constexpr bitfield_t<BAUDCTRLB_t, 0xF0, 4> BSCALE = {};    //< Baud Rate Scale
        static constexpr bitfield_t<BAUDCTRLB_t, 0x0F, 0> BSEL = {};    //< Baud Rate Selection bits[11:8]
    } BAUDCTRLB = {};

};

} // namespace device
