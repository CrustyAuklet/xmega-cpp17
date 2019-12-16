#pragma once

#include <cstdint>

namespace GPIO {
    enum class PinConfig : uint8_t {
        SENSE_BOTHEDGES     = 0x00U << 0U, //< IOPORT sense both rising and falling edges
        SENSE_RISING        = 0x01U << 0U, //< IOPORT sense rising edges
        SENSE_FALLING       = 0x02U << 0U, //< IOPORT sense falling edges
        SENSE_LEVEL_LOW     = 0x03U << 0U, //< IOPORT sense low level
        SENSE_INPUT_DISABLE = 0x07U << 0U, //< Digital Input Buffer Disable (ex: for ADC)
        MODE_TOTEM          = 0x00U << 3U, ///< push-pull on output, floating on input
        MODE_BUSKEEPER      = 0x01U << 3U, ///< push-pull on output, keeps last input
        MODE_PULLDOWN       = 0x02U << 3U, ///< push-pull on output, pull-down on input
        MODE_PULLUP         = 0x03U << 3U, ///< push-pull on output, pull-up on input
        MODE_WIREDOR        = 0x04U << 3U, ///< pin is driven high on output, externally pulled down or floating on input
        MODE_WIREDAND       = 0x05U << 3U, ///< pin is driven low on output, externally pulled down or floating on input
        MODE_WIREDORPULL    = 0x06U << 3U, ///< pin is driven high on output, internally pulled down on input
        MODE_WIREDANDPULL   = 0x07U << 3U, ///< pin is driven low on output, internally pulled high on input
        INVERT_PIN          = 0x01U << 6U, //< Invert output and input
        SLEW_RATE_LIMIT     = 0x01U << 7U  //< Slew rate limiting
    };

    constexpr PinConfig operator|(PinConfig a, PinConfig b) { return PinConfig(int(a) | int(b)); }
    constexpr PinConfig operator&(PinConfig a, PinConfig b) { return PinConfig(int(a) & int(b)); }

    template <class PORT, uint8_t PIN>
    class pin {
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

        constexpr void init() const noexcept {}
    };

    template <typename PIN_INSTANCE>
    struct no_init {
        PIN_INSTANCE m_pin;
        explicit constexpr no_init(const PIN_INSTANCE pin) : m_pin(pin) { }
        constexpr void init() const noexcept { }
    };

    template <typename PIN_INSTANCE>
    struct Unused {
        PIN_INSTANCE m_pin;
        explicit constexpr Unused(const PIN_INSTANCE pin) : m_pin(pin) { }
        constexpr void init() const noexcept {
            m_pin.set_lowpower();
        }
    };

    template <typename PIN_INSTANCE>
    struct output_low {
        PIN_INSTANCE m_pin;
        explicit constexpr output_low(const PIN_INSTANCE pin) : m_pin(pin) { }
        constexpr void init() const noexcept {
            m_pin.set_output();
            m_pin.configure(GPIO::PinConfig::MODE_TOTEM);
            m_pin.set_low();
        }
    };

    template <typename PIN_INSTANCE>
    struct output_high {
        PIN_INSTANCE m_pin;
        explicit constexpr output_high(const PIN_INSTANCE pin) : m_pin(pin) { }
        constexpr void init() const noexcept {
            m_pin.set_output();
            m_pin.configure(GPIO::PinConfig::MODE_TOTEM);
            m_pin.set_high();
        }
    };

    template <typename PIN_INSTANCE>
    struct input_floating {
        PIN_INSTANCE m_pin;
        explicit constexpr input_floating(const PIN_INSTANCE pin) : m_pin(pin) { }
        constexpr void init() const noexcept {
            m_pin.set_input();
            m_pin.configure(GPIO::PinConfig::MODE_TOTEM);
        }
    };

    template <typename PIN_INSTANCE>
    struct input_buskeeper {
        PIN_INSTANCE m_pin;
        explicit constexpr input_buskeeper(const PIN_INSTANCE pin) : m_pin(pin) { }
        constexpr void init() const noexcept {
            m_pin.set_input();
            m_pin.configure(GPIO::PinConfig::MODE_BUSKEEPER);
        }
    };

    template <typename PIN_INSTANCE>
    struct input_pullup {
        PIN_INSTANCE m_pin;
        explicit constexpr input_pullup(const PIN_INSTANCE pin) : m_pin(pin) { }
        constexpr void init() const noexcept {
            m_pin.set_input();
            m_pin.configure(GPIO::PinConfig::MODE_PULLUP);
        }
    };

    template <typename PIN_INSTANCE>
    struct input_pulldown {
        PIN_INSTANCE m_pin;
        explicit constexpr input_pulldown(const PIN_INSTANCE pin) : m_pin(pin) { }
        constexpr void init() const noexcept {
            m_pin.set_input();
            m_pin.configure(GPIO::PinConfig::MODE_PULLDOWN);
        }
    };

    template <typename PIN_INSTANCE>
    struct SDA : public output_low<PIN_INSTANCE> {
        explicit constexpr SDA(const PIN_INSTANCE pin) : output_low<PIN_INSTANCE>(pin) { }
    };

    template <typename PIN_INSTANCE>
    struct SCL : public output_low<PIN_INSTANCE> {
        explicit constexpr SCL(const PIN_INSTANCE pin) : output_low<PIN_INSTANCE>(pin) { }
    };

    template <typename PIN_INSTANCE>
    struct MOSI : public output_low<PIN_INSTANCE> {
        explicit constexpr MOSI(const PIN_INSTANCE pin) : output_low<PIN_INSTANCE>(pin) { }
    };

    template <typename PIN_INSTANCE>
    struct MISO : public input_floating<PIN_INSTANCE> {
        explicit constexpr MISO(const PIN_INSTANCE pin) : input_floating<PIN_INSTANCE>(pin) { }
    };

    template <typename PIN_INSTANCE>
    struct SCK : public output_low<PIN_INSTANCE> {
        explicit constexpr SCK(const PIN_INSTANCE pin) : output_low<PIN_INSTANCE>(pin) { }
    };

    template <typename PIN_INSTANCE>
    struct USART_RX : public input_floating<PIN_INSTANCE> {
        explicit constexpr USART_RX(const PIN_INSTANCE pin) : input_floating<PIN_INSTANCE>(pin) { }
    };

    template <typename PIN_INSTANCE>
    struct USART_TX : public output_low<PIN_INSTANCE> {
        explicit constexpr USART_TX(const PIN_INSTANCE pin) : output_low<PIN_INSTANCE>(pin) { }
    };

    template <typename PIN_INSTANCE>
    class Led : public output_low<PIN_INSTANCE> {
    public:
        using base = output_low<PIN_INSTANCE>;
        explicit constexpr Led(const PIN_INSTANCE pin) : output_low<PIN_INSTANCE>(pin) { }

        constexpr void toggle() const noexcept {
            base::m_pin.toggle();
        }

        constexpr void on() const noexcept {
            base::m_pin.set_high();
        }

        constexpr void off() const noexcept {
            base::m_pin.set_low();
        }

        constexpr void set(const bool enable) const noexcept {
            base::m_pin.set_value(enable);
        }
    };

    template <typename PIN_INSTANCE>
    class LedInverted : public Led<PIN_INSTANCE> {
    public:
        explicit constexpr LedInverted(const PIN_INSTANCE pin) : Led<PIN_INSTANCE>(pin) { }
        constexpr void init() const noexcept {
            Led<PIN_INSTANCE>::m_pin.set_output();
            Led<PIN_INSTANCE>::m_pin.configure(GPIO::PinConfig::INVERT_PIN | GPIO::PinConfig::MODE_TOTEM);
        }
    };

} // namespace GPIO