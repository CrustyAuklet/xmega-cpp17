/**
 * XMEGAAU-CRC (id I6111)
 * Cyclic Redundancy Checker
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * CRC
 * Cyclic Redundancy Checker
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct CRC_t {

    // Reset
    enum class RESETv : uint8_t {
        NO = 0x00, // No Reset
        RESET0 = 0x02, // Reset CRC with CHECKSUM to all zeros
        RESET1 = 0x03, // Reset CRC with CHECKSUM to all ones
    };

    // Input Source
    enum class SOURCEv : uint8_t {
        DISABLE = 0x00, // Disabled
        IO = 0x01, // I/O Interface
        FLASH = 0x02, // Flash
        DMAC0 = 0x04, // DMAC Channel 0
        DMAC1 = 0x05, // DMAC Channel 1
        DMAC2 = 0x06, // DMAC Channel 2
        DMAC3 = 0x07, // DMAC Channel 3
    };


    /// Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using RESET = reg_field_t<BASE_ADDRESS + 0x0000, 0xC0, 6, RESETv>;    //< Reset
        using CRC32 = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< CRC Mode
        using SOURCE = reg_field_t<BASE_ADDRESS + 0x0000, 0x0F, 0, SOURCEv>;    //< Input Source
    };

    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0001> {
        using ZERO = reg_field_t<BASE_ADDRESS + 0x0001, 0x02, 1>;    //< Zero detection
        using BUSY = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Busy
    };

    /// Data Input - 1 bytes
    struct DATAIN : public reg8_t<BASE_ADDRESS + 0x0003> {
    };

    /// Checksum byte 0 - 1 bytes
    struct CHECKSUM0 : public reg8_t<BASE_ADDRESS + 0x0004> {
    };

    /// Checksum byte 1 - 1 bytes
    struct CHECKSUM1 : public reg8_t<BASE_ADDRESS + 0x0005> {
    };

    /// Checksum byte 2 - 1 bytes
    struct CHECKSUM2 : public reg8_t<BASE_ADDRESS + 0x0006> {
    };

    /// Checksum byte 3 - 1 bytes
    struct CHECKSUM3 : public reg8_t<BASE_ADDRESS + 0x0007> {
    };
};

} // namespace device
