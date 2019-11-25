/**
 * XMEGAAU-FUSE (id I6570)
 * Fuses and Lockbits
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * NVM_FUSES
 * Fuses
 * Size: 6 bytes
 */
template <addressType BASE_ADDRESS>
struct NVM_FUSES_t {

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


    /// JTAG User ID - 1 bytes
    struct FUSEBYTE0 : public reg8_t<BASE_ADDRESS + 0x0000> {
        using JTAGUSERID = reg_field_t<BASE_ADDRESS + 0x0000, 0xFF, 0>;    //< JTAG User ID
    };

    /// Watchdog Configuration - 1 bytes
    struct FUSEBYTE1 : public reg8_t<BASE_ADDRESS + 0x0001> {
        using WDWP = reg_field_t<BASE_ADDRESS + 0x0001, 0xF0, 4, WDv>;    //< Watchdog Window Timeout Period
        using WDP = reg_field_t<BASE_ADDRESS + 0x0001, 0x0F, 0, WDPv>;    //< Watchdog Timeout Period
    };

    /// Reset Configuration - 1 bytes
    struct FUSEBYTE2 : public reg8_t<BASE_ADDRESS + 0x0002> {
        using BOOTRST = reg_field_t<BASE_ADDRESS + 0x0002, 0x40, 6, BOOTRSTv>;    //< Boot Loader Section Reset Vector
        using TOSCSEL = reg_field_t<BASE_ADDRESS + 0x0002, 0x20, 5, TOSCSELv>;    //< Timer Oscillator pin location
        using BODPD = reg_field_t<BASE_ADDRESS + 0x0002, 0x03, 0, BODv>;    //< BOD Operation in Power-Down Mode
    };

    /// Start-up Configuration - 1 bytes
    struct FUSEBYTE4 : public reg8_t<BASE_ADDRESS + 0x0004> {
        using RSTDISBL = reg_field_t<BASE_ADDRESS + 0x0004, 0x10, 4>;    //< External Reset Disable
        using SUT = reg_field_t<BASE_ADDRESS + 0x0004, 0x0C, 2, SUTv>;    //< Start-up Time
        using WDLOCK = reg_field_t<BASE_ADDRESS + 0x0004, 0x02, 1>;    //< Watchdog Timer Lock
        using JTAGEN = reg_field_t<BASE_ADDRESS + 0x0004, 0x01, 0>;    //< JTAG Interface Enable
    };

    /// EESAVE and BOD Level - 1 bytes
    struct FUSEBYTE5 : public reg8_t<BASE_ADDRESS + 0x0005> {
        using BODACT = reg_field_t<BASE_ADDRESS + 0x0005, 0x30, 4, BODACTv>;    //< BOD Operation in Active Mode
        using EESAVE = reg_field_t<BASE_ADDRESS + 0x0005, 0x08, 3>;    //< Preserve EEPROM Through Chip Erase
        using BODLVL = reg_field_t<BASE_ADDRESS + 0x0005, 0x07, 0, BODLVLv>;    //< Brownout Detection Voltage Level
    };
};

} // namespace device
