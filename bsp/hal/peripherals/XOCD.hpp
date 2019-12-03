/**
 * None-XOCD (id I6043)
 * On-Chip Debug System
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace XOCD {

}   // namespace XOCD

/**
 * OCD
 * On-Chip Debug System
 * Size: 2 bytes
 */
template <addressType BASE_ADDRESS>
struct OCD_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// OCD Register 0 - 1 bytes
    static constexpr struct OCDR0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<OCDR0_t, 7, 0> OCDRD = {};    //< OCDR Dirty
    } OCDR0 = {};

    /// OCD Register 1 - 1 bytes
    static constexpr struct OCDR1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<OCDR1_t, 0, 0, bool> OCDRD = {};    //< OCDR Dirty
    } OCDR1 = {};

};

} // namespace sfr
