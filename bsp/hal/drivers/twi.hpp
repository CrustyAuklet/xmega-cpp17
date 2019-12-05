#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

#include "gpio.hpp"
#include "peripherals/USART.hpp"
#include <cstdint>

// ERROR: remove this include!
#include "device.hpp"

namespace drivers {

    namespace TWI {
        constexpr uint8_t get_baud(const uint32_t CpuFreq, const uint32_t Baud, const uint32_t TRise) {
            return ((((((float)CpuFreq / (float)Baud)) - 10 - ((float)CpuFreq * TRise / 1'000'000))) / 2);
        }

        using BUS_STATE = sfr::TWI::MASTER_BUSSTATEv;
        using BUS_TIMEOUT = sfr::TWI::MASTER_TIMEOUTv;
        using SDA_HOLD = sfr::TWI::SDAHOLDv;
        using INT_LVL = sfr::TWI::MASTER_INTLVLv;
    } // namespace TWI

    template <typename TWI_INSTANCE, typename SDA_PIN, typename SCL_PIN>
    class TWI_Basic {
//        I2C_INSTANCE m_instance;
//        SDA_PIN m_sda;
//        SCL_PIN m_scl;
        decltype(device::TWIC) m_instance;  // ERROR: remove this include!
        decltype(device::PC2) m_sda;        // ERROR: remove this include!
        decltype(device::PC3) m_scl;        // ERROR: remove this include!
    public:
        constexpr TWI_Basic(const TWI_INSTANCE instance, const SDA_PIN sdapin, const SCL_PIN sclpin)
            : m_instance(instance), m_sda(sdapin), m_scl(sclpin)
        {}

        template <uint32_t CpuFreq, uint32_t Baud = 100'000, uint32_t TRise = 0>
        constexpr void init() const noexcept {
            // config pins for TWI master
            m_sda.set_output();
            m_sda.set_low();
            m_sda.configure(GPIO::PinConfig::MODE_TOTEM);
            m_scl.set_output();
            m_scl.set_low();
            m_scl.configure(GPIO::PinConfig::MODE_TOTEM);

            m_instance.CTRL = m_instance.CTRL.SDAHOLD.shift(TWI::SDA_HOLD::OFF)   // SDA Holdoff Time
                             | m_instance.CTRL.EDIEN.shift(false);    // External Driver Interface Enable


            m_instance.MASTER.CTRLB = m_instance.MASTER.CTRLB.TIMEOUT.shift(TWI::BUS_TIMEOUT::_200US)   // Bus Timeout Disabled
                                    | m_instance.MASTER.CTRLB.QCEN.shift(true)      // Quick Command Enable: read/write ISR triggered at slave ack
                                    | m_instance.MASTER.CTRLB.SMEN.shift(true);     // Smart Mode Enable: sent immediately after reading DATA register based on ACKACT mode

            // set bus state to unknown and clear RIF and WIF
            m_instance.MASTER.STATUS = m_instance.MASTER.STATUS.BUSSTATE.shift(TWI::BUS_STATE::UNKNOWN)
                                     | m_instance.MASTER.STATUS.WIF.shift(true)
                                     | m_instance.MASTER.STATUS.RIF.shift(true);

            m_instance.MASTER.BAUD = TWI::get_baud(CpuFreq, Baud, TRise);
        }

        /// sets bus state to idle and clears read and write interrupt flags
        constexpr void set_idle() const noexcept {
            const uint8_t state = m_instance.MASTER.STATUS;
            m_instance.MASTER.STATUS = m_instance.MASTER.STATUS.BUSSTATE.shift(TWI::BUS_STATE::IDLE)
                                     | m_instance.MASTER.STATUS.WIF.shift(true)
                                     | m_instance.MASTER.STATUS.RIF.shift(true);
        }

        /// enables the twi module
        constexpr void start() const noexcept {
            m_instance.MASTER.CTRLA.ENABLE = true;
        }

        /// disables the twi module
        constexpr void stop() const noexcept {
            m_instance.MASTER.CTRLA.ENABLE = false;
        }

        /// enables TWI read and write interrupts at the given level
        constexpr void enable_interrupt(const TWI::INT_LVL lvl, const bool read, const bool write) const noexcept {
            m_instance.MASTER.CTRLA |= m_instance.MASTER.CTRLA.INTLVL.shift(lvl)
                                    |  m_instance.MASTER.CTRLA.RIEN.shift(read)
                                    |  m_instance.MASTER.CTRLA.WIEN.shift(write);
        }

        /**
         * This flag is set when a byte is successfully received in master read mode; i.e., no
         * arbitration was lost or bus error occurred during the operation. Writing a one to
         * this bit location will clear RIF. When this flag is set, the master forces the SCL line low,
         * stretching the TWI clock period. Clearing the interrupt flags will release the SCL line.
         *
         * Flag is cleared automatically when: writing to ADDR, writing to DATA, reading DATA,
         * or writing a valid CMD to CTRLC
         * @return TRUE if the read complete flag is set
         */
        constexpr bool read_complete() const noexcept {
            return m_instance.MASTER.STATUS.RIF;
        }

        /**
         * This flag is set when a byte is transmitted in master write mode. The flag is set regardless
         * of the occurrence of a bus error or an arbitration lost condition. WIF is also set if
         * arbitration is lost during sending of a NACK in master read mode, and if issuing a START
         * condition when the bus state is unknown. Writing a one to this bit location will clear WIF.
         * When this flag is set, the master forces the SCL line low, stretching the TWI clock period.
         * Clearing the interrupt flags will release the SCL line.
         * @return TRUE if the Write complete flag is set
         */
        constexpr bool write_complete() const noexcept {
            return m_instance.MASTER.STATUS.WIF;
        }

        /**
         * This flag is set when the master is holding the SCL line low. This is a status flag and
         * a read-only flag that is set when RIF or WIF is set.
         */
        constexpr bool clock_holding() const noexcept {
            return m_instance.MASTER.STATUS.CLKHOLD;
        }

        /// Returns the most recent acknowledge bit from the slave, returning TRUE if that was an ACK
        constexpr bool received_ack() const noexcept {
            // in hardware a 1 means a NACK was received last
            return !m_instance.MASTER.STATUS.RXACK;
        }

        /**
         * This flag is set if arbitration is lost while transmitting a high data bit or a NACK bit,
         * or while issuing a START or repeated START condition on the bus.
         * This can be cleared directly with clear_arbitration_lost() or by writing to the ADDR register.
         * @return TRUE if arbitration was lost during last transmission
         */
        constexpr bool arbitration_lost() const noexcept {
            return m_instance.MASTER.STATUS.ARBLOST;
        }
        /// clears the arbitration lost flag
        constexpr void clear_arbitration_lost() const noexcept {
            m_instance.MASTER.STATUS.ARBLOST = 1;
        }

        /**
         * An illegal bus condition occurs if a  repeated START or a STOP condition is detected, and the number
         * of received or transmitted bits from the previous START condition is not a multiple of nine.
         * This can be cleared directly with clear_bus_error() or by writing to the ADDR register.
         * @return TRUE if an illegal bus condition has occurred
         */
        constexpr bool bus_error() const noexcept {
            return m_instance.MASTER.STATUS.BUSERR;
        }
        /// clears the bus error flag
        constexpr void clear_bus_error() const noexcept {
            m_instance.MASTER.STATUS.BUSERR = 1;
        }

        /// returns the current bus state
        constexpr TWI::BUS_STATE state() const noexcept {
            return m_instance.MASTER.STATUS.BUSSTATE;
        }

        /**
         * The master ADDR can be read at any time without interfering with ongoing bus activity.
         * @return current address set in hardware
         */
        constexpr uint8_t read_address() const noexcept {
            return m_instance.MASTER.ADDR;
        }

        /**
         * When the address (ADDR) register is written with a slave address and the R/W bit while
         * the bus is idle, a START condition is issued and the 7-bit slave address and the R/W bit
         * are transmitted on the bus. If the bus is already owned when ADDR is written, a repeated
         * START is issued. If the previous transaction was a master read and no acknowledge is sent yet,
         * the acknowledge action is sent before the repeated START condition.
         *
         * After completing the  operation and the acknowledge bit from the slave is received, the SCL line
         * is forced low if arbitration was not lost. WIF is set.
         *
         * If the bus state is unknown when ADDR is written, WIF is set and BUSERR is set.
         *
         * All TWI master flags are automatically cleared when ADDR is written. This includes BUSERR,
         * ARBLOST, RIF, and WIF.
         * @return current address set in hardware
         */
        constexpr void write_address(const uint8_t a) const noexcept {
            return m_instance.MASTER.ADDR = a;
        }

        /**
         * The data (DATA) register is used when transmitting and receiving data. During data transfer,
         * data are shifted from/to the DATA register and to/from the bus. This implies that the DATA
         * register cannot be accessed during byte transfers, and this is prevented by hardware.
         * The DATA register can only be accessed when the SCL line is held low by the master;
         * i.e., when CLKHOLD is set.
         *
         * In master read mode, RIF and CLKHOLD are set when one byte is received in the DATA register.
         * If smart mode is enabled, reading the DATA register will trigger the bus operation as set by
         * the ACKACT bit. If a bus error occurs during reception, WIF and BUSERR are set instead of RIF
         * @return byte from the data register
         */
        constexpr uint8_t read_data() const noexcept {
            return m_instance.MASTER.DATA;
        }

        /**
         * The data (DATA) register is used when transmitting and receiving data. During data transfer,
         * data are shifted from/to the DATA register and to/from the bus. This implies that the DATA
         * register cannot be accessed during byte transfers, and this is prevented by hardware.
         * The DATA register can only be accessed when the SCL line is held low by the master;
         * i.e., when CLKHOLD is set.
         *
         * In master write mode, writing the DATA register will trigger a data byte transfer followed by
         * the master receiving the acknowledge bit from the slave. WIF and CLKHOLD are set.
         *
         * @param d [IN] the data to send
         */
        constexpr void write_data(const uint8_t d) const noexcept {
            return m_instance.MASTER.DATA = d;
        }

//        /**
//         * @brief Read one character from USART_0
//         * Function will block if a character is not available.
//         * @return Data read from the USART_0 module
//         */
//        constexpr uint8_t get() const noexcept {
//            while (!m_instance.STATUS.RXCIF) {}
//            return m_instance.DATA;
//        }
//
//        /**
//         * \brief Write one character to USART_0
//         * Function will block until a character can be accepted.
//         * \param[in] data The character to write to the USART
//         * \return Nothing
//         */
//        constexpr void put(const uint8_t data) const noexcept {
//            while (!m_instance.STATUS.DREIF) {}
//            m_instance.DATA = data;
//        }
//
//        constexpr int32_t write(const char* data, const uint16_t len) const noexcept {
//            uint16_t i = 0;
//            for(; i < len; ++i) {
//                put(data[i]);
//            }
//            return i;
//        }
//
//        constexpr int32_t read(char* data, const uint16_t len) const noexcept {
//            uint16_t i = 0;
//            for(; i < len; ++i) {
//                data[i] = get();
//            }
//            return i;
//        }

    };

} // namespace drivers
#pragma clang diagnostic pop