#ifndef SEAL_HAL_UART_XMEGA
#define SEAL_HAL_UART_XMEGA

#include "gpio.hpp"
#include "peripherals/USART.hpp"
#include "device.hpp"
#include <cstdint>

namespace drivers {

    namespace USART {
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

        using CHAR_SIZE = sfr::USART::CHSIZEv;
        using PARITY_MODE = sfr::USART::PMODEv;
    }   // namespace USART

    template <typename UART_INSTANCE, typename RXD_PIN, typename TXD_PIN>
    class Uart_Basic {
        UART_INSTANCE m_instance;
        RXD_PIN m_rx;
        TXD_PIN m_tx;
    public:
        constexpr Uart_Basic(const UART_INSTANCE instance, const RXD_PIN rxp, const TXD_PIN txp)
            : m_instance(instance), m_rx(rxp), m_tx(txp)
        {}

        template <uint32_t Baud = 9600, bool DoubleSpeed = false>
        constexpr void init(const USART::CHAR_SIZE CharSize = USART::CHAR_SIZE::_8BIT, const USART::PARITY_MODE ParityMode = USART::PARITY_MODE::DISABLED, const bool TwoStopBits = false) const noexcept {
            static_assert(!USART::buad_too_high(Baud, DoubleSpeed), "Chosen baud rate is too high!");
            static_assert(!USART::buad_too_low(Baud, DoubleSpeed), "Chosen baud rate is too low!");

            // RXD_PIN::set_input();
            // RXD_PIN::configure(RXD_PIN::MODE_TOTEM);
            // TXD_PIN::set_output();
            // TXD_PIN::set_low();

            m_instance.BAUDCTRLB = 0;
            m_instance.BAUDCTRLA = 0;
            m_instance.CTRLB.CLK2X = DoubleSpeed;

            // INSTANCE::set_mode_async(CharSizeMode, TwoStopBits, ParityMode);
            // CTRLC::write( static_cast<uint8_t>(ParityMode) << CTRLC::PMODE::SHIFT         // Parity
            //         | TwoStopBits << CTRLC::SBMODE::SHIFT       // Stop Bit Mode
            //         | static_cast<uint8_t>(CharSizeMode)        // Character size
            //         | static_cast<uint8_t>(CMODEv::ASYNCHRONOUS)// Async Polled Mode
            // );
        }

        constexpr void start() const noexcept {
            m_instance.CTRLB |= m_instance.CTRLB.TXEN.shift(true) | m_instance.CTRLB.RXEN.shift(true);
        }

        constexpr void stop() const noexcept {
            m_instance.CTRLB &= ~(m_instance.CTRLB.TXEN.shift(false) | m_instance.CTRLB.RXEN.shift(false));
        }

        /**
         * \brief Read one character from USART_0
         * Function will block if a character is not available.
         * \return Data read from the USART_0 module
         */
        constexpr uint8_t get() const noexcept {
            while (!m_instance.STATUS.RXCIF) {}
            return m_instance.DATA;
        }

        /**
         * \brief Write one character to USART_0
         * Function will block until a character can be accepted.
         * \param[in] data The character to write to the USART
         * \return Nothing
         */
        constexpr void put(const uint8_t data) const noexcept {
            while (!m_instance.STATUS.DREIF) {}
            m_instance.DATA = data;
        }

        constexpr int32_t write(const char* data, const uint16_t len) const noexcept {
            uint16_t i = 0;
            for(; i < len; ++i) {
                put(data[i]);
            }
            return i;
        }

        constexpr int32_t read(char* data, const uint16_t len) const noexcept {
            uint16_t i = 0;
            for(; i < len; ++i) {
                data[i] = get();
            }
            return i;
        }
    };

}   // namesapce device
#endif  // SEAL_HAL_UART_XMEGA
