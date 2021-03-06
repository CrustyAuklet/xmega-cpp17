#pragma once
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "readability-static-accessed-through-instance"
#endif

#include "device.hpp"       // need this to forward the enum definitions
#include "pin_types.hpp"    // for pin type static checks
#include "nonstd/expected.hpp"     // std::expected implementation for safe return value
#include "nonstd/span.hpp"         // span for non-owning range based read/write functions
#include <initializer_list>
#include <cstdint>

namespace drivers {

    namespace USART {
        constexpr bool buad_too_high(const uint32_t CpuFreq, const uint32_t Baud, const bool doublespeed) {
            return doublespeed ? (Baud > CpuFreq / 8U) : (Baud > CpuFreq / 8U*2U);
        }

        constexpr bool buad_too_low(const uint32_t CpuFreq, const uint32_t Baud, const bool doublespeed) {
            return doublespeed ? (Baud < CpuFreq / 4'194'304UL) : (Baud < CpuFreq / 4'194'304UL*2UL );
        }

        /// calculates the baud settings for UART with BAUDCTRLA in the MSB of the return value and BAUDCTRLB in the LSB
        constexpr uint16_t get_baud(uint32_t CpuFreq, const uint32_t Baud) {
            // Find the lowest possible exponent.
            const uint32_t ratio  = CpuFreq / Baud;
            uint32_t limit  = 0xfffU >> 4U;
            int8_t exp = -7;
            while (exp < 7) {
                if (ratio < limit) {
                    break;
                }
                limit <<= 1U;
                if (exp < -3) {
                    limit |= 1U;
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
                CpuFreq -= 8 * Baud;

                // If we end up with a left-shift after taking the final divide-by-8 into account, do the shift before the divide.
                // Otherwise, left-shift the denominator instead (effectively resulting in an overall right shift.)
                if (exp <= -3) {
                    div = ((CpuFreq << (-exp - 3)) + Baud / 2) / Baud;
                } else {
                    const uint32_t baudShift = Baud << (exp + 3);
                    div = (CpuFreq + baudShift / 2) / baudShift;
                }
            } else {
                // We will always do a right shift in this case,
                // but we need to shift three extra positions because of the divide-by-8.
                const uint32_t baudShift = Baud << (exp + 3);
                div = (CpuFreq + baudShift / 2) / baudShift - 1;
            }

            const uint8_t baud_ctrl_a = div;
            const uint8_t baud_ctrl_b = (((div >> 8U) & 0x0F) | (exp << 4U));
            return baud_ctrl_a<<8U | baud_ctrl_b;
        }

        using CHAR_SIZE = sfr::USART::CHSIZEv;
        using PARITY_MODE = sfr::USART::PMODEv;

        /// list of UART errors for external consumers.
        /// Internal implementation (numbers) are NOT stable
        enum class error : uint8_t {
            TIMEOUT = (1U<<7U),
            FRAME_ERROR = (1U<<4U),
            BUFFER_OVERFLOW = (1U<<3U),
            PARITY_ERROR = (1U<<2U),
            NONE = (1U<<0U)
        };
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

        template <uint32_t CpuFreq, uint32_t Baud = 9600, bool DoubleSpeed = false>
        constexpr void start(const USART::CHAR_SIZE CharSize = USART::CHAR_SIZE::_8BIT, const USART::PARITY_MODE ParityMode = USART::PARITY_MODE::DISABLED, const bool TwoStopBits = false) const noexcept {
            static_assert(!USART::buad_too_high(CpuFreq, Baud, DoubleSpeed), "Chosen baud rate is too high!");
            static_assert(!USART::buad_too_low(CpuFreq, Baud, DoubleSpeed), "Chosen baud rate is too low!");
            m_instance.BAUDCTRLA = USART::get_baud(CpuFreq, Baud) >> 8U;
            m_instance.BAUDCTRLB = USART::get_baud(CpuFreq, Baud) & 0xFFU;
            m_instance.CTRLB.CLK2X = DoubleSpeed;

            m_instance.CTRLC = m_instance.CTRLC.PMODE.shift(ParityMode)
                               | m_instance.CTRLC.SBMODE.shift(TwoStopBits)
                               | m_instance.CTRLC.CHSIZE.shift(CharSize)
                               | m_instance.CTRLC.CMODE.shift(sfr::USART::CMODEv::ASYNCHRONOUS);
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

        [[nodiscard]] constexpr nonstd::expected<uint16_t, USART::error>
        write(std::initializer_list<const uint8_t> data) const noexcept {
            for(const uint8_t& d : data) {
                put(d);
            }
            return data.size();
        }

        [[nodiscard]] constexpr nonstd::expected<uint16_t, USART::error>
        read(nonstd::span<uint8_t> buffer) const noexcept {
            for(uint8_t& d : buffer) {
                d = get();
            }
            return buffer.size();
        }
    };

}   // namesapce device

#if __clang__
#pragma clang diagnostic pop
#endif
