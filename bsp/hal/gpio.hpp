#ifndef SEAL_HAL_GPIO_TEMPLATE
#define SEAL_HAL_GPIO_TEMPLATE

#include <cstdint>

template <class PORT, uint8_t PIN>
class gpio_pin {
    static_assert(PIN < 8, "PIN value in gpio_pin must be a number 0-7");
    static constexpr uint8_t PIN_MASK = 1 << PIN;   // Pin mask for use in all the functions
public:
    /// Set the pin as an output
    static void set_output() { PORT::DIRSET::write(PIN_MASK); }
    /// Set the pin as in input
    static void set_input() { PORT::DIRCLR::write(PIN_MASK); }
    /// Set the output level of the pin to low. Pin must be set as Output.
    static void set_low() { PORT::OUTSET::write(PIN_MASK); }
    /// Set the output level of the pin to high. Pin must be set as Output.
    static void set_high() { PORT::OUTCLR::write(PIN_MASK); }
    /// Toggle the output level of the pin. Pin must be set as Output.
    static void toggle() { PORT::OUTTGL::write(PIN_MASK); }
    /// set the level of the pin using a boolean argument
    static void set_value(const bool level) {
        if(level){ set_high(); }
        else { set_low(); }
    }
    /// get the current state of the pin. Digital input buffer must be enabled.
    static bool get_value() { return PORT::IN::read() & PIN_MASK; }

    enum PinConfig {
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

    // configure the GPIO pin with some OR value of flags in device::io::PinConfig
    static void configure(const PinConfig config) {
        using THIS_PINCTRL = reg8_t<PORT::PIN0CTRL::ADDRESS + PIN>;    // local typedef for offset of PINCTRL
        THIS_PINCTRL::write(config);
    }

    template <uint8_t INT_NUM>
    static void enable_interrupt() {
        static_assert(INT_NUM <= 1, "GPIO interrupt must be 0 or 1");
        using THIS_INTMASK = reg8_t<PORT::INTMASK_BASE_ADDRESS + INT_NUM>;    // local typedef for offset of interrupt
        THIS_INTMASK::write( THIS_INTMASK::read() | PIN_MASK );
    }

    template <uint8_t INT_NUM>
    static void disable_interrupt() {
        static_assert(INT_NUM <= 1, "GPIO interrupt must be 0 or 1");
        using THIS_INTMASK = reg8_t<PORT::INTMASK_BASE_ADDRESS + INT_NUM>;    // local typedef for offset of interrupt
        THIS_INTMASK::write( THIS_INTMASK::read() & ~PIN_MASK );
    }

    static void set_lowpower() {
        configure(MODE_PULLUP);
    }

};

template < typename GPIO_PIN >
class UnusedPin : public GPIO_PIN {
    UnusedPin() {
        GPIO_PIN::set_lowpower();
    }
};

#endif // SEAL_HAL_GPIO_TEMPLATE
