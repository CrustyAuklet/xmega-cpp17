/**
 * XMEGAAU-SPI (id I6090)
 * Serial Peripheral Interface
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * SPI
 * Serial Peripheral Interface
 * Size: 4 bytes
 */
template <addressType BASE_ADDRESS>
struct SPI_t {

    // SPI Mode
    enum class MODEv : uint8_t {
        _0 = 0x00, // SPI Mode 0
        _1 = 0x01, // SPI Mode 1
        _2 = 0x02, // SPI Mode 2
        _3 = 0x03, // SPI Mode 3
    };

    // Prescaler setting
    enum class PRESCALERv : uint8_t {
        DIV4 = 0x00, // System Clock / 4
        DIV16 = 0x01, // System Clock / 16
        DIV64 = 0x02, // System Clock / 64
        DIV128 = 0x03, // System Clock / 128
    };

    // Interrupt level
    enum class INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // SPI ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        INT = 0, // SPI Interrupt
    };

    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using CLK2X = reg_field_t<BASE_ADDRESS + 0x0000, 0x80, 7>;    //< Enable Double Speed
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x40, 6>;    //< Enable Module
        using DORD = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< Data Order Setting
        using MASTER = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Master Operation Enable
        using MODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x0C, 2, MODEv>;    //< SPI Mode
        using PRESCALER = reg_field_t<BASE_ADDRESS + 0x0000, 0x03, 0, PRESCALERv>;    //< Prescaler
    };

    /// Interrupt Control Register - 1 bytes
    struct INTCTRL : public reg8_t<BASE_ADDRESS + 0x0001> {
        using INTLVL = reg_field_t<BASE_ADDRESS + 0x0001, 0x03, 0, INTLVLv>;    //< Interrupt level
    };

    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0002> {
        using IF = reg_field_t<BASE_ADDRESS + 0x0002, 0x80, 7>;    //< Interrupt Flag
        using WRCOL = reg_field_t<BASE_ADDRESS + 0x0002, 0x40, 6>;    //< Write Collision
    };

    /// Data Register - 1 bytes
    struct DATA : public reg8_t<BASE_ADDRESS + 0x0003> {
    };
};

} // namespace device
