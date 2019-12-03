/**
 * XMEGAAU-USART (id I6090)
 * Universal Asynchronous Receiver-Transmitter
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

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
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
    } DATA = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<STATUS_t, 7, 7, bool> RXCIF = {};    //< Receive Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 6, 6, bool> TXCIF = {};    //< Transmit Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 5, 5, bool> DREIF = {};    //< Data Register Empty Flag
        static constexpr bitfield_t<STATUS_t, 4, 4, bool> FERR = {};    //< Frame Error
        static constexpr bitfield_t<STATUS_t, 3, 3, bool> BUFOVF = {};    //< Buffer Overflow
        static constexpr bitfield_t<STATUS_t, 2, 2, bool> PERR = {};    //< Parity Error
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> RXB8 = {};    //< Receive Bit 8
    } STATUS = {};

    /// Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<CTRLA_t, 5, 4, USART::RXCINTLVLv> RXCINTLVL = {};    //< Receive Interrupt Level
        static constexpr bitfield_t<CTRLA_t, 3, 2, USART::TXCINTLVLv> TXCINTLVL = {};    //< Transmit Interrupt Level
        static constexpr bitfield_t<CTRLA_t, 1, 0, USART::DREINTLVLv> DREINTLVL = {};    //< Data Register Empty Interrupt Level
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<CTRLB_t, 4, 4, bool> RXEN = {};    //< Receiver Enable
        static constexpr bitfield_t<CTRLB_t, 3, 3, bool> TXEN = {};    //< Transmitter Enable
        static constexpr bitfield_t<CTRLB_t, 2, 2, bool> CLK2X = {};    //< Double transmission speed
        static constexpr bitfield_t<CTRLB_t, 1, 1, bool> MPCM = {};    //< Multi-processor Communication Mode
        static constexpr bitfield_t<CTRLB_t, 0, 0, bool> TXB8 = {};    //< Transmit bit 8
    } CTRLB = {};

    /// Control Register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
        static constexpr bitfield_t<CTRLC_t, 7, 6, USART::CMODEv> CMODE = {};    //< Communication Mode
        static constexpr bitfield_t<CTRLC_t, 5, 4, USART::PMODEv> PMODE = {};    //< Parity Mode
        static constexpr bitfield_t<CTRLC_t, 3, 3, bool> SBMODE = {};    //< Stop Bit Mode
        static constexpr bitfield_t<CTRLC_t, 2, 0, USART::CHSIZEv> CHSIZE = {};    //< Character Size
    } CTRLC = {};

    /// Baud Rate Control Register A - 1 bytes
    static constexpr struct BAUDCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
        static constexpr bitfield_t<BAUDCTRLA_t, 7, 0> BSEL = {};    //< Baud Rate Selection Bits [7:0]
    } BAUDCTRLA = {};

    /// Baud Rate Control Register B - 1 bytes
    static constexpr struct BAUDCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0007>::operator=;
        static constexpr bitfield_t<BAUDCTRLB_t, 7, 4> BSCALE = {};    //< Baud Rate Scale
        static constexpr bitfield_t<BAUDCTRLB_t, 3, 0> BSEL = {};    //< Baud Rate Selection bits[11:8]
    } BAUDCTRLB = {};

    // USART ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        RXC = 0, // Reception Complete Interrupt
        DRE = 1, // Data Register Empty Interrupt
        TXC = 2, // Transmission Complete Interrupt
    };
};

} // namespace sfr
