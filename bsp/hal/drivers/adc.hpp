#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

#include "peripherals/ADC.hpp"
#include "gpio.hpp"
#include "device.hpp"
#include <cstdint>

#include "device.hpp"	// NOTE: This is only to assist in auto-complete. Comment out for compile.

namespace drivers {

    namespace ADC {
        enum CHANNELS { CH0 = 1, CH1 = 2, CH2 = 4, CH3 = 8 };

        using RESOLUTION = sfr::ADC::RESOLUTIONv;
        using CURRENT_LIMIT = sfr::ADC::CURRLIMITv;
        using REFERENCE = sfr::ADC::REFSELv;
        using PRESCALER = sfr::ADC::PRESCALERv;

        using INPUT_MODE = sfr::ADC::CH_INPUTMODEv;
        using GAIN = sfr::ADC::CH_GAINv;
        using INPUT_MODE = sfr::ADC::CH_INPUTMODEv;
        using INPUT_POS = sfr::ADC::CH_MUXPOSv;
        using INPUT_INTERNAL = sfr::ADC::CH_MUXINTv;
        using INPUT_NEG = sfr::ADC::CH_MUXNEGv;
        using INTERRUPT_MODE = sfr::ADC::CH_INTMODEv;
        using INTERRUPT_LVL = sfr::ADC::CH_INTLVLv;

    } // namespace ADC

    template <typename ADC_INSTANCE>
    class ADC_SingleEnded_Basic {
        ADC_INSTANCE m_instance;
//        decltype(device::ADCA) m_instance;  // NOTE: This is only to assist in auto-complete. Comment out for compile.
    public:
        constexpr ADC_SingleEnded_Basic(const ADC_INSTANCE instance)
            : m_instance(instance)
        {}

        /**
         * \brief Initialize ADC interface
         * If module is configured to disabled state, the clock to the ADC is disabled
         * if this is supported by the device's clock system.
         * \return Initialization status.
         */
        constexpr void init(const ADC::RESOLUTION resolution,
                            const ADC::PRESCALER prescale = ADC::PRESCALER::DIV4,
                            const bool high_impedance = false,
                            const ADC::CURRENT_LIMIT current_limit = ADC::CURRENT_LIMIT::NO,
                            const bool signed_mode = false) const noexcept
        {
            m_instance.CTRLB = m_instance.CTRLB.IMPMODE.shift(high_impedance)
                             | m_instance.CTRLB.CURRLIMIT.shift(current_limit)
                             | m_instance.CTRLB.CONMODE.shift(signed_mode)
                             | m_instance.CTRLB.RESOLUTION.shift(resolution);

            m_instance.PRESCALER.PRESCALER = prescale;
        }

        // TODO: implement this, do we need it?
//        constexpr void write_calibration(const uint16_t cal) const noexcept {
//            const uint8_t L = cal & 0xFFU;
//            const uint8_t H = (cal>>8U) & 0x0FU;
//            m_instance.CAL =
//        }

        /**
         * Enable the ADC channel. Sets the enable bit and flushes old readings.
         * If supported this will enable the clock to the ADC.
         */
        constexpr void start() const noexcept {
            m_instance.CTRLA |= (m_instance.CTRLA.ENABLE.shift(1) | m_instance.CTRLA.FLUSH.shift(1));
        }

        /**
         * Disable the ADC channel. Clears the enable bit, and if supported disables clock input.
         */
        constexpr void stop() const noexcept {
            m_instance.CTRLA.ENABLE = false;
        }

        constexpr void set_reference(const ADC::REFERENCE ref) const noexcept {
            m_instance.REFCTRL.REFSEL = ref;
        }

        constexpr void set_compare_value(const uint16_t cmp) const noexcept {
            // TODO: probably need to use RAMPZ in the register.h file
            m_instance.CMP = cmp;
        }

        template<unsigned CH = 0>
        constexpr void setup_channel(const ADC::INPUT_MODE mode = ADC::INPUT_MODE::SINGLEENDED, const ADC::GAIN gain = ADC::GAIN::_1X) const noexcept {
            static_assert(CH < 4, "ADC only has channels 0-3!");
            if constexpr (CH == 0) {
                m_instance.CH0.CTRL = (m_instance.CH0.CTRL.GAIN.shift(gain) | m_instance.CH0.CTRL.INPUTMODE.shift(mode));
            }
            if constexpr (CH == 1) {
                m_instance.CH1.CTRL = (m_instance.CH1.CTRL.GAIN.shift(gain) | m_instance.CH1.CTRL.INPUTMODE.shift(mode));
            }
            if constexpr (CH == 2) {
                m_instance.CH2.CTRL = (m_instance.CH2.CTRL.GAIN.shift(gain) | m_instance.CH2.CTRL.INPUTMODE.shift(mode));
            }
            if constexpr (CH == 3) {
                m_instance.CH3.CTRL = (m_instance.CH3.CTRL.GAIN.shift(gain) | m_instance.CH3.CTRL.INPUTMODE.shift(mode));
            }
        }

        template<unsigned CH = 0>
        constexpr void setup_channel_interrupts(const ADC::INTERRUPT_MODE mode = ADC::INTERRUPT_MODE::COMPLETE, const ADC::INTERRUPT_LVL lvl = ADC::INTERRUPT_LVL::OFF) const noexcept {
            static_assert(CH < 4, "ADC only has channels 0-3!");
            if constexpr (CH == 0) {
                m_instance.CH0.INTCTRL = (m_instance.CH0.INTCTRL.INTMODE.shift(mode) | m_instance.CH0.INTCTRL.INTLVL.shift(lvl));
            }
            if constexpr (CH == 1) {
                m_instance.CH1.INTCTRL = (m_instance.CH1.INTCTRL.INTMODE.shift(mode) | m_instance.CH1.INTCTRL.INTLVL.shift(lvl));
            }
            if constexpr (CH == 2) {
                m_instance.CH2.INTCTRL = (m_instance.CH2.INTCTRL.INTMODE.shift(mode) | m_instance.CH2.INTCTRL.INTLVL.shift(lvl));
            }
            if constexpr (CH == 3) {
                m_instance.CH3.INTCTRL = (m_instance.CH3.INTCTRL.INTMODE.shift(mode) | m_instance.CH3.INTCTRL.INTLVL.shift(lvl));
            }
        }

        template<unsigned CH = 0>
        constexpr void setup_channel_inputs(const ADC::INPUT_POS positive, const ADC::INPUT_NEG negative = ADC::INPUT_NEG::PIN0) const noexcept {
            static_assert(CH < 4, "ADC only has channels 0-3!");
            if constexpr (CH == 0) {
                m_instance.CH0.MUXCTRL = (m_instance.CH0.MUXCTRL.MUXPOS.shift(positive) | m_instance.CH0.MUXCTRL.MUXNEG.shift(negative));
            }
            if constexpr (CH == 1) {
                m_instance.CH1.MUXCTRL = (m_instance.CH1.MUXCTRL.MUXPOS.shift(positive) | m_instance.CH1.MUXCTRL.MUXNEG.shift(negative));
            }
            if constexpr (CH == 2) {
                m_instance.CH2.MUXCTRL = (m_instance.CH2.MUXCTRL.MUXPOS.shift(positive) | m_instance.CH2.MUXCTRL.MUXNEG.shift(negative));
            }
            if constexpr (CH == 3) {
                m_instance.CH3.MUXCTRL = (m_instance.CH3.MUXCTRL.MUXPOS.shift(positive) | m_instance.CH3.MUXCTRL.MUXNEG.shift(negative));
            }
        }

        template<unsigned CH = 0>
        constexpr void setup_channel_inputs(const ADC::INPUT_INTERNAL internal, const ADC::INPUT_NEG negative = ADC::INPUT_NEG::PIN0) const noexcept {
            if(internal == ADC::INPUT_INTERNAL::TEMP) { }
            else if (internal == ADC::INPUT_INTERNAL::BANDGAP) { }
            setup_channel_inputs<CH>(static_cast<ADC::INPUT_POS>(internal), negative);
        }

        /**
         * @brief Start a conversion on the ADC channel
         * @param [in] channel The ADC channel to start conversion on
         */
        template<unsigned CH = 0>
        constexpr void start_conversion(const uint8_t channel) const noexcept {
            static_assert(CH < 4, "ADC only has channels 0-3!");
            if constexpr (CH == 0) {
                m_instance.CH0.MUXCTRL.MUXPOS = static_cast<ADC::INPUT_POS>(channel & 0x0FU);
                m_instance.CH0.CTRL.INPUTMODE = ADC::INPUT_MODE::SINGLEENDED;
                m_instance.CH0.CTRL.START = true;
            }
            if constexpr (CH == 1) {
                m_instance.CH1.MUXCTRL.MUXPOS = static_cast<ADC::INPUT_POS>(channel & 0x0FU);
                m_instance.CH1.CTRL.INPUTMODE = ADC::INPUT_MODE::SINGLEENDED;
                m_instance.CH1.CTRL.START = true;
            }
            if constexpr (CH == 2) {
                m_instance.CH2.MUXCTRL.MUXPOS = static_cast<ADC::INPUT_POS>(channel & 0x0FU);
                m_instance.CH2.CTRL.INPUTMODE = ADC::INPUT_MODE::SINGLEENDED;
                m_instance.CH2.CTRL.START = true;
            }
            if constexpr (CH == 3) {
                m_instance.CH3.MUXCTRL.MUXPOS = static_cast<ADC::INPUT_POS>(channel & 0x0FU);
                m_instance.CH3.CTRL.INPUTMODE = ADC::INPUT_MODE::SINGLEENDED;
                m_instance.CH3.CTRL.START = true;
            }
        }

        /**
         * Check if the ADC conversion is done
         * @return TRUE if the conversion is done, FALSE if it is not done
         */
        template<unsigned CH = 0>
        constexpr bool is_conversion_done() const noexcept {
            static_assert(CH < 4, "ADC only has channels 0-3!");
            if constexpr (CH == 0) { return m_instance.INTFLAGS.CH0IF; }
            if constexpr (CH == 1) { return m_instance.INTFLAGS.CH1IF; }
            if constexpr (CH == 2) { return m_instance.INTFLAGS.CH2IF; }
            if constexpr (CH == 3) { return m_instance.INTFLAGS.CH3IF; }
        }

        /**
         * Check if the ADC conversion is done
         * @return TRUE if the conversion is done, FALSE if it is not done
         */
        template<unsigned CH = 0>
        constexpr void clear_interrupt_flag() const noexcept {
            static_assert(CH < 4, "ADC only has channels 0-3!");
            if constexpr (CH == 0) { m_instance.INTFLAGS.CH0IF = true; }
            if constexpr (CH == 1) { m_instance.INTFLAGS.CH1IF = true; }
            if constexpr (CH == 2) { m_instance.INTFLAGS.CH2IF = true; }
            if constexpr (CH == 3) { m_instance.INTFLAGS.CH3IF = true; }
        }

        /**
         * Get the conversion result from the given channel
         * @return Conversion result as an unsigned 16-bit integer
         */
        template<unsigned CH = 0>
        constexpr uint16_t get_conversion_result() const noexcept {
            static_assert(CH < 4, "ADC only has channels 0-3!");
            if constexpr (CH == 0) { return m_instance.CH0RES; }
            if constexpr (CH == 1) { return m_instance.CH1RES; }
            if constexpr (CH == 2) { return m_instance.CH2RES; }
            if constexpr (CH == 3) { return m_instance.CH3RES; }
        }

        /// Obtain the number of bits in a channels conversion results
        constexpr ADC::RESOLUTION get_resolution() const noexcept {
            return { m_instance.CTRLB.RESOLUTION };
        }
        /// Set the number of bits in a channels conversion results
        constexpr void set_resolution(const ADC::RESOLUTION res) const noexcept {
            m_instance.CTRLB.RESOLUTION = res;
        }

        /**
         * Start a conversion, wait until ready, and return the conversion result
         * @return Conversion result as an unsigned 16-bit integer, left aligned.
         */
        template<unsigned CH = 0>
        constexpr uint16_t read(const uint8_t channel) const noexcept {
            start_conversion<CH>(channel);
            while(!is_conversion_done<CH>()) {}
            const auto result = get_conversion_result<CH>();
            clear_interrupt_flag<CH>();
            return static_cast<uint16_t>(result);
        }

    };

} // namespace drivers
#pragma clang diagnostic pop
