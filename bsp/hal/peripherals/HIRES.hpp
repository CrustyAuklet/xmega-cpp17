/**
 * XMEGAAU-HIRES (id I6090)
 * Timer/Counter High-Resolution Extension
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * HIRES
 * High-Resolution Extension
 * Size: 1 bytes
 */
template <addressType BASE_ADDRESS>
struct HIRES_t {

    // High Resolution Enable
    enum class HRENv : uint8_t {
        NONE = 0x00, // No Fault Protection
        TC0 = 0x01, // Enable High Resolution on Timer/Counter 0
        TC1 = 0x02, // Enable High Resolution on Timer/Counter 1
        BOTH = 0x03, // Enable High Resolution both Timer/Counters
    };


    /// Control Register - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using HRPLUS = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< High Resolution Plus
        using HREN = reg_field_t<BASE_ADDRESS + 0x0000, 0x03, 0, HRENv>;    //< High Resolution Enable
    };
};

} // namespace device
