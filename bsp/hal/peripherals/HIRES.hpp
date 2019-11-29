/**
 * XMEGAAU-HIRES (id I6090)
 * Timer/Counter High-Resolution Extension
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace HIRES {

    // High Resolution Enable
    enum class HRENv : uint8_t {
        NONE = 0x00, // No Fault Protection
        TC0 = 0x01, // Enable High Resolution on Timer/Counter 0
        TC1 = 0x02, // Enable High Resolution on Timer/Counter 1
        BOTH = 0x03, // Enable High Resolution both Timer/Counters
    };
}   // namespace HIRES

/**
 * HIRES
 * High-Resolution Extension
 * Size: 1 bytes
 */
template <addressType BASE_ADDRESS>
struct HIRES_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRLA_t, 2, 2, bool> HRPLUS = {};    //< High Resolution Plus
        static constexpr bitfield_t<CTRLA_t, 1, 0, HIRES::HRENv> HREN = {};    //< High Resolution Enable
    } CTRLA = {};

};

} // namespace sfr
