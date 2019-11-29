/**
 * None-CPU (id I6000)
 * CPU
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace CPU {

    // CCP signatures
    enum class CCPv : uint8_t {
        SPM = 0x9D, // SPM Instruction Protection
        IOREG = 0xD8, // IO Register Protection
    };
}   // namespace CPU

/**
 * CPU
 * CPU registers
 * Size: 16 bytes
 */
template <addressType BASE_ADDRESS>
struct CPU_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Configuration Change Protection - 1 bytes
    static constexpr struct CCP_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<CCP_t, 7, 0, CPU::CCPv> CCP = {};    //< CCP signature
    } CCP = {};

    /// Ramp D - 1 bytes
    static constexpr struct RAMPD_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0008>::operator=;
    } RAMPD = {};

    /// Ramp X - 1 bytes
    static constexpr struct RAMPX_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0009>::operator=;
    } RAMPX = {};

    /// Ramp Y - 1 bytes
    static constexpr struct RAMPY_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000A>::operator=;
    } RAMPY = {};

    /// Ramp Z - 1 bytes
    static constexpr struct RAMPZ_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000B>::operator=;
    } RAMPZ = {};

    /// Extended Indirect Jump - 1 bytes
    static constexpr struct EIND_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000C>::operator=;
    } EIND = {};

    /// Stack Pointer Low - 1 bytes
    static constexpr struct SPL_t : reg_t<uint8_t, BASE_ADDRESS + 0x000D> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000D>::operator=;
    } SPL = {};

    /// Stack Pointer High - 1 bytes
    static constexpr struct SPH_t : reg_t<uint8_t, BASE_ADDRESS + 0x000E> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000E>::operator=;
    } SPH = {};

    /// Status Register - 1 bytes
    static constexpr struct SREG_t : reg_t<uint8_t, BASE_ADDRESS + 0x000F> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000F>::operator=;
        static constexpr bitfield_t<SREG_t, 7, 7, bool> I = {};    //< Global Interrupt Enable Flag
        static constexpr bitfield_t<SREG_t, 6, 6, bool> T = {};    //< Transfer Bit
        static constexpr bitfield_t<SREG_t, 5, 5, bool> H = {};    //< Half Carry Flag
        static constexpr bitfield_t<SREG_t, 4, 4, bool> S = {};    //< N Exclusive Or V Flag
        static constexpr bitfield_t<SREG_t, 3, 3, bool> V = {};    //< Two's Complement Overflow Flag
        static constexpr bitfield_t<SREG_t, 2, 2, bool> N = {};    //< Negative Flag
        static constexpr bitfield_t<SREG_t, 1, 1, bool> Z = {};    //< Zero Flag
        static constexpr bitfield_t<SREG_t, 0, 0, bool> C = {};    //< Carry Flag
    } SREG = {};

};

} // namespace sfr
