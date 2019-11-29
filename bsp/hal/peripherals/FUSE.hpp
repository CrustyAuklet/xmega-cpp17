/**
 * XMEGAAU-FUSE (id I6570)
 * Fuses and Lockbits
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace FUSE {

    // Boot Loader Section Reset Vector
    enum class BOOTRSTv : uint8_t {
        BOOTLDR = 0x00, // Boot Loader Reset
        APPLICATION = 0x01, // Application Reset
    };
    // Timer Oscillator pin location
    enum class TOSCSELv : uint8_t {
        ALTERNATE = 0x00, // TOSC1 / TOSC2 on separate pins
        XTAL = 0x01, // TOSC1 / TOSC2 shared with XTAL1 / XTAL2
    };
    // BOD operation
    enum class BODv : uint8_t {
        SAMPLED = 0x01, // BOD enabled in sampled mode
        CONTINUOUS = 0x02, // BOD enabled continuously
        DISABLED = 0x03, // BOD Disabled
    };
    // BOD operation
    enum class BODACTv : uint8_t {
        SAMPLED = 0x01, // BOD enabled in sampled mode
        CONTINUOUS = 0x02, // BOD enabled continuously
        DISABLED = 0x03, // BOD Disabled
    };
    // Watchdog (Window) Timeout Period
    enum class WDv : uint8_t {
        _8CLK = 0x00, // 8 cycles (8ms @ 3.3V)
        _16CLK = 0x01, // 16 cycles (16ms @ 3.3V)
        _32CLK = 0x02, // 32 cycles (32ms @ 3.3V)
        _64CLK = 0x03, // 64 cycles (64ms @ 3.3V)
        _128CLK = 0x04, // 128 cycles (0.125s @ 3.3V)
        _256CLK = 0x05, // 256 cycles (0.25s @ 3.3V)
        _512CLK = 0x06, // 512 cycles (0.5s @ 3.3V)
        _1KCLK = 0x07, // 1K cycles (1s @ 3.3V)
        _2KCLK = 0x08, // 2K cycles (2s @ 3.3V)
        _4KCLK = 0x09, // 4K cycles (4s @ 3.3V)
        _8KCLK = 0x0A, // 8K cycles (8s @ 3.3V)
    };
    // Watchdog (Window) Timeout Period
    enum class WDPv : uint8_t {
        _8CLK = 0x00, // 8 cycles (8ms @ 3.3V)
        _16CLK = 0x01, // 16 cycles (16ms @ 3.3V)
        _32CLK = 0x02, // 32 cycles (32ms @ 3.3V)
        _64CLK = 0x03, // 64 cycles (64ms @ 3.3V)
        _128CLK = 0x04, // 128 cycles (0.125s @ 3.3V)
        _256CLK = 0x05, // 256 cycles (0.25s @ 3.3V)
        _512CLK = 0x06, // 512 cycles (0.5s @ 3.3V)
        _1KCLK = 0x07, // 1K cycles (1s @ 3.3V)
        _2KCLK = 0x08, // 2K cycles (2s @ 3.3V)
        _4KCLK = 0x09, // 4K cycles (4s @ 3.3V)
        _8KCLK = 0x0A, // 8K cycles (8s @ 3.3V)
    };
    // Start-up Time
    enum class SUTv : uint8_t {
        _0MS = 0x03, // 0 ms
        _4MS = 0x01, // 4 ms
        _64MS = 0x00, // 64 ms
    };
    // Brownout Detection Voltage Level
    enum class BODLVLv : uint8_t {
        _1V6 = 0x07, // 1.6 V
        _1V8 = 0x06, // 1.8 V
        _2V0 = 0x05, // 2.0 V
        _2V2 = 0x04, // 2.2 V
        _2V4 = 0x03, // 2.4 V
        _2V6 = 0x02, // 2.6 V
        _2V8 = 0x01, // 2.8 V
        _3V0 = 0x00, // 3.0 V
    };
}   // namespace FUSE

/**
 * NVM_FUSES
 * Fuses
 * Size: 6 bytes
 */
template <addressType BASE_ADDRESS>
struct NVM_FUSES_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// JTAG User ID - 1 bytes
    static constexpr struct FUSEBYTE0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<FUSEBYTE0_t, 7, 0> JTAGUSERID = {};    //< JTAG User ID
    } FUSEBYTE0 = {};

    /// Watchdog Configuration - 1 bytes
    static constexpr struct FUSEBYTE1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<FUSEBYTE1_t, 7, 4, FUSE::WDv> WDWP = {};    //< Watchdog Window Timeout Period
        static constexpr bitfield_t<FUSEBYTE1_t, 3, 0, FUSE::WDPv> WDP = {};    //< Watchdog Timeout Period
    } FUSEBYTE1 = {};

    /// Reset Configuration - 1 bytes
    static constexpr struct FUSEBYTE2_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<FUSEBYTE2_t, 6, 6, bool> BOOTRST = {};    //< Boot Loader Section Reset Vector
        static constexpr bitfield_t<FUSEBYTE2_t, 5, 5, bool> TOSCSEL = {};    //< Timer Oscillator pin location
        static constexpr bitfield_t<FUSEBYTE2_t, 1, 0, FUSE::BODv> BODPD = {};    //< BOD Operation in Power-Down Mode
    } FUSEBYTE2 = {};

    /// Start-up Configuration - 1 bytes
    static constexpr struct FUSEBYTE4_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<FUSEBYTE4_t, 4, 4, bool> RSTDISBL = {};    //< External Reset Disable
        static constexpr bitfield_t<FUSEBYTE4_t, 3, 2, FUSE::SUTv> SUT = {};    //< Start-up Time
        static constexpr bitfield_t<FUSEBYTE4_t, 1, 1, bool> WDLOCK = {};    //< Watchdog Timer Lock
        static constexpr bitfield_t<FUSEBYTE4_t, 0, 0, bool> JTAGEN = {};    //< JTAG Interface Enable
    } FUSEBYTE4 = {};

    /// EESAVE and BOD Level - 1 bytes
    static constexpr struct FUSEBYTE5_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
        static constexpr bitfield_t<FUSEBYTE5_t, 5, 4, FUSE::BODACTv> BODACT = {};    //< BOD Operation in Active Mode
        static constexpr bitfield_t<FUSEBYTE5_t, 3, 3, bool> EESAVE = {};    //< Preserve EEPROM Through Chip Erase
        static constexpr bitfield_t<FUSEBYTE5_t, 2, 0, FUSE::BODLVLv> BODLVL = {};    //< Brownout Detection Voltage Level
    } FUSEBYTE5 = {};

};

} // namespace sfr
