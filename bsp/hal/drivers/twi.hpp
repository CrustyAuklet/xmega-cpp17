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
            return ((((((float)CpuFreq / (float)Baud)) - 10 - ((float)CpuFreq * TRise / 1000000))) / 2);
        }

        using BUS_STATE = sfr::TWI::MASTER_BUSSTATEv;
        using BUS_TIMEOUT = sfr::TWI::MASTER_TIMEOUTv;
        using SDA_HOLD = sfr::TWI::SDAHOLDv;
    } // namespace I2C

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
//            m_sda.set_input();
//            m_sda.configure(GPIO::PushPullConfig::TOTEM);
//            m_scl.set_output();
//            m_scl.set_low();

            m_instance.CTRL = m_instance.CTRL.SDAHOLD.shift(TWI::SDA_HOLD::OFF)   // SDA Holdoff Time
                             | m_instance.CTRL.EDIEN.shift(false);    // External Driver Interface Enable


            m_instance.MASTER.CTRLB = m_instance.MASTER.CTRLB.TIMEOUT.shift(TWI::BUS_TIMEOUT::DISABLED)   // Bus Timeout Disabled
                                    | m_instance.MASTER.CTRLB.QCEN.shift(false)      // Quick Command Enable
                                    | m_instance.MASTER.CTRLB.SMEN.shift(false);     // Smart Mode Enable

            m_instance.MASTER.STATUS = m_instance.MASTER.STATUS.BUSSTATE.shift(TWI::BUS_STATE::UNKNOWN);

            m_instance.MASTER.BAUD = TWI::get_baud(CpuFreq, Baud, TRise);

//            m_instance.MASTER.CTRLA = m_instance.MASTER.CTRLA.INTLVL.shift()    // interrupt level
//                                    | m_instance.MASTER.CTRLA.RIEN.shift()    // read interrupt enable
//                                    | m_instance.MASTER.CTRLA.WIEN.shift()    // write interrupt enable
//                                    | m_instance.MASTER.CTRLA.ENABLE.shift();   // TWI Master enable
        }

        constexpr void set_idle() const noexcept {
            const uint8_t state = m_instance.MASTER.STATUS;
            m_instance.MASTER.STATUS = m_instance.MASTER.STATUS.BUSSTATE.shift(TWI::BUS_STATE::IDLE);
        }

        constexpr void start() const noexcept {
            m_instance.MASTER.CTRLA.ENABLE = true;
        }

        constexpr void stop() const noexcept {
            m_instance.MASTER.CTRLA.ENABLE = false;
        }

        constexpr TWI::BUS_STATE state() const noexcept {
            return m_instance.MASTER.STATUS.BUSSTATE;
        }

        constexpr bool ready() const noexcept {
            return m_instance.MASTER.STATUS.;
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

} // namespace drivers
#pragma clang diagnostic pop