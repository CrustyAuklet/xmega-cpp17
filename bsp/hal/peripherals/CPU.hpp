/**
 * None-CPU (id I6000)
 * CPU
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

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
        static constexpr bitfield_t<CCP_t, 0xFF, 0, CCPv> CCP = {};    //< CCP signature
    } CCP = {};

    /// Ramp D - 1 bytes
    static constexpr struct RAMPD_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
    } RAMPD = {};

    /// Ramp X - 1 bytes
    static constexpr struct RAMPX_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
    } RAMPX = {};

    /// Ramp Y - 1 bytes
    static constexpr struct RAMPY_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
    } RAMPY = {};

    /// Ramp Z - 1 bytes
    static constexpr struct RAMPZ_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
    } RAMPZ = {};

    /// Extended Indirect Jump - 1 bytes
    static constexpr struct EIND_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
    } EIND = {};

    /// Stack Pointer Low - 1 bytes
    static constexpr struct SPL_t : reg_t<uint8_t, BASE_ADDRESS + 0x000D> {
    } SPL = {};

    /// Stack Pointer High - 1 bytes
    static constexpr struct SPH_t : reg_t<uint8_t, BASE_ADDRESS + 0x000E> {
    } SPH = {};

    /// Status Register - 1 bytes
    static constexpr struct SREG_t : reg_t<uint8_t, BASE_ADDRESS + 0x000F> {
        static constexpr bitfield_t<SREG_t, 0x80, 7> I = {};    //< Global Interrupt Enable Flag
        static constexpr bitfield_t<SREG_t, 0x40, 6> T = {};    //< Transfer Bit
        static constexpr bitfield_t<SREG_t, 0x20, 5> H = {};    //< Half Carry Flag
        static constexpr bitfield_t<SREG_t, 0x10, 4> S = {};    //< N Exclusive Or V Flag
        static constexpr bitfield_t<SREG_t, 0x08, 3> V = {};    //< Two's Complement Overflow Flag
        static constexpr bitfield_t<SREG_t, 0x04, 2> N = {};    //< Negative Flag
        static constexpr bitfield_t<SREG_t, 0x02, 1> Z = {};    //< Zero Flag
        static constexpr bitfield_t<SREG_t, 0x01, 0> C = {};    //< Carry Flag
    } SREG = {};

};

} // namespace device
