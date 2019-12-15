/**
 * XMEGAAU-SLEEP (id I6081)
 * Sleep Controller
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace SLEEP {

    // Sleep Mode
    enum class SMODEv : uint8_t {
        IDLE = 0x00, // Idle mode
        PDOWN = 0x02, // Power-down Mode
        PSAVE = 0x03, // Power-save Mode
        STDBY = 0x06, // Standby Mode
        ESTDBY = 0x07, // Extended Standby Mode
    };
}   // namespace SLEEP

/**
 * SLEEP
 * Sleep Controller
 * Size: 1 bytes
 */
template <addressType BASE_ADDRESS>
struct SLEEP_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRL_t, 3, 1, SLEEP::SMODEv> SMODE = {};    //< Sleep Mode
        static constexpr bitfield_t<CTRL_t, 0, 0, bool> SEN = {};    //< Sleep Enable
    } CTRL = {};

};

} // namespace sfr
