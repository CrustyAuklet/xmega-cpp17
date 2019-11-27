/**
 * XMEGAAU-CRC (id I6111)
 * Cyclic Redundancy Checker
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace CRC {

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

}   // namespace CRC

/**
 * CRC
 * Cyclic Redundancy Checker
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct CRC_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRL_t, 0xC0, 6, RESETv> RESET = {};    //< Reset
        static constexpr bitfield_t<CTRL_t, 0x20, 5> CRC32 = {};    //< CRC Mode
        static constexpr bitfield_t<CTRL_t, 0x0F, 0, SOURCEv> SOURCE = {};    //< Input Source
    } CTRL = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<STATUS_t, 0x02, 1> ZERO = {};    //< Zero detection
        static constexpr bitfield_t<STATUS_t, 0x01, 0> BUSY = {};    //< Busy
    } STATUS = {};

    /// Data Input - 1 bytes
    static constexpr struct DATAIN_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
    } DATAIN = {};

    /// Checksum byte 0 - 1 bytes
    static constexpr struct CHECKSUM0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
    } CHECKSUM0 = {};

    /// Checksum byte 1 - 1 bytes
    static constexpr struct CHECKSUM1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
    } CHECKSUM1 = {};

    /// Checksum byte 2 - 1 bytes
    static constexpr struct CHECKSUM2_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
    } CHECKSUM2 = {};

    /// Checksum byte 3 - 1 bytes
    static constexpr struct CHECKSUM3_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
    } CHECKSUM3 = {};

};

} // namespace device
