/**
 * None-RTC (id I6093)
 * Real-Time Counter
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * RTC
 * Real-Time Counter
 * Size: 14 bytes
 */
template <addressType BASE_ADDRESS>
struct RTC_t {

    // Prescaler Factor
    enum class PRESCALERv : uint8_t {
        OFF = 0x00, // RTC Off
        DIV1 = 0x01, // RTC Clock
        DIV2 = 0x02, // RTC Clock / 2
        DIV8 = 0x03, // RTC Clock / 8
        DIV16 = 0x04, // RTC Clock / 16
        DIV64 = 0x05, // RTC Clock / 64
        DIV256 = 0x06, // RTC Clock / 256
        DIV1024 = 0x07, // RTC Clock / 1024
    };

    // Compare Interrupt level
    enum class COMPINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Overflow Interrupt level
    enum class OVFINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // RTC ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        OVF = 0, // Overflow Interrupt
        COMP = 1, // Compare Interrupt
    };

    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using PRESCALER = reg_field_t<BASE_ADDRESS + 0x0000, 0x07, 0, PRESCALERv>;    //< Prescaling Factor
    };

    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0001> {
        using SYNCBUSY = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Synchronization Busy Flag
    };

    /// Interrupt Control Register - 1 bytes
    struct INTCTRL : public reg8_t<BASE_ADDRESS + 0x0002> {
        using COMPINTLVL = reg_field_t<BASE_ADDRESS + 0x0002, 0x0C, 2, COMPINTLVLv>;    //< Compare Match Interrupt Level
        using OVFINTLVL = reg_field_t<BASE_ADDRESS + 0x0002, 0x03, 0, OVFINTLVLv>;    //< Overflow Interrupt Level
    };

    /// Interrupt Flags - 1 bytes
    struct INTFLAGS : public reg8_t<BASE_ADDRESS + 0x0003> {
        using COMPIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x02, 1>;    //< Compare Match Interrupt Flag
        using OVFIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x01, 0>;    //< Overflow Interrupt Flag
    };

    /// Temporary register - 1 bytes
    struct TEMP : public reg8_t<BASE_ADDRESS + 0x0004> {
    };

    /// Count Register - 2 bytes
    struct CNT : public reg16_t<BASE_ADDRESS + 0x0008> {
    };

    /// Period Register - 2 bytes
    struct PER : public reg16_t<BASE_ADDRESS + 0x000A> {
    };

    /// Compare Register - 2 bytes
    struct COMP : public reg16_t<BASE_ADDRESS + 0x000C> {
    };
};

} // namespace device
