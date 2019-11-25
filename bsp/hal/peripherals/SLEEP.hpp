/**
 * XMEGAAU-SLEEP (id I6081)
 * Sleep Controller
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * SLEEP
 * Sleep Controller
 * Size: 1 bytes
 */
template <addressType BASE_ADDRESS>
struct SLEEP_t {

    // Sleep Mode
    enum class SMODEv : uint8_t {
        IDLE = 0x00, // Idle mode
        PDOWN = 0x02, // Power-down Mode
        PSAVE = 0x03, // Power-save Mode
        STDBY = 0x06, // Standby Mode
        ESTDBY = 0x07, // Extended Standby Mode
    };


    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using SMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x0E, 1, SMODEv>;    //< Sleep Mode
        using SEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Sleep Enable
    };
};

} // namespace device
