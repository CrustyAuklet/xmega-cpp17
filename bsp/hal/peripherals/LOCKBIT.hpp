/**
 * XMEGAAU-LOCKBIT (id I6570)
 * Fuses and Lockbits
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * NVM_LOCKBITS
 * Lock Bits
 * Size: 1 bytes
 */
template <addressType BASE_ADDRESS>
struct NVM_LOCKBITS_t {

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


    /// Lock Bits - 1 bytes
    struct LOCKBITS : public reg8_t<BASE_ADDRESS + 0x0000> {
        using BLBB = reg_field_t<BASE_ADDRESS + 0x0000, 0xC0, 6, BLBBv>;    //< Boot Lock Bits - Boot Section
        using BLBA = reg_field_t<BASE_ADDRESS + 0x0000, 0x30, 4, BLBAv>;    //< Boot Lock Bits - Application Section
        using BLBAT = reg_field_t<BASE_ADDRESS + 0x0000, 0x0C, 2, BLBATv>;    //< Boot Lock Bits - Application Table
        using LB = reg_field_t<BASE_ADDRESS + 0x0000, 0x03, 0, LBv>;    //< Lock Bits
    };
};

} // namespace device
