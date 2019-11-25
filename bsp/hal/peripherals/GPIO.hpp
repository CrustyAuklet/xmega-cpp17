/**
 * None-GPIO (id I6085)
 * General Purpose IO
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * GPIO
 * General Purpose IO Registers
 * Size: 16 bytes
 */
template <addressType BASE_ADDRESS>
struct GPIO_t {


    /// General Purpose IO Register 0 - 1 bytes
    struct GPIOR0 : public reg8_t<BASE_ADDRESS + 0x0000> {
    };

    /// General Purpose IO Register 1 - 1 bytes
    struct GPIOR1 : public reg8_t<BASE_ADDRESS + 0x0001> {
    };

    /// General Purpose IO Register 2 - 1 bytes
    struct GPIOR2 : public reg8_t<BASE_ADDRESS + 0x0002> {
    };

    /// General Purpose IO Register 3 - 1 bytes
    struct GPIOR3 : public reg8_t<BASE_ADDRESS + 0x0003> {
    };

    /// General Purpose IO Register 4 - 1 bytes
    struct GPIOR4 : public reg8_t<BASE_ADDRESS + 0x0004> {
    };

    /// General Purpose IO Register 5 - 1 bytes
    struct GPIOR5 : public reg8_t<BASE_ADDRESS + 0x0005> {
    };

    /// General Purpose IO Register 6 - 1 bytes
    struct GPIOR6 : public reg8_t<BASE_ADDRESS + 0x0006> {
    };

    /// General Purpose IO Register 7 - 1 bytes
    struct GPIOR7 : public reg8_t<BASE_ADDRESS + 0x0007> {
    };

    /// General Purpose IO Register 8 - 1 bytes
    struct GPIOR8 : public reg8_t<BASE_ADDRESS + 0x0008> {
    };

    /// General Purpose IO Register 9 - 1 bytes
    struct GPIOR9 : public reg8_t<BASE_ADDRESS + 0x0009> {
    };

    /// General Purpose IO Register 10 - 1 bytes
    struct GPIORA : public reg8_t<BASE_ADDRESS + 0x000A> {
    };

    /// General Purpose IO Register 11 - 1 bytes
    struct GPIORB : public reg8_t<BASE_ADDRESS + 0x000B> {
    };

    /// General Purpose IO Register 12 - 1 bytes
    struct GPIORC : public reg8_t<BASE_ADDRESS + 0x000C> {
    };

    /// General Purpose IO Register 13 - 1 bytes
    struct GPIORD : public reg8_t<BASE_ADDRESS + 0x000D> {
    };

    /// General Purpose IO Register 14 - 1 bytes
    struct GPIORE : public reg8_t<BASE_ADDRESS + 0x000E> {
    };

    /// General Purpose IO Register 15 - 1 bytes
    struct GPIORF : public reg8_t<BASE_ADDRESS + 0x000F> {
    };
};

} // namespace device
