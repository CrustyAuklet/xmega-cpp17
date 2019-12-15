/**
 * XMEGAAU-AWEX (id I6090)
 * Timer/Counter Advanced Waveform Extension
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

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
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRL_t, 5, 5, bool> PGM = {};    //< Pattern Generation Mode
        static constexpr bitfield_t<CTRL_t, 4, 4, bool> CWCM = {};    //< Common Waveform Channel Mode
        static constexpr bitfield_t<CTRL_t, 3, 3, bool> DTICCDEN = {};    //< Dead Time Insertion Compare Channel D Enable
        static constexpr bitfield_t<CTRL_t, 2, 2, bool> DTICCCEN = {};    //< Dead Time Insertion Compare Channel C Enable
        static constexpr bitfield_t<CTRL_t, 1, 1, bool> DTICCBEN = {};    //< Dead Time Insertion Compare Channel B Enable
        static constexpr bitfield_t<CTRL_t, 0, 0, bool> DTICCAEN = {};    //< Dead Time Insertion Compare Channel A Enable
    } CTRL = {};

    /// Fault Detection Event Mask - 1 bytes
    static constexpr struct FDEMASK_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
    } FDEMASK = {};

    /// Fault Detection Control Register - 1 bytes
    static constexpr struct FDCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<FDCTRL_t, 4, 4, bool> FDDBD = {};    //< Fault Detect on Disable Break Disable
        static constexpr bitfield_t<FDCTRL_t, 2, 2, bool> FDMODE = {};    //< Fault Detect Mode
        static constexpr bitfield_t<FDCTRL_t, 1, 0, AWEX::FDACTv> FDACT = {};    //< Fault Detect Action
    } FDCTRL = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<STATUS_t, 2, 2, bool> FDF = {};    //< Fault Detect Flag
        static constexpr bitfield_t<STATUS_t, 1, 1, bool> DTHSBUFV = {};    //< Dead Time High Side Buffer Valid
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> DTLSBUFV = {};    //< Dead Time Low Side Buffer Valid
    } STATUS = {};

    /// Status Set Register - 1 bytes
    static constexpr struct STATUSSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
        static constexpr bitfield_t<STATUSSET_t, 2, 2, bool> FDF = {};    //< Fault Detect Flag
        static constexpr bitfield_t<STATUSSET_t, 1, 1, bool> DTHSBUFV = {};    //< Dead Time High Side Buffer Valid
        static constexpr bitfield_t<STATUSSET_t, 0, 0, bool> DTLSBUFV = {};    //< Dead Time Low Side Buffer Valid
    } STATUSSET = {};

    /// Dead Time Both Sides - 1 bytes
    static constexpr struct DTBOTH_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
    } DTBOTH = {};

    /// Dead Time Both Sides Buffer - 1 bytes
    static constexpr struct DTBOTHBUF_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0007>::operator=;
    } DTBOTHBUF = {};

    /// Dead Time Low Side - 1 bytes
    static constexpr struct DTLS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0008>::operator=;
    } DTLS = {};

    /// Dead Time High Side - 1 bytes
    static constexpr struct DTHS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0009>::operator=;
    } DTHS = {};

    /// Dead Time Low Side Buffer - 1 bytes
    static constexpr struct DTLSBUF_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000A>::operator=;
    } DTLSBUF = {};

    /// Dead Time High Side Buffer - 1 bytes
    static constexpr struct DTHSBUF_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000B>::operator=;
    } DTHSBUF = {};

    /// Output Override Enable - 1 bytes
    static constexpr struct OUTOVEN_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000C>::operator=;
    } OUTOVEN = {};

};

} // namespace sfr
