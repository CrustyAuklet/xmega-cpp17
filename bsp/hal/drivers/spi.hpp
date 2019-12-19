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

    namespace SPI {
        using INT_LVL = sfr::SPI::INTLVLv;
        using MODE = sfr::SPI::MODEv;
        using PRESCALER = sfr::SPI::PRESCALERv;

        constexpr uint8_t calculate_clock(const uint32_t CpuFreq, const uint32_t max_baud) {
            const uint8_t flag_2x = 1U << 7U;
            if(CpuFreq/2 < max_baud) { return static_cast<uint8_t>(PRESCALER::DIV4) | flag_2x; }
            if(CpuFreq/4 < max_baud) { return static_cast<uint8_t>(PRESCALER::DIV4); }
            if(CpuFreq/8 < max_baud) { return static_cast<uint8_t>(PRESCALER::DIV16) | flag_2x; }
            if(CpuFreq/16 < max_baud) { return static_cast<uint8_t>(PRESCALER::DIV16); }
            if(CpuFreq/32 < max_baud) { return static_cast<uint8_t>(PRESCALER::DIV64) | flag_2x; }
            if(CpuFreq/64 < max_baud) { return static_cast<uint8_t>(PRESCALER::DIV64); }
            if(CpuFreq/128 < max_baud) { return static_cast<uint8_t>(PRESCALER::DIV128); }
        }

        struct MasterStatus {
            uint8_t spi_status_byte;
            /**
             * This flag is set when a serial transfer is complete and one byte is completely shifted in/out
             * of the DATA register. If SS is configured as input and is driven low when the SPI is in master mode,
             * this will also set this flag. IF is cleared by hardware when executing the corresponding interrupt
             * vector. Alternatively, the IF flag can be cleared by first reading the STATUS register when IF is
             * set, and then accessing the DATA register
             * @return TRUE if the interrupt flag is set
             */
            constexpr bool interrupt_flag() const noexcept {
                return spi_status_byte & (1U<<7U);
            }

            /**
             * The WRCOL flag is set if the DATA register is written during a data transfer.
             * This flag is cleared by first reading the STATUS register when WRCOL is set,
             * and then accessing the DATA register.
             * @return TRUE if the Write collision flag is set
             */
            constexpr bool write_collision() const noexcept {
                return spi_status_byte & (1U<<6U);;
            }
        };

        /// list of SPI errors for external consumers.
        /// Internal implementation (numbers) are NOT stable
        enum class error : uint8_t {
            TIMEOUT = (1U<<7U),
            COLLISION = (1U<<6U),
            NONE = (1U<<0U)
        };
    } // namespace SPI

    template <typename SPI_INSTANCE, typename MISO_PIN, typename MOSI_PIN, typename SCK_PIN, typename CS_PIN>
    class SPI_Master_Basic {
        SPI_INSTANCE m_instance;
        MISO_PIN m_miso;
        MOSI_PIN m_mosi;
        SCK_PIN  m_sck;
        CS_PIN   m_cs;
//        decltype(device::SPIC) m_instance;  // NOTE: This is only to assist in auto-complete. Comment out for compile.
//        decltype(device::PC2) m_cs;        // NOTE: This is only to assist in auto-complete. Comment out for compile.
    public:
        constexpr SPI_Master_Basic(const SPI_INSTANCE instance, const MISO_PIN miso, const MOSI_PIN mosi, const SCK_PIN sck, const CS_PIN cs)
            : m_instance(instance), m_miso(miso), m_mosi(mosi), m_sck(sck), m_cs(cs)
        {}

        /// enables the twi module
        template <uint32_t CpuFreq, uint32_t MaxBaud = 9600>
        constexpr void start(SPI::MODE Mode=SPI::MODE::_0, bool LSBFirst=false) const noexcept {
            static_assert(MaxBaud > CpuFreq/128, "Max Baud is too low! CPU / 128 can't get low enough!");
            constexpr uint8_t clk_config = SPI::calculate_clock(CpuFreq, 1'000'000U);
            m_instance.CTRL = clk_config
                            | m_instance.CTRL.ENABLE.shift(true)
                            | m_instance.CTRL.DORD.shift(LSBFirst)
                            | m_instance.CTRL.MASTER.shift(true)
                            | m_instance.CTRL.MODE.shift(Mode);
        }

        /// disables the twi module
        constexpr void stop() const noexcept {
            m_instance.CTRL = m_instance.CTRL.ENABLE.shift(false);
        }

        /// enables TWI read and write interrupts at the given level
        constexpr SPI::INT_LVL enable_interrupt(const SPI::INT_LVL lvl) const noexcept {
            const auto r = m_instance.INTCTRL;
            m_instance.INTCTRL = m_instance.INTCTRL.INTLVL.shift(lvl);
            return { r };
        }

        [[nodiscard]] constexpr SPI::MasterStatus get_status() const noexcept {
            return {m_instance.STATUS};
        }

        constexpr void write(const uint8_t data) const noexcept {
            m_instance.DATA = data;
        }

        constexpr uint8_t read() const noexcept {
            return m_instance.DATA;
        }

        constexpr uint8_t transfer(const uint8_t data) const noexcept {
            m_instance.DATA = data;
            while(get_status().interrupt_flag()){}
            return m_instance.DATA;
        }

        [[nodiscard]] constexpr nonstd::expected<uint16_t, SPI::error>
        transfer(nonstd::span<uint8_t> buffer) const noexcept {
            for(uint8_t& d : buffer) {
                m_instance.DATA = d;
                while(get_status().interrupt_flag()){}
                d = m_instance.DATA;
            }
            return buffer.size();
        }

        [[nodiscard]] constexpr nonstd::expected<uint16_t, SPI::error>
        write(nonstd::span<const uint8_t> buffer) const noexcept {
            for(const uint8_t& d : buffer) {
                m_instance.DATA = d;
                while(get_status().interrupt_flag()){}
            }
            return buffer.size();
        }

        [[nodiscard]] constexpr nonstd::expected<uint16_t, SPI::error>
        write(std::initializer_list<const uint8_t> data) const noexcept {
            return write(nonstd::span<const uint8_t>(data.begin(), data.end()) );
        }

        [[nodiscard]] constexpr nonstd::expected<uint16_t, SPI::error>
        read(nonstd::span<uint8_t> buffer) const noexcept {
            for(uint8_t& d : buffer) {
                m_instance.DATA = 0;
                while(get_status().interrupt_flag()){}
                d = m_instance.DATA;
            }
            return buffer.size();
        }

    };

} // namespace drivers

#if __clang__
#pragma clang diagnostic pop
#endif
