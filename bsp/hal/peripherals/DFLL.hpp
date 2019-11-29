/**
 * XMEGAAU-DFLL (id I6055)
 * DFLL
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace DFLL {

}   // namespace DFLL

/**
 * DFLL
 * DFLL
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct DFLL_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRL_t, 0, 0, bool> ENABLE = {};    //< DFLL Enable
    } CTRL = {};

    /// Calibration Register A - 1 bytes
    static constexpr struct CALA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<CALA_t, 6, 0> CALL = {};    //< DFLL Calibration Value A
    } CALA = {};

    /// Calibration Register B - 1 bytes
    static constexpr struct CALB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<CALB_t, 5, 0> CALH = {};    //< DFLL Calibration Value B
    } CALB = {};

    /// Oscillator Compare Register 0 - 1 bytes
    static constexpr struct COMP0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
    } COMP0 = {};

    /// Oscillator Compare Register 1 - 1 bytes
    static constexpr struct COMP1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
    } COMP1 = {};

    /// Oscillator Compare Register 2 - 1 bytes
    static constexpr struct COMP2_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
    } COMP2 = {};

};

} // namespace sfr
