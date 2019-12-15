#pragma once

#include <cstdint>

namespace GPIO {
    enum class PinConfig : uint8_t {
        SENSE_BOTHEDGES     = 0x00 << 0, //< IOPORT sense both rising and falling edges
        SENSE_RISING        = 0x01 << 0, //< IOPORT sense rising edges
        SENSE_FALLING       = 0x02 << 0, //< IOPORT sense falling edges
        SENSE_LEVEL_LOW     = 0x03 << 0, //< IOPORT sense low level
        SENSE_INPUT_DISABLE = 0x07 << 0, //< Digital Input Buffer Disable (ex: for ADC)
        MODE_TOTEM          = 0x00 << 3, ///< push-pull on output, floating on input
        MODE_BUSKEEPER      = 0x01 << 3, ///< push-pull on output, keeps last input
        MODE_PULLDOWN       = 0x02 << 3, ///< push-pull on output, pull-down on input
        MODE_PULLUP         = 0x03 << 3, ///< push-pull on output, pull-up on input
        MODE_WIREDOR        = 0x04 << 3, ///< pin is driven high on output, externally pulled down or floating on input
        MODE_WIREDAND       = 0x05 << 3, ///< pin is driven low on output, externally pulled down or floating on input
        MODE_WIREDORPULL    = 0x06 << 3, ///< pin is driven high on output, internally pulled down on input
        MODE_WIREDANDPULL   = 0x07 << 3, ///< pin is driven low on output, internally pulled high on input
        INVERT_PIN          = 0x01 << 6, //< Invert output and input
        SLEW_RATE_LIMIT     = 0x01 << 7  //< Slew rate limiting
    };

    constexpr PinConfig operator|(PinConfig a, PinConfig b) { return PinConfig(int(a) | int(b)); }
    constexpr PinConfig operator&(PinConfig a, PinConfig b) { return PinConfig(int(a) & int(b)); }
} // namespace GPIO

template <class PORT, uint8_t PIN>
class gpio_pin {
    static_assert(PIN < 8, "PIN value in gpio_pin must be a number 0-7");
    static constexpr uint8_t PIN_MASK = 1 << PIN;   // Pin mask for use in all the functions
    static constexpr PORT Port = {};
public:
    /// Set the pin as an output
    constexpr void set_output() const noexcept { Port.DIRSET = PIN_MASK; }
    /// Set the pin as in input
    constexpr void set_input() const noexcept { Port.DIRCLR = PIN_MASK; }
    /// Set the output level of the pin to low. Pin must be set as Output.
    constexpr void set_low() const noexcept { Port.OUTCLR = PIN_MASK; }
    /// Set the output level of the pin to high. Pin must be set as Output.
    constexpr void set_high() const noexcept { Port.OUTSET = PIN_MASK; }
    /// Toggle the output level of the pin. Pin must be set as Output.
    constexpr void toggle() const noexcept { Port.OUTTGL = PIN_MASK; }
    /// set the level of the pin using a boolean argument
    constexpr void set_value(const bool level) const noexcept {
        if(level){ set_high(); }
        else { set_low(); }
    }
    /// get the current state of the pin. Digital input buffer must be enabled.
    constexpr volatile bool get_value() const noexcept { return Port.IN & PIN_MASK; }

    constexpr operator volatile bool&() noexcept { return get_value(); }
    constexpr operator const volatile bool&() const noexcept { return get_value(); }

    // configure the GPIO pin with some OR value of flags in device::io::PinConfig
    constexpr void configure(const GPIO::PinConfig config) const noexcept {
        if constexpr(PIN == 0)      { Port.PIN0CTRL = static_cast<uint8_t>(config); }
        else if constexpr(PIN == 1) { Port.PIN1CTRL = static_cast<uint8_t>(config); }
        else if constexpr(PIN == 2) { Port.PIN2CTRL = static_cast<uint8_t>(config); }
        else if constexpr(PIN == 3) { Port.PIN3CTRL = static_cast<uint8_t>(config); }
        else if constexpr(PIN == 4) { Port.PIN4CTRL = static_cast<uint8_t>(config); }
        else if constexpr(PIN == 5) { Port.PIN5CTRL = static_cast<uint8_t>(config); }
        else if constexpr(PIN == 6) { Port.PIN6CTRL = static_cast<uint8_t>(config); }
        else if constexpr(PIN == 7) { Port.PIN7CTRL = static_cast<uint8_t>(config); }
    }

    template <uint8_t INT_NUM>
    constexpr void enable_interrupt() const noexcept {
        static_assert(INT_NUM <= 1, "GPIO interrupt must be 0 or 1");
        if constexpr(INT_NUM) {
            Port.INT0MASK |= PIN_MASK;
        }
        else {
            Port.INT1MASK |= PIN_MASK;
        }
    }

    template <uint8_t INT_NUM>
    constexpr void disable_interrupt() const noexcept {
        static_assert(INT_NUM <= 1, "GPIO interrupt must be 0 or 1");
        if constexpr(INT_NUM) {
            Port.INT0MASK &= ~PIN_MASK;
        }
        else {
            Port.INT1MASK &= ~PIN_MASK;
        }
    }

    constexpr void set_lowpower() const noexcept {
        configure(GPIO::PinConfig::MODE_PULLUP);
    }

    constexpr void set_analog() const noexcept {
        configure(GPIO::PinConfig::MODE_TOTEM | GPIO::PinConfig::SENSE_INPUT_DISABLE);
    }

};

template < typename GPIO_PIN >
class UnusedPin : public GPIO_PIN {
    UnusedPin() {
        GPIO_PIN::set_lowpower();
    }
};
