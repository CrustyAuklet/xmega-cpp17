/**
 * XMEGAAU-AWEX (id I6090)
 * Timer/Counter Advanced Waveform Extension
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * AWEX
 * Advanced Waveform Extension
 * Size: 13 bytes
 */
template <addressType BASE_ADDRESS>
struct AWEX_t {

    // Fault Detect Action
    enum class FDACTv : uint8_t {
        NONE = 0x00, // No Fault Protection
        CLEAROE = 0x01, // Clear Output Enable Bits
        CLEARDIR = 0x03, // Clear I/O Port Direction Bits
    };


    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using PGM = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< Pattern Generation Mode
        using CWCM = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Common Waveform Channel Mode
        using DTICCDEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x08, 3>;    //< Dead Time Insertion Compare Channel D Enable
        using DTICCCEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< Dead Time Insertion Compare Channel C Enable
        using DTICCBEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x02, 1>;    //< Dead Time Insertion Compare Channel B Enable
        using DTICCAEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Dead Time Insertion Compare Channel A Enable
    };

    /// Fault Detection Event Mask - 1 bytes
    struct FDEMASK : public reg8_t<BASE_ADDRESS + 0x0002> {
    };

    /// Fault Detection Control Register - 1 bytes
    struct FDCTRL : public reg8_t<BASE_ADDRESS + 0x0003> {
        using FDDBD = reg_field_t<BASE_ADDRESS + 0x0003, 0x10, 4>;    //< Fault Detect on Disable Break Disable
        using FDMODE = reg_field_t<BASE_ADDRESS + 0x0003, 0x04, 2>;    //< Fault Detect Mode
        using FDACT = reg_field_t<BASE_ADDRESS + 0x0003, 0x03, 0, FDACTv>;    //< Fault Detect Action
    };

    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0004> {
        using FDF = reg_field_t<BASE_ADDRESS + 0x0004, 0x04, 2>;    //< Fault Detect Flag
        using DTHSBUFV = reg_field_t<BASE_ADDRESS + 0x0004, 0x02, 1>;    //< Dead Time High Side Buffer Valid
        using DTLSBUFV = reg_field_t<BASE_ADDRESS + 0x0004, 0x01, 0>;    //< Dead Time Low Side Buffer Valid
    };

    /// Status Set Register - 1 bytes
    struct STATUSSET : public reg8_t<BASE_ADDRESS + 0x0005> {
        using FDF = reg_field_t<BASE_ADDRESS + 0x0005, 0x04, 2>;    //< Fault Detect Flag
        using DTHSBUFV = reg_field_t<BASE_ADDRESS + 0x0005, 0x02, 1>;    //< Dead Time High Side Buffer Valid
        using DTLSBUFV = reg_field_t<BASE_ADDRESS + 0x0005, 0x01, 0>;    //< Dead Time Low Side Buffer Valid
    };

    /// Dead Time Both Sides - 1 bytes
    struct DTBOTH : public reg8_t<BASE_ADDRESS + 0x0006> {
    };

    /// Dead Time Both Sides Buffer - 1 bytes
    struct DTBOTHBUF : public reg8_t<BASE_ADDRESS + 0x0007> {
    };

    /// Dead Time Low Side - 1 bytes
    struct DTLS : public reg8_t<BASE_ADDRESS + 0x0008> {
    };

    /// Dead Time High Side - 1 bytes
    struct DTHS : public reg8_t<BASE_ADDRESS + 0x0009> {
    };

    /// Dead Time Low Side Buffer - 1 bytes
    struct DTLSBUF : public reg8_t<BASE_ADDRESS + 0x000A> {
    };

    /// Dead Time High Side Buffer - 1 bytes
    struct DTHSBUF : public reg8_t<BASE_ADDRESS + 0x000B> {
    };

    /// Output Override Enable - 1 bytes
    struct OUTOVEN : public reg8_t<BASE_ADDRESS + 0x000C> {
    };
};

} // namespace device
