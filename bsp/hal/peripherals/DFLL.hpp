/**
 * XMEGAAU-DFLL (id I6055)
 * DFLL
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * DFLL
 * DFLL
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct DFLL_t {


    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< DFLL Enable
    };

    /// Calibration Register A - 1 bytes
    struct CALA : public reg8_t<BASE_ADDRESS + 0x0002> {
        using CALL = reg_field_t<BASE_ADDRESS + 0x0002, 0x7F, 0>;    //< DFLL Calibration Value A
    };

    /// Calibration Register B - 1 bytes
    struct CALB : public reg8_t<BASE_ADDRESS + 0x0003> {
        using CALH = reg_field_t<BASE_ADDRESS + 0x0003, 0x3F, 0>;    //< DFLL Calibration Value B
    };

    /// Oscillator Compare Register 0 - 1 bytes
    struct COMP0 : public reg8_t<BASE_ADDRESS + 0x0004> {
    };

    /// Oscillator Compare Register 1 - 1 bytes
    struct COMP1 : public reg8_t<BASE_ADDRESS + 0x0005> {
    };

    /// Oscillator Compare Register 2 - 1 bytes
    struct COMP2 : public reg8_t<BASE_ADDRESS + 0x0006> {
    };
};

} // namespace device
