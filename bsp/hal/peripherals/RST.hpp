/**
 * XMEGAAU-RST (id I6083)
 * Reset
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace RST {

}   // namespace RST

/**
 * RST
 * Reset
 * Size: 2 bytes
 */
template <addressType BASE_ADDRESS>
struct RST_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<STATUS_t, 6, 6, bool> SDRF = {};    //< Spike Detection Reset Flag
        static constexpr bitfield_t<STATUS_t, 5, 5, bool> SRF = {};    //< Software Reset Flag
        static constexpr bitfield_t<STATUS_t, 4, 4, bool> PDIRF = {};    //< Programming and Debug Interface Interface Reset Flag
        static constexpr bitfield_t<STATUS_t, 3, 3, bool> WDRF = {};    //< Watchdog Reset Flag
        static constexpr bitfield_t<STATUS_t, 2, 2, bool> BORF = {};    //< Brown-out Reset Flag
        static constexpr bitfield_t<STATUS_t, 1, 1, bool> EXTRF = {};    //< External Reset Flag
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> PORF = {};    //< Power-on Reset Flag
    } STATUS = {};

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<CTRL_t, 0, 0, bool> SWRST = {};    //< Software Reset
    } CTRL = {};

};

} // namespace sfr
