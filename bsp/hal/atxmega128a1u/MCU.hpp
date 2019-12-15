/**
 * XMEGAAU-MCU (id I6091)
 * MCU Control
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace MCU {

}   // namespace MCU

/**
 * MCU
 * MCU Control
 * Size: 12 bytes
 */
template <addressType BASE_ADDRESS>
struct MCU_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Device ID byte 0 - 1 bytes
    static constexpr struct DEVID0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
    } DEVID0 = {};

    /// Device ID byte 1 - 1 bytes
    static constexpr struct DEVID1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
    } DEVID1 = {};

    /// Device ID byte 2 - 1 bytes
    static constexpr struct DEVID2_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
    } DEVID2 = {};

    /// Revision ID - 1 bytes
    static constexpr struct REVID_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
    } REVID = {};

    /// JTAG User ID - 1 bytes
    static constexpr struct JTAGUID_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
    } JTAGUID = {};

    /// MCU Control - 1 bytes
    static constexpr struct MCUCR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
        static constexpr bitfield_t<MCUCR_t, 0, 0, bool> JTAGD = {};    //< JTAG Disable
    } MCUCR = {};

    /// Analog Startup Delay - 1 bytes
    static constexpr struct ANAINIT_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0007>::operator=;
        static constexpr bitfield_t<ANAINIT_t, 3, 2> STARTUPDLYB = {};    //< Analog startup delay Port B
        static constexpr bitfield_t<ANAINIT_t, 1, 0> STARTUPDLYA = {};    //< Analog startup delay Port A
    } ANAINIT = {};

    /// Event System Lock - 1 bytes
    static constexpr struct EVSYSLOCK_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0008>::operator=;
        static constexpr bitfield_t<EVSYSLOCK_t, 4, 4, bool> EVSYS1LOCK = {};    //< Event Channel 4-7 Lock
        static constexpr bitfield_t<EVSYSLOCK_t, 0, 0, bool> EVSYS0LOCK = {};    //< Event Channel 0-3 Lock
    } EVSYSLOCK = {};

    /// AWEX Lock - 1 bytes
    static constexpr struct AWEXLOCK_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0009>::operator=;
        static constexpr bitfield_t<AWEXLOCK_t, 3, 3, bool> AWEXFLOCK = {};    //< AWeX on T/C F0 Lock
        static constexpr bitfield_t<AWEXLOCK_t, 2, 2, bool> AWEXELOCK = {};    //< AWeX on T/C E0 Lock
        static constexpr bitfield_t<AWEXLOCK_t, 1, 1, bool> AWEXDLOCK = {};    //< AWeX on T/C D0 Lock
        static constexpr bitfield_t<AWEXLOCK_t, 0, 0, bool> AWEXCLOCK = {};    //< AWeX on T/C C0 Lock
    } AWEXLOCK = {};

};

} // namespace sfr
