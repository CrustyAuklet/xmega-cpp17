/**
 * None-PMIC (id I6057)
 * Programmable Multi-level Interrupt Controller
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

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
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<STATUS_t, 7, 7, bool> NMIEX = {};    //< Non-maskable Interrupt Executing
        static constexpr bitfield_t<STATUS_t, 2, 2, bool> HILVLEX = {};    //< High Level Interrupt Executing
        static constexpr bitfield_t<STATUS_t, 1, 1, bool> MEDLVLEX = {};    //< Medium Level Interrupt Executing
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> LOLVLEX = {};    //< Low Level Interrupt Executing
    } STATUS = {};

    /// Interrupt Priority - 1 bytes
    static constexpr struct INTPRI_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<INTPRI_t, 7, 0> INTPRI = {};    //< Interrupt Priority
    } INTPRI = {};

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<CTRL_t, 7, 7, bool> RREN = {};    //< Round-Robin Priority Enable
        static constexpr bitfield_t<CTRL_t, 6, 6, bool> IVSEL = {};    //< Interrupt Vector Select
        static constexpr bitfield_t<CTRL_t, 2, 2, bool> HILVLEN = {};    //< High Level Enable
        static constexpr bitfield_t<CTRL_t, 1, 1, bool> MEDLVLEN = {};    //< Medium Level Enable
        static constexpr bitfield_t<CTRL_t, 0, 0, bool> LOLVLEN = {};    //< Low Level Enable
    } CTRL = {};

};

} // namespace sfr
