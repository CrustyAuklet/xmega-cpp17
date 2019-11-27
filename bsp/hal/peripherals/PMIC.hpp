/**
 * None-PMIC (id I6057)
 * Programmable Multi-level Interrupt Controller
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace PMIC {

}   // namespace PMIC

/**
 * PMIC
 * Programmable Multi-level Interrupt Controller
 * Size: 16 bytes
 */
template <addressType BASE_ADDRESS>
struct PMIC_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<STATUS_t, 0x80, 7> NMIEX = {};    //< Non-maskable Interrupt Executing
        static constexpr bitfield_t<STATUS_t, 0x04, 2> HILVLEX = {};    //< High Level Interrupt Executing
        static constexpr bitfield_t<STATUS_t, 0x02, 1> MEDLVLEX = {};    //< Medium Level Interrupt Executing
        static constexpr bitfield_t<STATUS_t, 0x01, 0> LOLVLEX = {};    //< Low Level Interrupt Executing
    } STATUS = {};

    /// Interrupt Priority - 1 bytes
    static constexpr struct INTPRI_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<INTPRI_t, 0xFF, 0> INTPRI = {};    //< Interrupt Priority
    } INTPRI = {};

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<CTRL_t, 0x80, 7> RREN = {};    //< Round-Robin Priority Enable
        static constexpr bitfield_t<CTRL_t, 0x40, 6> IVSEL = {};    //< Interrupt Vector Select
        static constexpr bitfield_t<CTRL_t, 0x04, 2> HILVLEN = {};    //< High Level Enable
        static constexpr bitfield_t<CTRL_t, 0x02, 1> MEDLVLEN = {};    //< Medium Level Enable
        static constexpr bitfield_t<CTRL_t, 0x01, 0> LOLVLEN = {};    //< Low Level Enable
    } CTRL = {};

};

} // namespace device
