/**
 * XMEGAAU-TC2 (id I6090)
 * 16-bit Timer/Counter type 2
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * TC2
 * 16-bit Timer/Counter type 2
 * Size: 48 bytes
 */
template <addressType BASE_ADDRESS>
struct TC2_t {

    // Clock Selection
    enum class CLKSELv : uint8_t {
        OFF = 0x00, // Timer Off
        DIV1 = 0x01, // System Clock
        DIV2 = 0x02, // System Clock / 2
        DIV4 = 0x03, // System Clock / 4
        DIV8 = 0x04, // System Clock / 8
        DIV64 = 0x05, // System Clock / 64
        DIV256 = 0x06, // System Clock / 256
        DIV1024 = 0x07, // System Clock / 1024
        EVCH0 = 0x08, // Event Channel 0
        EVCH1 = 0x09, // Event Channel 1
        EVCH2 = 0x0A, // Event Channel 2
        EVCH3 = 0x0B, // Event Channel 3
        EVCH4 = 0x0C, // Event Channel 4
        EVCH5 = 0x0D, // Event Channel 5
        EVCH6 = 0x0E, // Event Channel 6
        EVCH7 = 0x0F, // Event Channel 7
    };

    // Byte Mode
    enum class BYTEMv : uint8_t {
        NORMAL = 0x00, // 16-bit mode
        BYTEMODE = 0x01, // Timer/Counter operating in byte mode only (TC2)
        SPLITMODE = 0x02, // Timer/Counter split into two 8-bit Counters
    };

    // High Byte Underflow Interrupt Level
    enum class HUNFINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Low Byte Underflow Interrupt Level
    enum class LUNFINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Low Byte Compare D Interrupt Level
    enum class LCMPDINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Low Byte Compare C Interrupt Level
    enum class LCMPCINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Low Byte Compare B Interrupt Level
    enum class LCMPBINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Low Byte Compare A Interrupt Level
    enum class LCMPAINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Timer/Counter Command
    enum class CMDv : uint8_t {
        NONE = 0x00, // No Command
        RESTART = 0x02, // Force Restart
        RESET = 0x03, // Force Hard Reset
    };

    // Timer/Counter Command
    enum class CMDENv : uint8_t {
        LOW = 0x01, // Low Byte Timer/Counter
        HIGH = 0x02, // High Byte Timer/Counter
        BOTH = 0x03, // Both Low Byte and High Byte Timer/Counters
    };

    // TC2 ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        LUNF = 0, // Low Byte Underflow Interrupt
        HUNF = 1, // High Byte Underflow Interrupt
        LCMPA = 2, // Low Byte Compare A Interrupt
        LCMPB = 3, // Low Byte Compare B Interrupt
        LCMPC = 4, // Low Byte Compare C Interrupt
        LCMPD = 5, // Low Byte Compare D Interrupt
    };

    /// Control Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using CLKSEL = reg_field_t<BASE_ADDRESS + 0x0000, 0x0F, 0, CLKSELv>;    //< Clock Selection
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0001> {
        using HCMPDEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x80, 7>;    //< High Byte Compare D Enable
        using HCMPCEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x40, 6>;    //< High Byte Compare C Enable
        using HCMPBEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x20, 5>;    //< High Byte Compare B Enable
        using HCMPAEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x10, 4>;    //< High Byte Compare A Enable
        using LCMPDEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x08, 3>;    //< Low Byte Compare D Enable
        using LCMPCEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x04, 2>;    //< Low Byte Compare C Enable
        using LCMPBEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x02, 1>;    //< Low Byte Compare B Enable
        using LCMPAEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Low Byte Compare A Enable
    };

    /// Control register C - 1 bytes
    struct CTRLC : public reg8_t<BASE_ADDRESS + 0x0002> {
        using HCMPD = reg_field_t<BASE_ADDRESS + 0x0002, 0x80, 7>;    //< High Byte Compare D Output Value
        using HCMPC = reg_field_t<BASE_ADDRESS + 0x0002, 0x40, 6>;    //< High Byte Compare C Output Value
        using HCMPB = reg_field_t<BASE_ADDRESS + 0x0002, 0x20, 5>;    //< High Byte Compare B Output Value
        using HCMPA = reg_field_t<BASE_ADDRESS + 0x0002, 0x10, 4>;    //< High Byte Compare A Output Value
        using LCMPD = reg_field_t<BASE_ADDRESS + 0x0002, 0x08, 3>;    //< Low Byte Compare D Output Value
        using LCMPC = reg_field_t<BASE_ADDRESS + 0x0002, 0x04, 2>;    //< Low Byte Compare C Output Value
        using LCMPB = reg_field_t<BASE_ADDRESS + 0x0002, 0x02, 1>;    //< Low Byte Compare B Output Value
        using LCMPA = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Low Byte Compare A Output Value
    };

    /// Control Register E - 1 bytes
    struct CTRLE : public reg8_t<BASE_ADDRESS + 0x0004> {
        using BYTEM = reg_field_t<BASE_ADDRESS + 0x0004, 0x03, 0, BYTEMv>;    //< Byte Mode
    };

    /// Interrupt Control Register A - 1 bytes
    struct INTCTRLA : public reg8_t<BASE_ADDRESS + 0x0006> {
        using HUNFINTLVL = reg_field_t<BASE_ADDRESS + 0x0006, 0x0C, 2, HUNFINTLVLv>;    //< High Byte Underflow Interrupt Level
        using LUNFINTLVL = reg_field_t<BASE_ADDRESS + 0x0006, 0x03, 0, LUNFINTLVLv>;    //< Low Byte Underflow interrupt level
    };

    /// Interrupt Control Register B - 1 bytes
    struct INTCTRLB : public reg8_t<BASE_ADDRESS + 0x0007> {
        using LCMPDINTLVL = reg_field_t<BASE_ADDRESS + 0x0007, 0xC0, 6, LCMPDINTLVLv>;    //< Low Byte Compare D Interrupt Level
        using LCMPCINTLVL = reg_field_t<BASE_ADDRESS + 0x0007, 0x30, 4, LCMPCINTLVLv>;    //< Low Byte Compare C Interrupt Level
        using LCMPBINTLVL = reg_field_t<BASE_ADDRESS + 0x0007, 0x0C, 2, LCMPBINTLVLv>;    //< Low Byte Compare B Interrupt Level
        using LCMPAINTLVL = reg_field_t<BASE_ADDRESS + 0x0007, 0x03, 0, LCMPAINTLVLv>;    //< Low Byte Compare A Interrupt Level
    };

    /// Control Register F - 1 bytes
    struct CTRLF : public reg8_t<BASE_ADDRESS + 0x0009> {
        using CMD = reg_field_t<BASE_ADDRESS + 0x0009, 0x0C, 2, CMDv>;    //< Command
        using CMDEN = reg_field_t<BASE_ADDRESS + 0x0009, 0x03, 0, CMDENv>;    //< Command Enable
    };

    /// Interrupt Flag Register - 1 bytes
    struct INTFLAGS : public reg8_t<BASE_ADDRESS + 0x000C> {
        using LCMPDIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x80, 7>;    //< Low Byte Compare D Interrupt Flag
        using LCMPCIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x40, 6>;    //< Low Byte Compare C Interrupt Flag
        using LCMPBIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x20, 5>;    //< Low Byte Compare B Interrupt Flag
        using LCMPAIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x10, 4>;    //< Low Byte Compare A Interrupt Flag
        using HUNFIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x02, 1>;    //< High Byte Underflow Interrupt Flag
        using LUNFIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x01, 0>;    //< Low Byte Underflow Interrupt Flag
    };

    /// Low Byte Count - 1 bytes
    struct LCNT : public reg8_t<BASE_ADDRESS + 0x0020> {
    };

    /// High Byte Count - 1 bytes
    struct HCNT : public reg8_t<BASE_ADDRESS + 0x0021> {
    };

    /// Low Byte Period - 1 bytes
    struct LPER : public reg8_t<BASE_ADDRESS + 0x0026> {
    };

    /// High Byte Period - 1 bytes
    struct HPER : public reg8_t<BASE_ADDRESS + 0x0027> {
    };

    /// Low Byte Compare A - 1 bytes
    struct LCMPA : public reg8_t<BASE_ADDRESS + 0x0028> {
    };

    /// High Byte Compare A - 1 bytes
    struct HCMPA : public reg8_t<BASE_ADDRESS + 0x0029> {
    };

    /// Low Byte Compare B - 1 bytes
    struct LCMPB : public reg8_t<BASE_ADDRESS + 0x002A> {
    };

    /// High Byte Compare B - 1 bytes
    struct HCMPB : public reg8_t<BASE_ADDRESS + 0x002B> {
    };

    /// Low Byte Compare C - 1 bytes
    struct LCMPC : public reg8_t<BASE_ADDRESS + 0x002C> {
    };

    /// High Byte Compare C - 1 bytes
    struct HCMPC : public reg8_t<BASE_ADDRESS + 0x002D> {
    };

    /// Low Byte Compare D - 1 bytes
    struct LCMPD : public reg8_t<BASE_ADDRESS + 0x002E> {
    };

    /// High Byte Compare D - 1 bytes
    struct HCMPD : public reg8_t<BASE_ADDRESS + 0x002F> {
    };
};

} // namespace device
