/**
 * None-CPU (id I6000)
 * CPU
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * CPU
 * CPU registers
 * Size: 16 bytes
 */
template <addressType BASE_ADDRESS>
struct CPU_t {

    // CCP signatures
    enum class CCPv : uint8_t {
        SPM = 0x9D, // SPM Instruction Protection
        IOREG = 0xD8, // IO Register Protection
    };


    /// Configuration Change Protection - 1 bytes
    struct CCP : public reg8_t<BASE_ADDRESS + 0x0004> {
        using CCPf = reg_field_t<BASE_ADDRESS + 0x0004, 0xFF, 0, CCPv>;    //< CCP signature
    };

    /// Ramp D - 1 bytes
    struct RAMPD : public reg8_t<BASE_ADDRESS + 0x0008> {
    };

    /// Ramp X - 1 bytes
    struct RAMPX : public reg8_t<BASE_ADDRESS + 0x0009> {
    };

    /// Ramp Y - 1 bytes
    struct RAMPY : public reg8_t<BASE_ADDRESS + 0x000A> {
    };

    /// Ramp Z - 1 bytes
    struct RAMPZ : public reg8_t<BASE_ADDRESS + 0x000B> {
    };

    /// Extended Indirect Jump - 1 bytes
    struct EIND : public reg8_t<BASE_ADDRESS + 0x000C> {
    };

    /// Stack Pointer Low - 1 bytes
    struct SPL : public reg8_t<BASE_ADDRESS + 0x000D> {
    };

    /// Stack Pointer High - 1 bytes
    struct SPH : public reg8_t<BASE_ADDRESS + 0x000E> {
    };

    /// Status Register - 1 bytes
    struct SREG : public reg8_t<BASE_ADDRESS + 0x000F> {
        using I = reg_field_t<BASE_ADDRESS + 0x000F, 0x80, 7>;    //< Global Interrupt Enable Flag
        using T = reg_field_t<BASE_ADDRESS + 0x000F, 0x40, 6>;    //< Transfer Bit
        using H = reg_field_t<BASE_ADDRESS + 0x000F, 0x20, 5>;    //< Half Carry Flag
        using S = reg_field_t<BASE_ADDRESS + 0x000F, 0x10, 4>;    //< N Exclusive Or V Flag
        using V = reg_field_t<BASE_ADDRESS + 0x000F, 0x08, 3>;    //< Two's Complement Overflow Flag
        using N = reg_field_t<BASE_ADDRESS + 0x000F, 0x04, 2>;    //< Negative Flag
        using Z = reg_field_t<BASE_ADDRESS + 0x000F, 0x02, 1>;    //< Zero Flag
        using C = reg_field_t<BASE_ADDRESS + 0x000F, 0x01, 0>;    //< Carry Flag
    };
};

} // namespace device
