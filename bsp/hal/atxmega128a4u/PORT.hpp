/**
 * XMEGAAU-PORT (id I6075)
 * I/O Port Configuration
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

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
}   // namespace PORT

/**
 * PORT
 * I/O Ports
 * Size: 24 bytes
 */
template <addressType BASE_ADDRESS>
struct PORT_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// I/O Port Data Direction - 1 bytes
    static constexpr struct DIR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
    } DIR = {};

    /// I/O Port Data Direction Set - 1 bytes
    static constexpr struct DIRSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
    } DIRSET = {};

    /// I/O Port Data Direction Clear - 1 bytes
    static constexpr struct DIRCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
    } DIRCLR = {};

    /// I/O Port Data Direction Toggle - 1 bytes
    static constexpr struct DIRTGL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
    } DIRTGL = {};

    /// I/O Port Output - 1 bytes
    static constexpr struct OUT_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
    } OUT = {};

    /// I/O Port Output Set - 1 bytes
    static constexpr struct OUTSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
    } OUTSET = {};

    /// I/O Port Output Clear - 1 bytes
    static constexpr struct OUTCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
    } OUTCLR = {};

    /// I/O Port Output Toggle - 1 bytes
    static constexpr struct OUTTGL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0007>::operator=;
    } OUTTGL = {};

    /// I/O port Input - 1 bytes
    static constexpr struct IN_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0008>::operator=;
    } IN = {};

    /// Interrupt Control Register - 1 bytes
    static constexpr struct INTCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0009>::operator=;
        static constexpr bitfield_t<INTCTRL_t, 3, 2, PORT::INT1LVLv> INT1LVL = {};    //< Port Interrupt 1 Level
        static constexpr bitfield_t<INTCTRL_t, 1, 0, PORT::INT0LVLv> INT0LVL = {};    //< Port Interrupt 0 Level
    } INTCTRL = {};

    /// Port Interrupt 0 Mask - 1 bytes
    static constexpr struct INT0MASK_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000A>::operator=;
    } INT0MASK = {};

    /// Port Interrupt 1 Mask - 1 bytes
    static constexpr struct INT1MASK_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000B>::operator=;
    } INT1MASK = {};

    /// Interrupt Flag Register - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000C>::operator=;
        static constexpr bitfield_t<INTFLAGS_t, 1, 1, bool> INT1IF = {};    //< Port Interrupt 1 Flag
        static constexpr bitfield_t<INTFLAGS_t, 0, 0, bool> INT0IF = {};    //< Port Interrupt 0 Flag
    } INTFLAGS = {};

    /// I/O Port Pin Remap Register - 1 bytes
    static constexpr struct REMAP_t : reg_t<uint8_t, BASE_ADDRESS + 0x000E> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000E>::operator=;
        static constexpr bitfield_t<REMAP_t, 5, 5, bool> SPI = {};    //< SPI
        static constexpr bitfield_t<REMAP_t, 4, 4, bool> USART0 = {};    //< USART0
        static constexpr bitfield_t<REMAP_t, 3, 3, bool> TC0D = {};    //< Timer/Counter 0 Output Compare D
        static constexpr bitfield_t<REMAP_t, 2, 2, bool> TC0C = {};    //< Timer/Counter 0 Output Compare C
        static constexpr bitfield_t<REMAP_t, 1, 1, bool> TC0B = {};    //< Timer/Counter 0 Output Compare B
        static constexpr bitfield_t<REMAP_t, 0, 0, bool> TC0A = {};    //< Timer/Counter 0 Output Compare A
    } REMAP = {};

    /// Pin 0 Control Register - 1 bytes
    static constexpr struct PIN0CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0010> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0010>::operator=;
        static constexpr bitfield_t<PIN0CTRL_t, 7, 7, bool> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN0CTRL_t, 6, 6, bool> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN0CTRL_t, 5, 3, PORT::OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN0CTRL_t, 2, 0, PORT::ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN0CTRL = {};

    /// Pin 1 Control Register - 1 bytes
    static constexpr struct PIN1CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0011> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0011>::operator=;
        static constexpr bitfield_t<PIN1CTRL_t, 7, 7, bool> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN1CTRL_t, 6, 6, bool> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN1CTRL_t, 5, 3, PORT::OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN1CTRL_t, 2, 0, PORT::ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN1CTRL = {};

    /// Pin 2 Control Register - 1 bytes
    static constexpr struct PIN2CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0012> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0012>::operator=;
        static constexpr bitfield_t<PIN2CTRL_t, 7, 7, bool> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN2CTRL_t, 6, 6, bool> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN2CTRL_t, 5, 3, PORT::OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN2CTRL_t, 2, 0, PORT::ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN2CTRL = {};

    /// Pin 3 Control Register - 1 bytes
    static constexpr struct PIN3CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0013> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0013>::operator=;
        static constexpr bitfield_t<PIN3CTRL_t, 7, 7, bool> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN3CTRL_t, 6, 6, bool> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN3CTRL_t, 5, 3, PORT::OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN3CTRL_t, 2, 0, PORT::ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN3CTRL = {};

    /// Pin 4 Control Register - 1 bytes
    static constexpr struct PIN4CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0014> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0014>::operator=;
        static constexpr bitfield_t<PIN4CTRL_t, 7, 7, bool> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN4CTRL_t, 6, 6, bool> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN4CTRL_t, 5, 3, PORT::OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN4CTRL_t, 2, 0, PORT::ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN4CTRL = {};

    /// Pin 5 Control Register - 1 bytes
    static constexpr struct PIN5CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0015> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0015>::operator=;
        static constexpr bitfield_t<PIN5CTRL_t, 7, 7, bool> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN5CTRL_t, 6, 6, bool> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN5CTRL_t, 5, 3, PORT::OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN5CTRL_t, 2, 0, PORT::ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN5CTRL = {};

    /// Pin 6 Control Register - 1 bytes
    static constexpr struct PIN6CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0016> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0016>::operator=;
        static constexpr bitfield_t<PIN6CTRL_t, 7, 7, bool> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN6CTRL_t, 6, 6, bool> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN6CTRL_t, 5, 3, PORT::OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN6CTRL_t, 2, 0, PORT::ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN6CTRL = {};

    /// Pin 7 Control Register - 1 bytes
    static constexpr struct PIN7CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0017> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0017>::operator=;
        static constexpr bitfield_t<PIN7CTRL_t, 7, 7, bool> SRLEN = {};    //< Slew Rate Enable
        static constexpr bitfield_t<PIN7CTRL_t, 6, 6, bool> INVEN = {};    //< Inverted I/O Enable
        static constexpr bitfield_t<PIN7CTRL_t, 5, 3, PORT::OPCv> OPC = {};    //< Output/Pull Configuration
        static constexpr bitfield_t<PIN7CTRL_t, 2, 0, PORT::ISCv> ISC = {};    //< Input/Sense Configuration
    } PIN7CTRL = {};

    // PORT ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        INT0 = 0, // External Interrupt 0
        INT1 = 1, // External Interrupt 1
    };
};

} // namespace sfr
