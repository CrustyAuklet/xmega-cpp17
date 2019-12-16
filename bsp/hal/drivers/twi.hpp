#pragma once
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "readability-static-accessed-through-instance"
#endif

#include "device.hpp"       // need this to forward the enum definitions
#include "pin_types.hpp"    // for pin type static checks
#include <cstdint>

namespace drivers {

    namespace TWI {
        constexpr uint8_t get_baud(const uint32_t CpuFreq, const uint32_t Baud, const uint32_t TRise) {
            return ((((((float)CpuFreq / (float)Baud)) - 10 - ((float)CpuFreq * TRise / 1'000'000))) / 2);
        }

        using BUS_STATE = sfr::TWI::MASTER_BUSSTATEv;
        using BUS_TIMEOUT = sfr::TWI::MASTER_TIMEOUTv;
        using SDA_HOLD = sfr::TWI::SDAHOLDv;
        using INT_LVL = sfr::TWI::MASTER_INTLVLv;
        using MASTER_CMD = sfr::TWI::MASTER_CMDv;

        enum class TWI_ERROR : uint8_t { NACK, ARBITRATION_LOST, BUS_ERROR };

		// TODO: Improve this status class API
        struct MasterStatus {
            uint8_t twi_status_byte;

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
                return twi_status_byte & (1U<<7U);
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
                return twi_status_byte & (1U<<6U);;
            }

            /**
             * This flag is set when the master is holding the SCL line low. This is a status flag and
             * a read-only flag that is set when RIF or WIF is set.
             */
            constexpr bool clock_holding() const noexcept {
                return twi_status_byte & (1U<<5U);
            }

            /// Returns the most recent acknowledge bit from the slave, returning TRUE if that was an ACK
            constexpr bool received_nack() const noexcept {
                // in hardware a 1 means a NACK was received last
                return twi_status_byte & (1U<<4U);
            }

            /**
             * This flag is set if arbitration is lost while transmitting a high data bit or a NACK bit,
             * or while issuing a START or repeated START condition on the bus.
             * This can be cleared directly with clear_arbitration_lost() or by writing to the ADDR register.
             * @return TRUE if arbitration was lost during last transmission
             */
            constexpr bool arbitration_lost() const noexcept {
                return twi_status_byte & (1U<<3U);
            }

            /**
             * An illegal bus condition occurs if a  repeated START or a STOP condition is detected, and the number
             * of received or transmitted bits from the previous START condition is not a multiple of nine.
             * This can be cleared directly with clear_bus_error() or by writing to the ADDR register.
             * @return TRUE if an illegal bus condition has occurred
             */
            constexpr bool bus_error() const noexcept {
                return twi_status_byte & (1U<<2U);
            }

            /// returns the current bus state
            constexpr TWI::BUS_STATE state() const noexcept {
                return static_cast<TWI::BUS_STATE>(twi_status_byte & 0x03U);
            }

            /// returns true if any write error occured
            constexpr bool write_error() const noexcept {
                return twi_status_byte & (0x1CU);    // mask for NACK, arbitration lost, or bus error
            }
        };

    } // namespace TWI

    template <typename TWI_INSTANCE, typename SDA_PIN, typename SCL_PIN>
    class TWI_Master_Basic {
        TWI_INSTANCE m_instance;
        SDA_PIN m_sda;
        SCL_PIN m_scl;
//        decltype(device::TWIC) m_instance;  // NOTE: This is only to assist in auto-complete. Comment out for compile.
//        decltype(device::PC2) m_sda;        // NOTE: This is only to assist in auto-complete. Comment out for compile.
//        decltype(device::PC3) m_scl;        // NOTE: This is only to assist in auto-complete. Comment out for compile.
    public:
        constexpr TWI_Master_Basic(const TWI_INSTANCE instance, const SDA_PIN sdapin, const SCL_PIN sclpin)
            : m_instance(instance), m_sda(sdapin), m_scl(sclpin)
        {}

        template <uint32_t CpuFreq, uint32_t Baud = 100'000, uint32_t TRise = 0>
        constexpr void start() const noexcept {
            m_instance.CTRL = m_instance.CTRL.SDAHOLD.shift(TWI::SDA_HOLD::OFF)   // SDA Holdoff Time
                             | m_instance.CTRL.EDIEN.shift(false);    // External Driver Interface Enable


            m_instance.MASTER.CTRLB = m_instance.MASTER.CTRLB.TIMEOUT.shift(TWI::BUS_TIMEOUT::_200US)   // Bus Timeout Disabled
                                    | m_instance.MASTER.CTRLB.QCEN.shift(false)      // Quick Command Enable: read/write ISR triggered at slave ack
                                    | m_instance.MASTER.CTRLB.SMEN.shift(false);     // Smart Mode Enable: sent immediately after reading DATA register based on ACKACT mode

            // set bus state to unknown and clear RIF and WIF
            m_instance.MASTER.STATUS = m_instance.MASTER.STATUS.BUSSTATE.shift(TWI::BUS_STATE::UNKNOWN)
                                     | m_instance.MASTER.STATUS.WIF.shift(true)
                                     | m_instance.MASTER.STATUS.RIF.shift(true);

            m_instance.MASTER.BAUD = TWI::get_baud(CpuFreq, Baud, TRise);
            m_instance.MASTER.CTRLA.ENABLE = true;
        }

        /// disables the twi module
        constexpr void stop() const noexcept {
            // disable peripheral
            m_instance.MASTER.CTRLA.ENABLE = false;
        }

        /// sets bus state to idle and clears read and write interrupt flags
        constexpr void set_idle() const noexcept {
            const uint8_t state = m_instance.MASTER.STATUS;
            m_instance.MASTER.STATUS = m_instance.MASTER.STATUS.BUSSTATE.shift(TWI::BUS_STATE::IDLE)
                                       | m_instance.MASTER.STATUS.WIF.shift(true)
                                       | m_instance.MASTER.STATUS.RIF.shift(true);
        }

        /// enables TWI read and write interrupts at the given level
        constexpr void enable_interrupt(const TWI::INT_LVL lvl, const bool read, const bool write) const noexcept {
            m_instance.MASTER.CTRLA |= m_instance.MASTER.CTRLA.INTLVL.shift(lvl)
                                    |  m_instance.MASTER.CTRLA.RIEN.shift(read)
                                    |  m_instance.MASTER.CTRLA.WIEN.shift(write);
        }

        constexpr TWI::MasterStatus get_status() const noexcept {
            return {m_instance.MASTER.STATUS};
        }

        /// clears the arbitration lost flag
        constexpr void clear_arbitration_lost() const noexcept {
            m_instance.MASTER.STATUS.ARBLOST = 1;
        }

        /// clears the bus error flag
        constexpr void clear_bus_error() const noexcept {
            m_instance.MASTER.STATUS.BUSERR = 1;
        }

        /// clears the write complete interrupt
        constexpr void clear_write_interrupt() const noexcept {
            m_instance.MASTER.STATUS.WIF = 1;
        }

        /// clears the read complete interrupt
        constexpr void clear_read_interrupt() const noexcept {
            m_instance.MASTER.STATUS.RIF = 1;
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
         */
        template<bool SevenBitAddress=false>
        constexpr void write_address(uint8_t address, const bool read = false) const noexcept {
            if constexpr (SevenBitAddress) {
                address <<= 1U;
            }
            m_instance.MASTER.ADDR = (address | static_cast<uint8_t>(read));
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
		 * @param last_byte [IN] If false then the read will be automatically ACKed and the next byte will be read. 
		 *						 If TRUE then no action is taken, just a simple read
         * @return byte from the data register
         */
        constexpr uint8_t read_data(const bool last_byte = false) const noexcept {
			const uint8_t data = m_instance.MASTER.DATA;
            if(!last_byte) {
                m_instance.MASTER.CTRLC = m_instance.MASTER.CTRLC.CMD.shift(TWI::MASTER_CMD::RECVTRANS);
            }
            return data;
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
            m_instance.MASTER.DATA = d;
        }

        /// set stop condition on the bus, with or without a preceding NACK
        constexpr void send_stop(const bool NACK = false) const noexcept {
            m_instance.MASTER.CTRLC = m_instance.MASTER.CTRLC.ACKACT.shift(NACK) | m_instance.MASTER.CTRLC.CMD.shift(TWI::MASTER_CMD::STOP);
        }
		
		/// set a repeated start condition on the bus. With or without a preceding NACK.
		constexpr void send_restart(const bool NACK = false) const noexcept {
			m_instance.MASTER.CTRLC = m_instance.MASTER.CTRLC.ACKACT.shift(NACK) | m_instance.MASTER.CTRLC.CMD.shift(TWI::MASTER_CMD::REPSTART);
		}

        /// send a buffer of data to the given address
        template<bool SevenBitAddress=false>
        constexpr uint16_t write(const uint8_t addr, const uint8_t* data, const uint16_t length, const bool stop = true) const noexcept {
            write_address<SevenBitAddress>(addr);
            uint16_t timeout = 1000;
            while(!get_status().write_complete() && --timeout){}
            if(get_status().write_error() || !timeout) {
                send_stop(true);
                return 0;
            }

            uint16_t count = 0;
            while(count < length) {
                write_data(data[count]);
                timeout = 1000;
                while(!get_status().write_complete() && --timeout) {}
                if(get_status().write_error() || !timeout) {
                    send_stop(true);
                    return count;
                }
                ++count;
            }

            if(stop) {
                send_stop();
            }
            return count;
        }

        /// read a buffer of data
        template<bool SevenBitAddress=false>
        constexpr uint16_t read(const uint8_t addr, uint8_t* data, const uint16_t length) const noexcept {
            // start a read operation
            write_address<SevenBitAddress>(addr, true);
            uint16_t count = 0;
            uint16_t timeout = 1000;

            while(count < length) {
                while(!get_status().read_complete() && --timeout){}
                if(get_status().write_error() || !timeout) {
                    send_stop(true);
                    return 0;
                }
				
                const bool last_byte = (count == length-1);
                data[count] = read_data(last_byte);
                ++count;
            }
			send_stop(true);
            timeout = 1000;
            while(get_status().state() != TWI::BUS_STATE::IDLE  && --timeout) {}
            if(!timeout) {
                set_idle();
            }
            return count;
        }

        template<bool SevenBitAddress=false>
        constexpr uint8_t read_reg8(const uint8_t addr, const uint8_t reg_addr) const noexcept {
            const uint8_t c1 = write(addr, &reg_addr, 1, false);
            if(c1 != 1) {
                return 0;
            }

            uint8_t retVal = 0;
            const uint8_t c2 = read(addr, &retVal, 1);
            return c2 != 1 ? 0 : retVal;
        }

        template<bool SevenBitAddress=false>
        constexpr bool write_reg8(const uint8_t addr, const uint8_t reg_addr, const uint8_t data) const noexcept {
            const uint8_t buf[2] = {reg_addr, data};
            const uint8_t c = write(addr, buf, 2);
            return c == 2;
        }

    };

} // namespace drivers

#if __clang__
#pragma clang diagnostic pop
#endif
