/**
 * XMEGAAU-CRC (id I6111)
 * Cyclic Redundancy Checker
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

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
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRL_t, 7, 6, CRC::RESETv> RESET = {};    //< Reset
        static constexpr bitfield_t<CTRL_t, 5, 5, bool> CRC32 = {};    //< CRC Mode
        static constexpr bitfield_t<CTRL_t, 3, 0, CRC::SOURCEv> SOURCE = {};    //< Input Source
    } CTRL = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<STATUS_t, 1, 1, bool> ZERO = {};    //< Zero detection
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> BUSY = {};    //< Busy
    } STATUS = {};

    /// Data Input - 1 bytes
    static constexpr struct DATAIN_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
    } DATAIN = {};

    /// Checksum byte 0 - 1 bytes
    static constexpr struct CHECKSUM0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
    } CHECKSUM0 = {};

    /// Checksum byte 1 - 1 bytes
    static constexpr struct CHECKSUM1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
    } CHECKSUM1 = {};

    /// Checksum byte 2 - 1 bytes
    static constexpr struct CHECKSUM2_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
    } CHECKSUM2 = {};

    /// Checksum byte 3 - 1 bytes
    static constexpr struct CHECKSUM3_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0007>::operator=;
    } CHECKSUM3 = {};

};

} // namespace sfr
