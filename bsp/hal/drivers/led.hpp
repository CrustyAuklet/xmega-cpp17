#pragma once
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "readability-static-accessed-through-instance"
#endif

#include "device.hpp"
#include "gpio.hpp"
#include <cstdint>

namespace drivers {

    template <typename PIN_INSTANCE>
    class Led {
    protected:
        PIN_INSTANCE m_pin;    // pin instance for this LED
    public:
        constexpr Led(const PIN_INSTANCE pin) : m_pin(pin) { }

        constexpr void init() const noexcept {
            m_pin.set_output();
        }

        constexpr void toggle() const noexcept {
            m_pin.toggle();
        }

        constexpr void on() const noexcept {
            m_pin.set_high();
        }

        constexpr void off() const noexcept {
            m_pin.set_low();
        }

        constexpr void set(const bool enable) const noexcept {
            m_pin.set_value(enable);
        }
    };

    template <typename PIN_INSTANCE>
    class LedInverted : public Led<PIN_INSTANCE> {
    public:
        constexpr LedInverted(const PIN_INSTANCE pin) : Led<PIN_INSTANCE>(pin) { }

        constexpr void init() const noexcept {
            Led<PIN_INSTANCE>::m_pin.set_output();
            Led<PIN_INSTANCE>::m_pin.configure(GPIO::PinConfig::INVERT_PIN | GPIO::PinConfig::MODE_TOTEM);
        }

    };

}   // namesapce device

#if __clang__
#pragma clang diagnostic pop
#endif
