/**
 * XMEGAAU-IRCOM (id I6090)
 * IR Communication Module
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * IRCOM
 * IR Communication Module
 * Size: 3 bytes
 */
template <addressType BASE_ADDRESS>
struct IRCOM_t {

    // Event channel selection
    enum class EVSELv : uint8_t {
        OFF = 0x00, // No Event Source
        _0 = 0x08, // Event Channel 0
        _1 = 0x09, // Event Channel 1
        _2 = 0x0A, // Event Channel 2
        _3 = 0x0B, // Event Channel 3
        _4 = 0x0C, // Event Channel 4
        _5 = 0x0D, // Event Channel 5
        _6 = 0x0E, // Event Channel 6
        _7 = 0x0F, // Event Channel 7
    };


    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using EVSEL = reg_field_t<BASE_ADDRESS + 0x0000, 0x0F, 0, EVSELv>;    //< Event Channel Select
    };

    /// IrDA Transmitter Pulse Length Control Register - 1 bytes
    struct TXPLCTRL : public reg8_t<BASE_ADDRESS + 0x0001> {
    };

    /// IrDA Receiver Pulse Length Control Register - 1 bytes
    struct RXPLCTRL : public reg8_t<BASE_ADDRESS + 0x0002> {
    };
};

} // namespace device
