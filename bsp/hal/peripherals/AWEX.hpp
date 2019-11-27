/**
 * XMEGAAU-AWEX (id I6090)
 * Timer/Counter Advanced Waveform Extension
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace AWEX {

    // Fault Detect Action
    enum class FDACTv : uint8_t {
        NONE = 0x00, // No Fault Protection
        CLEAROE = 0x01, // Clear Output Enable Bits
        CLEARDIR = 0x03, // Clear I/O Port Direction Bits
    };

}   // namespace AWEX

/**
 * AWEX
 * Advanced Waveform Extension
 * Size: 13 bytes
 */
template <addressType BASE_ADDRESS>
struct AWEX_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRL_t, 0x20, 5> PGM = {};    //< Pattern Generation Mode
        static constexpr bitfield_t<CTRL_t, 0x10, 4> CWCM = {};    //< Common Waveform Channel Mode
        static constexpr bitfield_t<CTRL_t, 0x08, 3> DTICCDEN = {};    //< Dead Time Insertion Compare Channel D Enable
        static constexpr bitfield_t<CTRL_t, 0x04, 2> DTICCCEN = {};    //< Dead Time Insertion Compare Channel C Enable
        static constexpr bitfield_t<CTRL_t, 0x02, 1> DTICCBEN = {};    //< Dead Time Insertion Compare Channel B Enable
        static constexpr bitfield_t<CTRL_t, 0x01, 0> DTICCAEN = {};    //< Dead Time Insertion Compare Channel A Enable
    } CTRL = {};

    /// Fault Detection Event Mask - 1 bytes
    static constexpr struct FDEMASK_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
    } FDEMASK = {};

    /// Fault Detection Control Register - 1 bytes
    static constexpr struct FDCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<FDCTRL_t, 0x10, 4> FDDBD = {};    //< Fault Detect on Disable Break Disable
        static constexpr bitfield_t<FDCTRL_t, 0x04, 2> FDMODE = {};    //< Fault Detect Mode
        static constexpr bitfield_t<FDCTRL_t, 0x03, 0, FDACTv> FDACT = {};    //< Fault Detect Action
    } FDCTRL = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        static constexpr bitfield_t<STATUS_t, 0x04, 2> FDF = {};    //< Fault Detect Flag
        static constexpr bitfield_t<STATUS_t, 0x02, 1> DTHSBUFV = {};    //< Dead Time High Side Buffer Valid
        static constexpr bitfield_t<STATUS_t, 0x01, 0> DTLSBUFV = {};    //< Dead Time Low Side Buffer Valid
    } STATUS = {};

    /// Status Set Register - 1 bytes
    static constexpr struct STATUSSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        static constexpr bitfield_t<STATUSSET_t, 0x04, 2> FDF = {};    //< Fault Detect Flag
        static constexpr bitfield_t<STATUSSET_t, 0x02, 1> DTHSBUFV = {};    //< Dead Time High Side Buffer Valid
        static constexpr bitfield_t<STATUSSET_t, 0x01, 0> DTLSBUFV = {};    //< Dead Time Low Side Buffer Valid
    } STATUSSET = {};

    /// Dead Time Both Sides - 1 bytes
    static constexpr struct DTBOTH_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
    } DTBOTH = {};

    /// Dead Time Both Sides Buffer - 1 bytes
    static constexpr struct DTBOTHBUF_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
    } DTBOTHBUF = {};

    /// Dead Time Low Side - 1 bytes
    static constexpr struct DTLS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
    } DTLS = {};

    /// Dead Time High Side - 1 bytes
    static constexpr struct DTHS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
    } DTHS = {};

    /// Dead Time Low Side Buffer - 1 bytes
    static constexpr struct DTLSBUF_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
    } DTLSBUF = {};

    /// Dead Time High Side Buffer - 1 bytes
    static constexpr struct DTHSBUF_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
    } DTHSBUF = {};

    /// Output Override Enable - 1 bytes
    static constexpr struct OUTOVEN_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
    } OUTOVEN = {};

};

} // namespace device
