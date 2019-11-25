/**
 * None-AES (id I6096)
 * AES Module
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * AES
 * AES Module
 * Size: 5 bytes
 */
template <addressType BASE_ADDRESS>
struct AES_t {

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

    /// AES Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using START = reg_field_t<BASE_ADDRESS + 0x0000, 0x80, 7>;    //< Start/Run
        using AUTO = reg_field_t<BASE_ADDRESS + 0x0000, 0x40, 6>;    //< Auto Start Trigger
        using RESET = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< AES Software Reset
        using DECRYPT = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Decryption / Direction
        using XOR = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< State XOR Load Enable
    };

    /// AES Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0001> {
        using ERROR = reg_field_t<BASE_ADDRESS + 0x0001, 0x80, 7>;    //< AES Error
        using SRIF = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< State Ready Interrupt Flag
    };

    /// AES State Register - 1 bytes
    struct STATE : public reg8_t<BASE_ADDRESS + 0x0002> {
    };

    /// AES Key Register - 1 bytes
    struct KEY : public reg8_t<BASE_ADDRESS + 0x0003> {
    };

    /// AES Interrupt Control Register - 1 bytes
    struct INTCTRL : public reg8_t<BASE_ADDRESS + 0x0004> {
        using INTLVL = reg_field_t<BASE_ADDRESS + 0x0004, 0x03, 0, INTLVLv>;    //< Interrupt level
    };
};

} // namespace device
