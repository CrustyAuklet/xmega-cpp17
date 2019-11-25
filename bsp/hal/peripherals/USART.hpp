/**
 * XMEGAAU-USART (id I6090)
 * Universal Asynchronous Receiver-Transmitter
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

    constexpr bool buad_too_high(const uint32_t Baud, const bool doublespeed) {
        return doublespeed ? (Baud > F_CPU / 8U) : (Baud > F_CPU / 8U*2U);
    }

    constexpr bool buad_too_low(const uint32_t Baud, const bool doublespeed) {
        return doublespeed ? (Baud < F_CPU / 4194304UL) : (Baud < F_CPU / 4194304UL*2UL );
    }

    /// calculates the baud settings for UART with BAUDCTRLA in the MSB of the return value and BAUDCTRLB in the LSB
    constexpr uint16_t get_baud(const uint32_t Baud) {
        // Find the lowest possible exponent.
        uint32_t cpu_hz = F_CPU;
        uint32_t limit  = 0xfffU >> 4;
        const uint32_t ratio  = F_CPU / Baud;
        int8_t exp = -7;
        while (exp < 7) {
            if (ratio < limit) {
                break;
            }
            limit <<= 1;
            if (exp < -3) {
                limit |= 1;
            }
            exp++;
        }
        //
        // Depending on the value of exp, scale either the input frequency or the target baud rate.
        // By always scaling upwards, we never introduce any additional inaccuracy.
        //
        // We are including the final divide-by-8 (aka. right-shift-by-3) in this operation as it
        // ensures that we never exceeed 2**32 at any point.
        //
        // The formula for calculating BSEL is slightly different when exp is negative than it is when exp is positive.
        uint32_t div = 0;
        if (exp < 0) {
            // We are supposed to subtract 1, then apply BSCALE. We want to apply BSCALE first,
            // so we need to turn everything inside the parenthesis into a single fractional expression.
            cpu_hz -= 8 * Baud;

            // If we end up with a left-shift after taking the final divide-by-8 into account, do the shift before the divide.
            // Otherwise, left-shift the denominator instead (effectively resulting in an overall right shift.)
            if (exp <= -3) {
                div = ((cpu_hz << (-exp - 3)) + Baud / 2) / Baud;
            } else {
                const uint32_t baudShift = Baud << (exp + 3);
                div = (cpu_hz + baudShift / 2) / baudShift;
            }
        } else {
            // We will always do a right shift in this case,
            // but we need to shift three extra positions because of the divide-by-8.
            const uint32_t baudShift = Baud << (exp + 3);
            div = (cpu_hz + baudShift / 2) / baudShift - 1;
        }

        const uint8_t buad_ctrl_a = div;
        const uint8_t buad_ctrl_b = (((div >> 8) & 0X0F) | (exp << 4));
        return buad_ctrl_a<<8 | buad_ctrl_b;
    }

/**
 * USART
 * Universal Synchronous/Asynchronous Receiver/Transmitter
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct USART_t {

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

    /// Data Register - 1 bytes
    struct DATA : public reg8_t<BASE_ADDRESS + 0x0000> {
    };

    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0001> {
        using RXCIF = reg_field_t<BASE_ADDRESS + 0x0001, 0x80, 7>;    //< Receive Interrupt Flag
        using TXCIF = reg_field_t<BASE_ADDRESS + 0x0001, 0x40, 6>;    //< Transmit Interrupt Flag
        using DREIF = reg_field_t<BASE_ADDRESS + 0x0001, 0x20, 5>;    //< Data Register Empty Flag
        using FERR = reg_field_t<BASE_ADDRESS + 0x0001, 0x10, 4>;    //< Frame Error
        using BUFOVF = reg_field_t<BASE_ADDRESS + 0x0001, 0x08, 3>;    //< Buffer Overflow
        using PERR = reg_field_t<BASE_ADDRESS + 0x0001, 0x04, 2>;    //< Parity Error
        using RXB8 = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Receive Bit 8
    };

    /// Control Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0003> {
        using RXCINTLVL = reg_field_t<BASE_ADDRESS + 0x0003, 0x30, 4, RXCINTLVLv>;    //< Receive Interrupt Level
        using TXCINTLVL = reg_field_t<BASE_ADDRESS + 0x0003, 0x0C, 2, TXCINTLVLv>;    //< Transmit Interrupt Level
        using DREINTLVL = reg_field_t<BASE_ADDRESS + 0x0003, 0x03, 0, DREINTLVLv>;    //< Data Register Empty Interrupt Level
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0004> {
        using RXEN = reg_field_t<BASE_ADDRESS + 0x0004, 0x10, 4>;    //< Receiver Enable
        using TXEN = reg_field_t<BASE_ADDRESS + 0x0004, 0x08, 3>;    //< Transmitter Enable
        using CLK2X = reg_field_t<BASE_ADDRESS + 0x0004, 0x04, 2>;    //< Double transmission speed
        using MPCM = reg_field_t<BASE_ADDRESS + 0x0004, 0x02, 1>;    //< Multi-processor Communication Mode
        using TXB8 = reg_field_t<BASE_ADDRESS + 0x0004, 0x01, 0>;    //< Transmit bit 8
    };

    /// Control Register C - 1 bytes
    struct CTRLC : public reg8_t<BASE_ADDRESS + 0x0005> {
        using CMODE = reg_field_t<BASE_ADDRESS + 0x0005, 0xC0, 6, CMODEv>;    //< Communication Mode
        using PMODE = reg_field_t<BASE_ADDRESS + 0x0005, 0x30, 4, PMODEv>;    //< Parity Mode
        using SBMODE = reg_field_t<BASE_ADDRESS + 0x0005, 0x08, 3>;    //< Stop Bit Mode
        using CHSIZE = reg_field_t<BASE_ADDRESS + 0x0005, 0x07, 0, CHSIZEv>;    //< Character Size
    };

    /// Baud Rate Control Register A - 1 bytes
    struct BAUDCTRLA : public reg8_t<BASE_ADDRESS + 0x0006> {
        using BSEL = reg_field_t<BASE_ADDRESS + 0x0006, 0xFF, 0>;    //< Baud Rate Selection Bits [7:0]
    };

    /// Baud Rate Control Register B - 1 bytes
    struct BAUDCTRLB : public reg8_t<BASE_ADDRESS + 0x0007> {
        using BSCALE = reg_field_t<BASE_ADDRESS + 0x0007, 0xF0, 4>;    //< Baud Rate Scale
        using BSEL = reg_field_t<BASE_ADDRESS + 0x0007, 0x0F, 0>;    //< Baud Rate Selection bits[11:8]
    };

    /************************************* Helper Fucntions *************************************/

    /// set the baud rate with compile time constant values and checking
    template <uint32_t Baud = 9600, bool DoubleSpeed = false>
    static void set_baud() {
        static_assert( !buad_too_high(Baud, DoubleSpeed), "Baud speed for UART is too high!");
        static_assert( !buad_too_low(Baud, DoubleSpeed), "Baud speed for UART is too low!");

        BAUDCTRLB::write( get_baud(Baud)&0xFF );
        BAUDCTRLA::write( get_baud(Baud)>>8 );
        CTRLB::CLK2X::write(DoubleSpeed);
    }

    /// init RX and TX pins to the proper state
    template < typename RXD_PIN, typename TXD_PIN >
    static void init_async_pins() {
        RXD_PIN::set_input();
        RXD_PIN::configure(RXD_PIN::MODE_TOTEM);
        TXD_PIN::set_output();
        TXD_PIN::set_low();
    }

    /// set the port mode: Char size, parity, and stop bits. 8N1 by default
    static void set_mode_async(const CHSIZEv CharSizeMode = CHSIZEv::_8BIT, const bool TwoStopBits = false, const PMODEv ParityMode = PMODEv::EVEN) {
        CTRLC::write( static_cast<uint8_t>(ParityMode) << CTRLC::PMODE::SHIFT         // Parity
                    | TwoStopBits << CTRLC::SBMODE::SHIFT       // Stop Bit Mode
                    | static_cast<uint8_t>(CharSizeMode)        // Character size
                    | static_cast<uint8_t>(CMODEv::ASYNCHRONOUS)// Async Polled Mode
        );
    }

    /// Enables the USART module by setting the RX and TX enable-bits in the USART control register
    static void enable_tx() {
        CTRLB::TXEN::write(1);
    }

    /// Enables the USART module by setting the RX enable-bit in the USART control register
    static void enable_rx() {
        CTRLB::RXEN::write(1);
    }

    /// Enables the USART module by setting the TX enable-bit in the USART control register
    static void enable() {
        CTRLB::write( CTRLB::read() | CTRLB::TXEN::BIT_MASK | CTRLB::RXEN::BIT_MASK );
    }

    /// Disables the USART module by clearing the enable-bit(s) in the USART control register
    static void disable() {
        CTRLB::write( CTRLB::read() & ~(CTRLB::TXEN::BIT_MASK | CTRLB::RXEN::BIT_MASK) );
    }

    /**
     * \brief Get recieved data from USART_0
     * \return Data register from USART_0 module
     */
    static uint8_t get_data() {
        return DATA::read();
    }

    static void write_data(const uint8_t d) {
        DATA::write(d);
    }

    /**
     * \brief Check if the usart can accept data to be transmitted
     * \return The status of USART TX data ready check
     * \retval false The USART can not receive data to be transmitted
     * \retval true The USART can receive data to be transmitted
     */
    static bool tx_ready() {
        return STATUS::DREIF::read();
    }

    /**
     * \brief Check if the USART has received data
     * \return The status of USART RX data ready check
     * \retval true The USART has received data
     * \retval false The USART has not received data
     */
    static bool rx_ready() {
        return STATUS::RXCIF::read();
    }

    /**
     * \brief Check if USART_0 data is transmitted
     * \return Receiver ready status
     * \retval true  Data is not completely shifted out of the shift register
     * \retval false Data completely shifted out if the USART shift register
     */
    static bool tx_busy() {
        return !STATUS::TXCIF::read();
    }
};

} // namespace device
