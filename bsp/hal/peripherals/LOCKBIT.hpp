/**
 * XMEGAAU-LOCKBIT (id I6570)
 * Fuses and Lockbits
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace LOCKBIT {

    // Boot lock bits - boot setcion
    enum class BLBBv : uint8_t {
        RWLOCK = 0x00, // Read and write not allowed
        RLOCK = 0x01, // Read not allowed
        WLOCK = 0x02, // Write not allowed
        NOLOCK = 0x03, // No locks
    };

    // Boot lock bits - application section
    enum class BLBAv : uint8_t {
        RWLOCK = 0x00, // Read and write not allowed
        RLOCK = 0x01, // Read not allowed
        WLOCK = 0x02, // Write not allowed
        NOLOCK = 0x03, // No locks
    };

    // Boot lock bits - application table section
    enum class BLBATv : uint8_t {
        RWLOCK = 0x00, // Read and write not allowed
        RLOCK = 0x01, // Read not allowed
        WLOCK = 0x02, // Write not allowed
        NOLOCK = 0x03, // No locks
    };

    // Lock bits
    enum class LBv : uint8_t {
        RWLOCK = 0x00, // Read and write not allowed
        WLOCK = 0x02, // Write not allowed
        NOLOCK = 0x03, // No locks
    };

}   // namespace LOCKBIT

/**
 * NVM_LOCKBITS
 * Lock Bits
 * Size: 1 bytes
 */
template <addressType BASE_ADDRESS>
struct NVM_LOCKBITS_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Lock Bits - 1 bytes
    static constexpr struct LOCKBITS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<LOCKBITS_t, 0xC0, 6, BLBBv> BLBB = {};    //< Boot Lock Bits - Boot Section
        static constexpr bitfield_t<LOCKBITS_t, 0x30, 4, BLBAv> BLBA = {};    //< Boot Lock Bits - Application Section
        static constexpr bitfield_t<LOCKBITS_t, 0x0C, 2, BLBATv> BLBAT = {};    //< Boot Lock Bits - Application Table
        static constexpr bitfield_t<LOCKBITS_t, 0x03, 0, LBv> LB = {};    //< Lock Bits
    } LOCKBITS = {};

};

} // namespace device
