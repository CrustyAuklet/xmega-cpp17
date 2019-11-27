/**
 * XMEGAAU-PORT (id I6075)
 * I/O Port Configuration
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace PORT {

    // Port Interrupt 0 Level
    enum class INT0LVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Port Interrupt 1 Level
    enum class INT1LVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Output/Pull Configuration
    enum class OPCv : uint8_t {
        TOTEM = 0x00, // Totempole
        BUSKEEPER = 0x01, // Totempole w/ Bus keeper on Input and Output
        PULLDOWN = 0x02, // Totempole w/ Pull-down on Input
        PULLUP = 0x03, // Totempole w/ Pull-up on Input
        WIREDOR = 0x04, // Wired OR
        WIREDAND = 0x05, // Wired AND
        WIREDORPULL = 0x06, // Wired OR w/ Pull-down
        WIREDANDPULL = 0x07, // Wired AND w/ Pull-up
    };

    // Input/Sense Configuration
    enum class ISCv : uint8_t {
        BOTHEDGES = 0x00, // Sense Both Edges
        RISING = 0x01, // Sense Rising Edge
        FALLING = 0x02, // Sense Falling Edge
        LEVEL = 0x03, // Sense Level (Transparent For Events)
        INPUT_DISABLE = 0x07, // Disable Digital Input Buffer
    };

    // PORT ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        INT0 = 0, // External Interrupt 0
        INT1 = 1, // External Interrupt 1
    };
}   // namespace PORT

/**
 * PORT
 * I/O Ports
 * Size: 24 bytes
 */
template <addressType BASE_ADDRESS>
struct PORT_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;
    using tag_type = PORT_t<BASE_ADDRESS>;

    /// I/O Port Data Direction - 1 bytes
    static constexpr struct DIR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
    } DIR = {};

    /// I/O Port Data Direction Set - 1 bytes
    static constexpr struct DIRSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
    } DIRSET = {};

    /// I/O Port Data Direction Clear - 1 bytes
    static constexpr struct DIRCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
    } DIRCLR = {};

    /// I/O Port Data Direction Toggle - 1 bytes
    static constexpr struct DIRTGL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
    } DIRTGL = {};

    /// I/O Port Output - 1 bytes
    static constexpr struct OUT_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
    } OUT = {};

    /// I/O Port Output Set - 1 bytes
    static constexpr struct OUTSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
    } OUTSET = {};

    /// I/O Port Output Clear - 1 bytes
    static constexpr struct OUTCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
    } OUTCLR = {};

    /// I/O Port Output Toggle - 1 bytes
    static constexpr struct OUTTGL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
    } OUTTGL = {};

    /// I/O port Input - 1 bytes
    static constexpr struct IN_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
    } IN = {};

    /// Interrupt Control Register - 1 bytes
    static constexpr struct INTCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        static constexpr bitfield_t<INTCTRL_t, 0x0C, 2, INT1LVLv> INT1LVL = {};    //< Port Interrupt 1 Level
        static constexpr bitfield_t<INTCTRL_t, 0x03, 0, INT0LVLv> INT0LVL = {};    //< Port Interrupt 0 Level
    } INTCTRL = {};

    /// Port Interrupt 0 Mask - 1 bytes
    static constexpr struct INT0MASK_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
    } INT0MASK = {};

    /// Port Interrupt 1 Mask - 1 bytes
    static constexpr struct INT1MASK_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
    } INT1MASK = {};

    /// Interrupt Flag Register - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        static constexpr bitfield_t<INTFLAGS_t, 0x02, 1> INT1IF = {};    //< Port Interrupt 1 Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x01, 0> INT0IF = {};    //< Port Interrupt 0 Flag
    } INTFLAGS = {};

    /// I/O Port Pin Remap Register - 1 bytes
    static constexpr struct REMAP_t : reg_t<uint8_t, BASE_ADDRESS + 0x000E> {
        static constexpr bitfield_t<REMAP_t, 0x20, 5> SPI = {};    //< SPI
        static constexpr bitfield_t<REMAP_t, 0x10, 4> USART0 = {};    //< USART0
        static constexpr bitfield_t<REMAP_t, 0x08, 3> TC0D = {};    //< Timer/Counter 0 Output Compare D
        static constexpr bitfield_t<REMAP_t, 0x04, 2> TC0C = {};    //< Timer/Counter 0 Output Compare C
        static constexpr bitfield_t<REMAP_t, 0x02, 1> TC0B = {};    //< Timer/Counter 0 Output Compare B
        static constexpr bitfield_t<REMAP_t, 0x01, 0> TC0A = {};    //< Timer/Counter 0 Output Compare A
    } REMAP = {};

    /// Pin 0 Control Register - 1 bytes
    static constexpr struct PIN0CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0010> {
        static constexpr bitfield_t<PIN0CTRL_t, 0x80, 7> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN0CTRL_t, 0x40, 6> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN0CTRL_t, 0x38, 3, OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN0CTRL_t, 0x07, 0, ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN0CTRL = {};

    /// Pin 1 Control Register - 1 bytes
    static constexpr struct PIN1CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0011> {
        static constexpr bitfield_t<PIN1CTRL_t, 0x80, 7> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN1CTRL_t, 0x40, 6> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN1CTRL_t, 0x38, 3, OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN1CTRL_t, 0x07, 0, ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN1CTRL = {};

    /// Pin 2 Control Register - 1 bytes
    static constexpr struct PIN2CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0012> {
        static constexpr bitfield_t<PIN2CTRL_t, 0x80, 7> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN2CTRL_t, 0x40, 6> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN2CTRL_t, 0x38, 3, OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN2CTRL_t, 0x07, 0, ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN2CTRL = {};

    /// Pin 3 Control Register - 1 bytes
    static constexpr struct PIN3CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0013> {
        static constexpr bitfield_t<PIN3CTRL_t, 0x80, 7> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN3CTRL_t, 0x40, 6> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN3CTRL_t, 0x38, 3, OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN3CTRL_t, 0x07, 0, ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN3CTRL = {};

    /// Pin 4 Control Register - 1 bytes
    static constexpr struct PIN4CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0014> {
        static constexpr bitfield_t<PIN4CTRL_t, 0x80, 7> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN4CTRL_t, 0x40, 6> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN4CTRL_t, 0x38, 3, OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN4CTRL_t, 0x07, 0, ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN4CTRL = {};

    /// Pin 5 Control Register - 1 bytes
    static constexpr struct PIN5CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0015> {
        static constexpr bitfield_t<PIN5CTRL_t, 0x80, 7> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN5CTRL_t, 0x40, 6> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN5CTRL_t, 0x38, 3, OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN5CTRL_t, 0x07, 0, ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN5CTRL = {};

    /// Pin 6 Control Register - 1 bytes
    static constexpr struct PIN6CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0016> {
        static constexpr bitfield_t<PIN6CTRL_t, 0x80, 7> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN6CTRL_t, 0x40, 6> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN6CTRL_t, 0x38, 3, OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN6CTRL_t, 0x07, 0, ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN6CTRL = {};

    /// Pin 7 Control Register - 1 bytes
    static constexpr struct PIN7CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0017> {
        static constexpr bitfield_t<PIN7CTRL_t, 0x80, 7> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN7CTRL_t, 0x40, 6> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN7CTRL_t, 0x38, 3, OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN7CTRL_t, 0x07, 0, ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN7CTRL = {};

};

} // namespace device
