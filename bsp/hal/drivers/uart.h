#ifndef SEAL_HAL_UART_XMEGA
#define SEAL_HAL_UART_XMEGA

#include "device.hpp"
#include <cstdint>

namespace drivers {

    template <typename UART_INSTANCE, typename RXD_PIN, typename TXD_PIN>
    class Uart_Basic {
        typedef UART_INSTANCE INSTANCE;
    public:
        typedef typename INSTANCE::RXCINTLVLv RX_INTLVLv;     // enum of RX interrupt level settings
        typedef typename INSTANCE::TXCINTLVLv TX_INTLVLv;     // enum of TX interrupt level settings
        typedef typename INSTANCE::DREINTLVLv DRE_INTLVLv;    // enum of DRE interrupt level settings
        typedef typename INSTANCE::CHSIZEv    CHSIZEv;        // Character Size Options
        typedef typename INSTANCE::CMODEv     CMODEv;         // USART Peripheral Mode Options
        typedef typename INSTANCE::PMODEv     PMODEv;         // Parity Mode Options

        template <uint32_t Baud = 9600, bool DoubleSpeed = false>
        static void init(const CHSIZEv CharSizeMode = CHSIZEv::_8BIT, const bool TwoStopBits = false, const PMODEv ParityMode = PMODEv::EVEN) {
            INSTANCE::template init_async_pins<RXD_PIN, TXD_PIN>();
            INSTANCE::template set_baud<Baud, DoubleSpeed>();
            INSTANCE::set_mode_async(CharSizeMode, TwoStopBits, ParityMode);
        }

        static void start() {
            INSTANCE::enable();
        }

        static void stop() {
            INSTANCE::disable();
        }

        /**
         * \brief Read one character from USART_0
         * Function will block if a character is not available.
         * \return Data read from the USART_0 module
         */
        static uint8_t get() {
            while (!INSTANCE::rx_ready()) {}
            return INSTANCE::DATA::read();
        }

        /**
         * \brief Write one character to USART_0
         * Function will block until a character can be accepted.
         * \param[in] data The character to write to the USART
         * \return Nothing
         */
        static void put(const uint8_t data) {
            while (!INSTANCE::tx_ready()) {}
            INSTANCE::DATA::write(data);
        }

        static int32_t write(const char* data, const uint16_t len) {
            uint16_t i = 0;
            for(; i < len; ++i) {
                put(data[i]);
            }
            return i;
        }

        static int32_t read(char* data, const uint16_t len) {
            uint16_t i = 0;
            for(; i < len; ++i) {
                data[i] = get();
            }
            return i;
        }
    };

}   // namesapce device
#endif  // SEAL_HAL_UART_XMEGA
