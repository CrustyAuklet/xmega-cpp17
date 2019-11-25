/**
 * None-PMIC (id I6057)
 * Programmable Multi-level Interrupt Controller
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * PMIC
 * Programmable Multi-level Interrupt Controller
 * Size: 16 bytes
 */
template <addressType BASE_ADDRESS>
struct PMIC_t {


    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0000> {
        using NMIEX = reg_field_t<BASE_ADDRESS + 0x0000, 0x80, 7>;    //< Non-maskable Interrupt Executing
        using HILVLEX = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< High Level Interrupt Executing
        using MEDLVLEX = reg_field_t<BASE_ADDRESS + 0x0000, 0x02, 1>;    //< Medium Level Interrupt Executing
        using LOLVLEX = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Low Level Interrupt Executing
    };

    /// Interrupt Priority - 1 bytes
    struct INTPRI : public reg8_t<BASE_ADDRESS + 0x0001> {
        using INTPRIf = reg_field_t<BASE_ADDRESS + 0x0001, 0xFF, 0>;    //< Interrupt Priority
    };

    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0002> {
        using RREN = reg_field_t<BASE_ADDRESS + 0x0002, 0x80, 7>;    //< Round-Robin Priority Enable
        using IVSEL = reg_field_t<BASE_ADDRESS + 0x0002, 0x40, 6>;    //< Interrupt Vector Select
        using HILVLEN = reg_field_t<BASE_ADDRESS + 0x0002, 0x04, 2>;    //< High Level Enable
        using MEDLVLEN = reg_field_t<BASE_ADDRESS + 0x0002, 0x02, 1>;    //< Medium Level Enable
        using LOLVLEN = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Low Level Enable
    };
};

} // namespace device
