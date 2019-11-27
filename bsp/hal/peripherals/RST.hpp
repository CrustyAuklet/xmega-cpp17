/**
 * XMEGAAU-RST (id I6083)
 * Reset
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

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
        static constexpr bitfield_t<STATUS_t, 0x40, 6> SDRF = {};    //< Spike Detection Reset Flag
        static constexpr bitfield_t<STATUS_t, 0x20, 5> SRF = {};    //< Software Reset Flag
        static constexpr bitfield_t<STATUS_t, 0x10, 4> PDIRF = {};    //< Programming and Debug Interface Interface Reset Flag
        static constexpr bitfield_t<STATUS_t, 0x08, 3> WDRF = {};    //< Watchdog Reset Flag
        static constexpr bitfield_t<STATUS_t, 0x04, 2> BORF = {};    //< Brown-out Reset Flag
        static constexpr bitfield_t<STATUS_t, 0x02, 1> EXTRF = {};    //< External Reset Flag
        static constexpr bitfield_t<STATUS_t, 0x01, 0> PORF = {};    //< Power-on Reset Flag
    } STATUS = {};

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<CTRL_t, 0x01, 0> SWRST = {};    //< Software Reset
    } CTRL = {};

};

} // namespace device
