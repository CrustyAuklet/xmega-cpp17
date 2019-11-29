/**
 * None-EBI (id I3001)
 * External Bus Interface
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace EBI {

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
}   // namespace EBI

/**
 * EBI_CS
 * EBI Chip Select Module
 * Size: 4 bytes
 */
template <addressType BASE_ADDRESS>
struct EBI_CS_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Chip Select Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRLA_t, 6, 2, EBI::CS_ASIZEv> ASIZE = {};    //< Address Size
        static constexpr bitfield_t<CTRLA_t, 6, 2, EBI::CS_ASPACEv> ASPACE = {};    //< Legacy name: Address Space
        static constexpr bitfield_t<CTRLA_t, 1, 0, EBI::CS_MODEv> MODE = {};    //< Memory Mode
    } CTRLA = {};

    /// Chip Select Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<CTRLB_t, 2, 0, EBI::CS_SRWSv> SRWS = {};    //< SRAM Wait State Cycles
        static constexpr bitfield_t<CTRLB_t, 7, 7, bool> SDINITDONE = {};    //< SDRAM Initialization Done
        static constexpr bitfield_t<CTRLB_t, 2, 2, bool> SDSREN = {};    //< SDRAM Self-refresh Enable
        static constexpr bitfield_t<CTRLB_t, 1, 0, EBI::CS_SDMODEv> SDMODE = {};    //< SDRAM Mode
    } CTRLB = {};

    /// Chip Select Base Address - 2 bytes
    static constexpr struct BASEADDR_t : reg_t<uint16_t, BASE_ADDRESS + 0x0002> {
    } BASEADDR = {};

};

/**
 * EBI
 * External Bus Interface
 * Size: 32 bytes
 */
template <addressType BASE_ADDRESS>
struct EBI_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRL_t, 7, 6, EBI::SDDATAWv> SDDATAW = {};    //< SDRAM Data Width Setting
        static constexpr bitfield_t<CTRL_t, 5, 4, EBI::LPCMODEv> LPCMODE = {};    //< SRAM LPC Mode
        static constexpr bitfield_t<CTRL_t, 3, 2, EBI::SRMODEv> SRMODE = {};    //< SRAM Mode
        static constexpr bitfield_t<CTRL_t, 1, 0, EBI::IFMODEv> IFMODE = {};    //< Interface Mode
    } CTRL = {};

    /// SDRAM Control Register A - 1 bytes
    static constexpr struct SDRAMCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<SDRAMCTRLA_t, 3, 3, bool> SDCAS = {};    //< SDRAM CAS Latency Setting
        static constexpr bitfield_t<SDRAMCTRLA_t, 2, 2, bool> SDROW = {};    //< SDRAM ROW Bits Setting
        static constexpr bitfield_t<SDRAMCTRLA_t, 1, 0, EBI::SDCOLv> SDCOL = {};    //< SDRAM Column Bits Setting
    } SDRAMCTRLA = {};

    /// SDRAM Refresh Period - 2 bytes
    static constexpr struct REFRESH_t : reg_t<uint16_t, BASE_ADDRESS + 0x0004> {
    } REFRESH = {};

    /// SDRAM Initialization Delay - 2 bytes
    static constexpr struct INITDLY_t : reg_t<uint16_t, BASE_ADDRESS + 0x0006> {
    } INITDLY = {};

    /// SDRAM Control Register B - 1 bytes
    static constexpr struct SDRAMCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        static constexpr bitfield_t<SDRAMCTRLB_t, 7, 6, EBI::MRDLYv> MRDLY = {};    //< SDRAM Mode Register Delay
        static constexpr bitfield_t<SDRAMCTRLB_t, 5, 3, EBI::ROWCYCDLYv> ROWCYCDLY = {};    //< SDRAM Row Cycle Delay
        static constexpr bitfield_t<SDRAMCTRLB_t, 2, 0, EBI::RPDLYv> RPDLY = {};    //< SDRAM Row-to-Precharge Delay
    } SDRAMCTRLB = {};

    /// SDRAM Control Register C - 1 bytes
    static constexpr struct SDRAMCTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        static constexpr bitfield_t<SDRAMCTRLC_t, 7, 6, EBI::WRDLYv> WRDLY = {};    //< SDRAM Write Recovery Delay
        static constexpr bitfield_t<SDRAMCTRLC_t, 5, 3, EBI::ESRDLYv> ESRDLY = {};    //< SDRAM Exit-Self-refresh-to-Active Delay
        static constexpr bitfield_t<SDRAMCTRLC_t, 2, 0, EBI::ROWCOLDLYv> ROWCOLDLY = {};    //< SDRAM Row-to-Column Delay
    } SDRAMCTRLC = {};

    /// Chip Select 0
    static constexpr EBI_CS_t<BASE_ADDRESS + 0x0010> CS0 = {};

    /// Chip Select 1
    static constexpr EBI_CS_t<BASE_ADDRESS + 0x0014> CS1 = {};

    /// Chip Select 2
    static constexpr EBI_CS_t<BASE_ADDRESS + 0x0018> CS2 = {};

    /// Chip Select 3
    static constexpr EBI_CS_t<BASE_ADDRESS + 0x001C> CS3 = {};

};

} // namespace sfr
