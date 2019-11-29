/**
 * XMEGAAU-SPI (id I6090)
 * Serial Peripheral Interface
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace SPI {

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
}   // namespace SPI

/**
 * SPI
 * Serial Peripheral Interface
 * Size: 4 bytes
 */
template <addressType BASE_ADDRESS>
struct SPI_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRL_t, 7, 7, bool> CLK2X = {};    //< Enable Double Speed
        static constexpr bitfield_t<CTRL_t, 6, 6, bool> ENABLE = {};    //< Enable Module
        static constexpr bitfield_t<CTRL_t, 5, 5, bool> DORD = {};    //< Data Order Setting
        static constexpr bitfield_t<CTRL_t, 4, 4, bool> MASTER = {};    //< Master Operation Enable
        static constexpr bitfield_t<CTRL_t, 3, 2, SPI::MODEv> MODE = {};    //< SPI Mode
        static constexpr bitfield_t<CTRL_t, 1, 0, SPI::PRESCALERv> PRESCALER = {};    //< Prescaler
    } CTRL = {};

    /// Interrupt Control Register - 1 bytes
    static constexpr struct INTCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<INTCTRL_t, 1, 0, SPI::INTLVLv> INTLVL = {};    //< Interrupt level
    } INTCTRL = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<STATUS_t, 7, 7, bool> IF = {};    //< Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 6, 6, bool> WRCOL = {};    //< Write Collision
    } STATUS = {};

    /// Data Register - 1 bytes
    static constexpr struct DATA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
    } DATA = {};

    // SPI ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        INT = 0, // SPI Interrupt
    };
};

} // namespace sfr
