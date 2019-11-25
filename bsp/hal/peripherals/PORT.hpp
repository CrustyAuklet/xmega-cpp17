/**
 * XMEGAAU-PORT (id I6075)
 * I/O Port Configuration
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * PORT
 * I/O Ports
 * Size: 24 bytes
 */
template <addressType BASE_ADDRESS>
struct PORT_t {

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

    /// I/O Port Data Direction - 1 bytes
    struct DIR : public reg8_t<BASE_ADDRESS + 0x0000> {
    };

    /// I/O Port Data Direction Set - 1 bytes
    struct DIRSET : public reg8_t<BASE_ADDRESS + 0x0001> {
    };

    /// I/O Port Data Direction Clear - 1 bytes
    struct DIRCLR : public reg8_t<BASE_ADDRESS + 0x0002> {
    };

    /// I/O Port Data Direction Toggle - 1 bytes
    struct DIRTGL : public reg8_t<BASE_ADDRESS + 0x0003> {
    };

    /// I/O Port Output - 1 bytes
    struct OUT : public reg8_t<BASE_ADDRESS + 0x0004> {
    };

    /// I/O Port Output Set - 1 bytes
    struct OUTSET : public reg8_t<BASE_ADDRESS + 0x0005> {
    };

    /// I/O Port Output Clear - 1 bytes
    struct OUTCLR : public reg8_t<BASE_ADDRESS + 0x0006> {
    };

    /// I/O Port Output Toggle - 1 bytes
    struct OUTTGL : public reg8_t<BASE_ADDRESS + 0x0007> {
    };

    /// I/O port Input - 1 bytes
    struct IN : public reg8_t<BASE_ADDRESS + 0x0008> {
    };

    /// Interrupt Control Register - 1 bytes
    struct INTCTRL : public reg8_t<BASE_ADDRESS + 0x0009> {
        using INT1LVL = reg_field_t<BASE_ADDRESS + 0x0009, 0x0C, 2, INT1LVLv>;    //< Port Interrupt 1 Level
        using INT0LVL = reg_field_t<BASE_ADDRESS + 0x0009, 0x03, 0, INT0LVLv>;    //< Port Interrupt 0 Level
    };

    /// Port Interrupt 0 Mask - 1 bytes
    struct INT0MASK : public reg8_t<BASE_ADDRESS + 0x000A> {
    };

    /// Port Interrupt 1 Mask - 1 bytes
    struct INT1MASK : public reg8_t<BASE_ADDRESS + 0x000B> {
    };

    /// Interrupt Flag Register - 1 bytes
    struct INTFLAGS : public reg8_t<BASE_ADDRESS + 0x000C> {
        using INT1IF = reg_field_t<BASE_ADDRESS + 0x000C, 0x02, 1>;    //< Port Interrupt 1 Flag
        using INT0IF = reg_field_t<BASE_ADDRESS + 0x000C, 0x01, 0>;    //< Port Interrupt 0 Flag
    };

    /// I/O Port Pin Remap Register - 1 bytes
    struct REMAP : public reg8_t<BASE_ADDRESS + 0x000E> {
        using SPI = reg_field_t<BASE_ADDRESS + 0x000E, 0x20, 5>;    //< SPI
        using USART0 = reg_field_t<BASE_ADDRESS + 0x000E, 0x10, 4>;    //< USART0
        using TC0D = reg_field_t<BASE_ADDRESS + 0x000E, 0x08, 3>;    //< Timer/Counter 0 Output Compare D
        using TC0C = reg_field_t<BASE_ADDRESS + 0x000E, 0x04, 2>;    //< Timer/Counter 0 Output Compare C
        using TC0B = reg_field_t<BASE_ADDRESS + 0x000E, 0x02, 1>;    //< Timer/Counter 0 Output Compare B
        using TC0A = reg_field_t<BASE_ADDRESS + 0x000E, 0x01, 0>;    //< Timer/Counter 0 Output Compare A
    };

    /// Pin 0 Control Register - 1 bytes
    struct PIN0CTRL : public reg8_t<BASE_ADDRESS + 0x0010> {
        using SRLEN = reg_field_t<BASE_ADDRESS + 0x0010, 0x80, 7>;    //< Slew Rate Enable
        using INVEN = reg_field_t<BASE_ADDRESS + 0x0010, 0x40, 6>;    //< Inverted I/O Enable
        using OPC = reg_field_t<BASE_ADDRESS + 0x0010, 0x38, 3, OPCv>;    //< Output/Pull Configuration
        using ISC = reg_field_t<BASE_ADDRESS + 0x0010, 0x07, 0, ISCv>;    //< Input/Sense Configuration
    };

    /// Pin 1 Control Register - 1 bytes
    struct PIN1CTRL : public reg8_t<BASE_ADDRESS + 0x0011> {
        using SRLEN = reg_field_t<BASE_ADDRESS + 0x0011, 0x80, 7>;    //< Slew Rate Enable
        using INVEN = reg_field_t<BASE_ADDRESS + 0x0011, 0x40, 6>;    //< Inverted I/O Enable
        using OPC = reg_field_t<BASE_ADDRESS + 0x0011, 0x38, 3, OPCv>;    //< Output/Pull Configuration
        using ISC = reg_field_t<BASE_ADDRESS + 0x0011, 0x07, 0, ISCv>;    //< Input/Sense Configuration
    };

    /// Pin 2 Control Register - 1 bytes
    struct PIN2CTRL : public reg8_t<BASE_ADDRESS + 0x0012> {
        using SRLEN = reg_field_t<BASE_ADDRESS + 0x0012, 0x80, 7>;    //< Slew Rate Enable
        using INVEN = reg_field_t<BASE_ADDRESS + 0x0012, 0x40, 6>;    //< Inverted I/O Enable
        using OPC = reg_field_t<BASE_ADDRESS + 0x0012, 0x38, 3, OPCv>;    //< Output/Pull Configuration
        using ISC = reg_field_t<BASE_ADDRESS + 0x0012, 0x07, 0, ISCv>;    //< Input/Sense Configuration
    };

    /// Pin 3 Control Register - 1 bytes
    struct PIN3CTRL : public reg8_t<BASE_ADDRESS + 0x0013> {
        using SRLEN = reg_field_t<BASE_ADDRESS + 0x0013, 0x80, 7>;    //< Slew Rate Enable
        using INVEN = reg_field_t<BASE_ADDRESS + 0x0013, 0x40, 6>;    //< Inverted I/O Enable
        using OPC = reg_field_t<BASE_ADDRESS + 0x0013, 0x38, 3, OPCv>;    //< Output/Pull Configuration
        using ISC = reg_field_t<BASE_ADDRESS + 0x0013, 0x07, 0, ISCv>;    //< Input/Sense Configuration
    };

    /// Pin 4 Control Register - 1 bytes
    struct PIN4CTRL : public reg8_t<BASE_ADDRESS + 0x0014> {
        using SRLEN = reg_field_t<BASE_ADDRESS + 0x0014, 0x80, 7>;    //< Slew Rate Enable
        using INVEN = reg_field_t<BASE_ADDRESS + 0x0014, 0x40, 6>;    //< Inverted I/O Enable
        using OPC = reg_field_t<BASE_ADDRESS + 0x0014, 0x38, 3, OPCv>;    //< Output/Pull Configuration
        using ISC = reg_field_t<BASE_ADDRESS + 0x0014, 0x07, 0, ISCv>;    //< Input/Sense Configuration
    };

    /// Pin 5 Control Register - 1 bytes
    struct PIN5CTRL : public reg8_t<BASE_ADDRESS + 0x0015> {
        using SRLEN = reg_field_t<BASE_ADDRESS + 0x0015, 0x80, 7>;    //< Slew Rate Enable
        using INVEN = reg_field_t<BASE_ADDRESS + 0x0015, 0x40, 6>;    //< Inverted I/O Enable
        using OPC = reg_field_t<BASE_ADDRESS + 0x0015, 0x38, 3, OPCv>;    //< Output/Pull Configuration
        using ISC = reg_field_t<BASE_ADDRESS + 0x0015, 0x07, 0, ISCv>;    //< Input/Sense Configuration
    };

    /// Pin 6 Control Register - 1 bytes
    struct PIN6CTRL : public reg8_t<BASE_ADDRESS + 0x0016> {
        using SRLEN = reg_field_t<BASE_ADDRESS + 0x0016, 0x80, 7>;    //< Slew Rate Enable
        using INVEN = reg_field_t<BASE_ADDRESS + 0x0016, 0x40, 6>;    //< Inverted I/O Enable
        using OPC = reg_field_t<BASE_ADDRESS + 0x0016, 0x38, 3, OPCv>;    //< Output/Pull Configuration
        using ISC = reg_field_t<BASE_ADDRESS + 0x0016, 0x07, 0, ISCv>;    //< Input/Sense Configuration
    };

    /// Pin 7 Control Register - 1 bytes
    struct PIN7CTRL : public reg8_t<BASE_ADDRESS + 0x0017> {
        using SRLEN = reg_field_t<BASE_ADDRESS + 0x0017, 0x80, 7>;    //< Slew Rate Enable
        using INVEN = reg_field_t<BASE_ADDRESS + 0x0017, 0x40, 6>;    //< Inverted I/O Enable
        using OPC = reg_field_t<BASE_ADDRESS + 0x0017, 0x38, 3, OPCv>;    //< Output/Pull Configuration
        using ISC = reg_field_t<BASE_ADDRESS + 0x0017, 0x07, 0, ISCv>;    //< Input/Sense Configuration
    };
};

} // namespace device
