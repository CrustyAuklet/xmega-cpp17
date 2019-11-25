/**
 * XMEGAAU-VPORT (id I6075)
 * Virtual Ports
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * VPORT
 * Virtual Port
 * Size: 4 bytes
 */
template <addressType BASE_ADDRESS>
struct VPORT_t {


    /// I/O Port Data Direction - 1 bytes
    struct DIR : public reg8_t<BASE_ADDRESS + 0x0000> {
    };

    /// I/O Port Output - 1 bytes
    struct OUT : public reg8_t<BASE_ADDRESS + 0x0001> {
    };

    /// I/O Port Input - 1 bytes
    struct IN : public reg8_t<BASE_ADDRESS + 0x0002> {
    };

    /// Interrupt Flag Register - 1 bytes
    struct INTFLAGS : public reg8_t<BASE_ADDRESS + 0x0003> {
        using INT1IF = reg_field_t<BASE_ADDRESS + 0x0003, 0x02, 1>;    //< Port Interrupt 1 Flag
        using INT0IF = reg_field_t<BASE_ADDRESS + 0x0003, 0x01, 0>;    //< Port Interrupt 0 Flag
    };
};

} // namespace device
