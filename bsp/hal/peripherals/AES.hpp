/**
 * None-AES (id I6096)
 * AES Module
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace AES {

    // Interrupt level
    enum class INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // AES ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        INT = 0, // AES Interrupt
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
        static constexpr bitfield_t<CTRL_t, 0x80, 7> START = {};    //< Start/Run
        static constexpr bitfield_t<CTRL_t, 0x40, 6> AUTO = {};    //< Auto Start Trigger
        static constexpr bitfield_t<CTRL_t, 0x20, 5> RESET = {};    //< AES Software Reset
        static constexpr bitfield_t<CTRL_t, 0x10, 4> DECRYPT = {};    //< Decryption / Direction
        static constexpr bitfield_t<CTRL_t, 0x04, 2> XOR = {};    //< State XOR Load Enable
    } CTRL = {};

    /// AES Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<STATUS_t, 0x80, 7> ERROR = {};    //< AES Error
        static constexpr bitfield_t<STATUS_t, 0x01, 0> SRIF = {};    //< State Ready Interrupt Flag
    } STATUS = {};

    /// AES State Register - 1 bytes
    static constexpr struct STATE_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
    } STATE = {};

    /// AES Key Register - 1 bytes
    static constexpr struct KEY_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
    } KEY = {};

    /// AES Interrupt Control Register - 1 bytes
    static constexpr struct INTCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        static constexpr bitfield_t<INTCTRL_t, 0x03, 0, INTLVLv> INTLVL = {};    //< Interrupt level
    } INTCTRL = {};

};

} // namespace device
