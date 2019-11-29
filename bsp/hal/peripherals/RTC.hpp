/**
 * None-RTC (id I6093)
 * Real-Time Counter
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace RTC {

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
}   // namespace RTC

/**
 * RTC
 * Real-Time Counter
 * Size: 14 bytes
 */
template <addressType BASE_ADDRESS>
struct RTC_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRL_t, 2, 0, RTC::PRESCALERv> PRESCALER = {};    //< Prescaling Factor
    } CTRL = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> SYNCBUSY = {};    //< Synchronization Busy Flag
    } STATUS = {};

    /// Interrupt Control Register - 1 bytes
    static constexpr struct INTCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<INTCTRL_t, 3, 2, RTC::COMPINTLVLv> COMPINTLVL = {};    //< Compare Match Interrupt Level
        static constexpr bitfield_t<INTCTRL_t, 1, 0, RTC::OVFINTLVLv> OVFINTLVL = {};    //< Overflow Interrupt Level
    } INTCTRL = {};

    /// Interrupt Flags - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<INTFLAGS_t, 1, 1, bool> COMPIF = {};    //< Compare Match Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0, 0, bool> OVFIF = {};    //< Overflow Interrupt Flag
    } INTFLAGS = {};

    /// Temporary register - 1 bytes
    static constexpr struct TEMP_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
    } TEMP = {};

    /// Count Register - 2 bytes
    static constexpr struct CNT_t : reg_t<uint16_t, BASE_ADDRESS + 0x0008> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0008>::operator=;
    } CNT = {};

    /// Period Register - 2 bytes
    static constexpr struct PER_t : reg_t<uint16_t, BASE_ADDRESS + 0x000A> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x000A>::operator=;
    } PER = {};

    /// Compare Register - 2 bytes
    static constexpr struct COMP_t : reg_t<uint16_t, BASE_ADDRESS + 0x000C> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x000C>::operator=;
    } COMP = {};

    // RTC ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        OVF = 0, // Overflow Interrupt
        COMP = 1, // Compare Interrupt
    };
};

} // namespace sfr
