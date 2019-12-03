/**
 * None-AES (id I6096)
 * AES Module
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace AES {

    // Interrupt level
    enum class INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };
}   // namespace AES

/**
 * AES
 * AES Module
 * Size: 5 bytes
 */
template <addressType BASE_ADDRESS>
struct AES_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// AES Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRL_t, 7, 7, bool> START = {};    //< Start/Run
        static constexpr bitfield_t<CTRL_t, 6, 6, bool> AUTO = {};    //< Auto Start Trigger
        static constexpr bitfield_t<CTRL_t, 5, 5, bool> RESET = {};    //< AES Software Reset
        static constexpr bitfield_t<CTRL_t, 4, 4, bool> DECRYPT = {};    //< Decryption / Direction
        static constexpr bitfield_t<CTRL_t, 2, 2, bool> XOR = {};    //< State XOR Load Enable
    } CTRL = {};

    /// AES Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<STATUS_t, 7, 7, bool> ERROR = {};    //< AES Error
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> SRIF = {};    //< State Ready Interrupt Flag
    } STATUS = {};

    /// AES State Register - 1 bytes
    static constexpr struct STATE_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
    } STATE = {};

    /// AES Key Register - 1 bytes
    static constexpr struct KEY_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
    } KEY = {};

    /// AES Interrupt Control Register - 1 bytes
    static constexpr struct INTCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<INTCTRL_t, 1, 0, AES::INTLVLv> INTLVL = {};    //< Interrupt level
    } INTCTRL = {};

    // AES ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        INT = 0, // AES Interrupt
    };
};

} // namespace sfr
