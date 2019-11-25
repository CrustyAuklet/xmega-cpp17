/**
 * XMEGAAU-RST (id I6083)
 * Reset
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * RST
 * Reset
 * Size: 2 bytes
 */
template <addressType BASE_ADDRESS>
struct RST_t {


    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0000> {
        using SDRF = reg_field_t<BASE_ADDRESS + 0x0000, 0x40, 6>;    //< Spike Detection Reset Flag
        using SRF = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< Software Reset Flag
        using PDIRF = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Programming and Debug Interface Interface Reset Flag
        using WDRF = reg_field_t<BASE_ADDRESS + 0x0000, 0x08, 3>;    //< Watchdog Reset Flag
        using BORF = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< Brown-out Reset Flag
        using EXTRF = reg_field_t<BASE_ADDRESS + 0x0000, 0x02, 1>;    //< External Reset Flag
        using PORF = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Power-on Reset Flag
    };

    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0001> {
        using SWRST = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Software Reset
    };
};

} // namespace device
