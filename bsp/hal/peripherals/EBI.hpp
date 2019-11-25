/**
 * None-EBI (id I3001)
 * External Bus Interface
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * EBI_CS
 * EBI Chip Select Module
 * Size: 4 bytes
 */
template <addressType BASE_ADDRESS>
struct EBI_CS_t {
    // Chip Select adress size
    enum class CS_ASIZEv : uint8_t {
        _256B = 0x00, // 256 bytes
        _512B = 0x01, // 512 bytes
        _1KB = 0x02, // 1K bytes
        _2KB = 0x03, // 2K bytes
        _4KB = 0x04, // 4K bytes
        _8KB = 0x05, // 8K bytes
        _16KB = 0x06, // 16K bytes
        _32KB = 0x07, // 32K bytes
        _64KB = 0x08, // 64K bytes
        _128KB = 0x09, // 128K bytes
        _256KB = 0x0A, // 256K bytes
        _512KB = 0x0B, // 512K bytes
        _1MB = 0x0C, // 1M bytes
        _2MB = 0x0D, // 2M bytes
        _4MB = 0x0E, // 4M bytes
        _8MB = 0x0F, // 8M bytes
        _16M = 0x10, // 16M bytes
    };

    // Legacy: Chip Select adress space
    enum class CS_ASPACEv : uint8_t {
        _256B = 0x00, // 256 bytes
        _512B = 0x01, // 512 bytes
        _1KB = 0x02, // 1K bytes
        _2KB = 0x03, // 2K bytes
        _4KB = 0x04, // 4K bytes
        _8KB = 0x05, // 8K bytes
        _16KB = 0x06, // 16K bytes
        _32KB = 0x07, // 32K bytes
        _64KB = 0x08, // 64K bytes
        _128KB = 0x09, // 128K bytes
        _256KB = 0x0A, // 256K bytes
        _512KB = 0x0B, // 512K bytes
        _1MB = 0x0C, // 1M bytes
        _2MB = 0x0D, // 2M bytes
        _4MB = 0x0E, // 4M bytes
        _8MB = 0x0F, // 8M bytes
        _16M = 0x10, // 16M bytes
    };

    // SRAM Wait State Selection
    enum class CS_SRWSv : uint8_t {
        _0CLK = 0x00, // 0 cycles
        _1CLK = 0x01, // 1 cycle
        _2CLK = 0x02, // 2 cycles
        _3CLK = 0x03, // 3 cycles
        _4CLK = 0x04, // 4 cycles
        _5CLK = 0x05, // 5 cycles
        _6CLK = 0x06, // 6 cycles
        _7CLK = 0x07, // 7 cycles
    };

    // Chip Select address mode
    enum class CS_MODEv : uint8_t {
        DISABLED = 0x00, // Chip Select Disabled
        SRAM = 0x01, // Chip Select in SRAM mode
        LPC = 0x02, // Chip Select in SRAM LPC mode
        SDRAM = 0x03, // Chip Select in SDRAM mode
    };

    // Chip Select SDRAM mode
    enum class CS_SDMODEv : uint8_t {
        NORMAL = 0x00, // Normal mode
        LOAD = 0x01, // Load Mode Register command mode
    };

    /// Chip Select Control Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using ASIZE = reg_field_t<BASE_ADDRESS + 0x0000, 0x7C, 2, CS_ASIZEv>;    //< Address Size
        using ASPACE = reg_field_t<BASE_ADDRESS + 0x0000, 0x7C, 2, CS_ASPACEv>;    //< Legacy name: Address Space
        using MODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x03, 0, CS_MODEv>;    //< Memory Mode
    };

    /// Chip Select Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0001> {
        using SRWS = reg_field_t<BASE_ADDRESS + 0x0001, 0x07, 0, CS_SRWSv>;    //< SRAM Wait State Cycles
        using SDINITDONE = reg_field_t<BASE_ADDRESS + 0x0001, 0x80, 7>;    //< SDRAM Initialization Done
        using SDSREN = reg_field_t<BASE_ADDRESS + 0x0001, 0x04, 2>;    //< SDRAM Self-refresh Enable
        using SDMODE = reg_field_t<BASE_ADDRESS + 0x0001, 0x03, 0, CS_SDMODEv>;    //< SDRAM Mode
    };

    /// Chip Select Base Address - 2 bytes
    struct BASEADDR : public reg16_t<BASE_ADDRESS + 0x0002> {
    };
};

/**
 * EBI
 * External Bus Interface
 * Size: 32 bytes
 */
template <addressType BASE_ADDRESS>
struct EBI_t {
    //
    enum class SDDATAWv : uint8_t {
        _4BIT = 0x00, // 4-bit data bus
        _8BIT = 0x01, // 8-bit data bus
    };

    //
    enum class LPCMODEv : uint8_t {
        ALE1 = 0x00, // Data muxed with addr byte 0
        ALE12 = 0x02, // Data muxed with addr byte 0 and 1
    };

    //
    enum class SRMODEv : uint8_t {
        ALE1 = 0x00, // Addr byte 0 muxed with 1
        ALE2 = 0x01, // Addr byte 0 muxed with 2
        ALE12 = 0x02, // Addr byte 0 muxed with 1 and 2
        NOALE = 0x03, // No addr muxing
    };

    //
    enum class IFMODEv : uint8_t {
        DISABLED = 0x00, // EBI Disabled
        _3PORT = 0x01, // 3-port mode
        _4PORT = 0x02, // 4-port mode
        _2PORT = 0x03, // 2-port mode
    };

    //
    enum class SDCOLv : uint8_t {
        _8BIT = 0x00, // 8 column bits
        _9BIT = 0x01, // 9 column bits
        _10BIT = 0x02, // 10 column bits
        _11BIT = 0x03, // 11 column bits
    };

    // SDRAM Load Mode to Active delay
    enum class MRDLYv : uint8_t {
        _0CLK = 0x00, // 0 cycles
        _1CLK = 0x01, // 1 cycle
        _2CLK = 0x02, // 2 cycles
        _3CLK = 0x03, // 3 cycles
    };

    // SDRAM Row Cycle Delay
    enum class ROWCYCDLYv : uint8_t {
        _0CLK = 0x00, // 0 cycles
        _1CLK = 0x01, // 1 cycle
        _2CLK = 0x02, // 2 cycles
        _3CLK = 0x03, // 3 cycles
        _4CLK = 0x04, // 4 cycles
        _5CLK = 0x05, // 5 cycles
        _6CLK = 0x06, // 6 cycles
        _7CLK = 0x07, // 7 cycles
    };

    // SDRAM Row to Precharge Delay
    enum class RPDLYv : uint8_t {
        _0CLK = 0x00, // 0 cycles
        _1CLK = 0x01, // 1 cycle
        _2CLK = 0x02, // 2 cycles
        _3CLK = 0x03, // 3 cycles
        _4CLK = 0x04, // 4 cycles
        _5CLK = 0x05, // 5 cycles
        _6CLK = 0x06, // 6 cycles
        _7CLK = 0x07, // 7 cycles
    };

    // SDRAM Write Recovery Delay
    enum class WRDLYv : uint8_t {
        _0CLK = 0x00, // 0 cycles
        _1CLK = 0x01, // 1 cycle
        _2CLK = 0x02, // 2 cycles
        _3CLK = 0x03, // 3 cycles
    };

    // SDRAM Exit Self Refresh to Active Delay
    enum class ESRDLYv : uint8_t {
        _0CLK = 0x00, // 0 cycles
        _1CLK = 0x01, // 1 cycle
        _2CLK = 0x02, // 2 cycles
        _3CLK = 0x03, // 3 cycles
        _4CLK = 0x04, // 4 cycles
        _5CLK = 0x05, // 5 cycles
        _6CLK = 0x06, // 6 cycles
        _7CLK = 0x07, // 7 cycles
    };

    // SDRAM Row to Column Delay
    enum class ROWCOLDLYv : uint8_t {
        _0CLK = 0x00, // 0 cycles
        _1CLK = 0x01, // 1 cycle
        _2CLK = 0x02, // 2 cycles
        _3CLK = 0x03, // 3 cycles
        _4CLK = 0x04, // 4 cycles
        _5CLK = 0x05, // 5 cycles
        _6CLK = 0x06, // 6 cycles
        _7CLK = 0x07, // 7 cycles
    };


    /// Control - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using SDDATAW = reg_field_t<BASE_ADDRESS + 0x0000, 0xC0, 6, SDDATAWv>;    //< SDRAM Data Width Setting
        using LPCMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x30, 4, LPCMODEv>;    //< SRAM LPC Mode
        using SRMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x0C, 2, SRMODEv>;    //< SRAM Mode
        using IFMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x03, 0, IFMODEv>;    //< Interface Mode
    };

    /// SDRAM Control Register A - 1 bytes
    struct SDRAMCTRLA : public reg8_t<BASE_ADDRESS + 0x0001> {
        using SDCAS = reg_field_t<BASE_ADDRESS + 0x0001, 0x08, 3>;    //< SDRAM CAS Latency Setting
        using SDROW = reg_field_t<BASE_ADDRESS + 0x0001, 0x04, 2>;    //< SDRAM ROW Bits Setting
        using SDCOL = reg_field_t<BASE_ADDRESS + 0x0001, 0x03, 0, SDCOLv>;    //< SDRAM Column Bits Setting
    };

    /// SDRAM Refresh Period - 2 bytes
    struct REFRESH : public reg16_t<BASE_ADDRESS + 0x0004> {
    };

    /// SDRAM Initialization Delay - 2 bytes
    struct INITDLY : public reg16_t<BASE_ADDRESS + 0x0006> {
    };

    /// SDRAM Control Register B - 1 bytes
    struct SDRAMCTRLB : public reg8_t<BASE_ADDRESS + 0x0008> {
        using MRDLY = reg_field_t<BASE_ADDRESS + 0x0008, 0xC0, 6, MRDLYv>;    //< SDRAM Mode Register Delay
        using ROWCYCDLY = reg_field_t<BASE_ADDRESS + 0x0008, 0x38, 3, ROWCYCDLYv>;    //< SDRAM Row Cycle Delay
        using RPDLY = reg_field_t<BASE_ADDRESS + 0x0008, 0x07, 0, RPDLYv>;    //< SDRAM Row-to-Precharge Delay
    };

    /// SDRAM Control Register C - 1 bytes
    struct SDRAMCTRLC : public reg8_t<BASE_ADDRESS + 0x0009> {
        using WRDLY = reg_field_t<BASE_ADDRESS + 0x0009, 0xC0, 6, WRDLYv>;    //< SDRAM Write Recovery Delay
        using ESRDLY = reg_field_t<BASE_ADDRESS + 0x0009, 0x38, 3, ESRDLYv>;    //< SDRAM Exit-Self-refresh-to-Active Delay
        using ROWCOLDLY = reg_field_t<BASE_ADDRESS + 0x0009, 0x07, 0, ROWCOLDLYv>;    //< SDRAM Row-to-Column Delay
    };

    /// Chip Select 0
    EBI_CS_t<BASE_ADDRESS + 0x0010> CS0;

    /// Chip Select 1
    EBI_CS_t<BASE_ADDRESS + 0x0014> CS1;

    /// Chip Select 2
    EBI_CS_t<BASE_ADDRESS + 0x0018> CS2;

    /// Chip Select 3
    EBI_CS_t<BASE_ADDRESS + 0x001C> CS3;

};

} // namespace device
