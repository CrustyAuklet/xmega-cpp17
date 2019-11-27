/**
 * XMEGAAU-TC2 (id I6090)
 * 16-bit Timer/Counter type 2
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace TC2 {

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
}   // namespace TC2

/**
 * TC2
 * 16-bit Timer/Counter type 2
 * Size: 48 bytes
 */
template <addressType BASE_ADDRESS>
struct TC2_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRLA_t, 0x0F, 0, CLKSELv> CLKSEL = {};    //< Clock Selection
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<CTRLB_t, 0x80, 7> HCMPDEN = {};    //< High Byte Compare D Enable
        static constexpr bitfield_t<CTRLB_t, 0x40, 6> HCMPCEN = {};    //< High Byte Compare C Enable
        static constexpr bitfield_t<CTRLB_t, 0x20, 5> HCMPBEN = {};    //< High Byte Compare B Enable
        static constexpr bitfield_t<CTRLB_t, 0x10, 4> HCMPAEN = {};    //< High Byte Compare A Enable
        static constexpr bitfield_t<CTRLB_t, 0x08, 3> LCMPDEN = {};    //< Low Byte Compare D Enable
        static constexpr bitfield_t<CTRLB_t, 0x04, 2> LCMPCEN = {};    //< Low Byte Compare C Enable
        static constexpr bitfield_t<CTRLB_t, 0x02, 1> LCMPBEN = {};    //< Low Byte Compare B Enable
        static constexpr bitfield_t<CTRLB_t, 0x01, 0> LCMPAEN = {};    //< Low Byte Compare A Enable
    } CTRLB = {};

    /// Control register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<CTRLC_t, 0x80, 7> HCMPD = {};    //< High Byte Compare D Output Value
        static constexpr bitfield_t<CTRLC_t, 0x40, 6> HCMPC = {};    //< High Byte Compare C Output Value
        static constexpr bitfield_t<CTRLC_t, 0x20, 5> HCMPB = {};    //< High Byte Compare B Output Value
        static constexpr bitfield_t<CTRLC_t, 0x10, 4> HCMPA = {};    //< High Byte Compare A Output Value
        static constexpr bitfield_t<CTRLC_t, 0x08, 3> LCMPD = {};    //< Low Byte Compare D Output Value
        static constexpr bitfield_t<CTRLC_t, 0x04, 2> LCMPC = {};    //< Low Byte Compare C Output Value
        static constexpr bitfield_t<CTRLC_t, 0x02, 1> LCMPB = {};    //< Low Byte Compare B Output Value
        static constexpr bitfield_t<CTRLC_t, 0x01, 0> LCMPA = {};    //< Low Byte Compare A Output Value
    } CTRLC = {};

    /// Control Register E - 1 bytes
    static constexpr struct CTRLE_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        static constexpr bitfield_t<CTRLE_t, 0x03, 0, BYTEMv> BYTEM = {};    //< Byte Mode
    } CTRLE = {};

    /// Interrupt Control Register A - 1 bytes
    static constexpr struct INTCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        static constexpr bitfield_t<INTCTRLA_t, 0x0C, 2, HUNFINTLVLv> HUNFINTLVL = {};    //< High Byte Underflow Interrupt Level
        static constexpr bitfield_t<INTCTRLA_t, 0x03, 0, LUNFINTLVLv> LUNFINTLVL = {};    //< Low Byte Underflow interrupt level
    } INTCTRLA = {};

    /// Interrupt Control Register B - 1 bytes
    static constexpr struct INTCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        static constexpr bitfield_t<INTCTRLB_t, 0xC0, 6, LCMPDINTLVLv> LCMPDINTLVL = {};    //< Low Byte Compare D Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 0x30, 4, LCMPCINTLVLv> LCMPCINTLVL = {};    //< Low Byte Compare C Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 0x0C, 2, LCMPBINTLVLv> LCMPBINTLVL = {};    //< Low Byte Compare B Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 0x03, 0, LCMPAINTLVLv> LCMPAINTLVL = {};    //< Low Byte Compare A Interrupt Level
    } INTCTRLB = {};

    /// Control Register F - 1 bytes
    static constexpr struct CTRLF_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        static constexpr bitfield_t<CTRLF_t, 0x0C, 2, CMDv> CMD = {};    //< Command
        static constexpr bitfield_t<CTRLF_t, 0x03, 0, CMDENv> CMDEN = {};    //< Command Enable
    } CTRLF = {};

    /// Interrupt Flag Register - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        static constexpr bitfield_t<INTFLAGS_t, 0x80, 7> LCMPDIF = {};    //< Low Byte Compare D Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x40, 6> LCMPCIF = {};    //< Low Byte Compare C Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x20, 5> LCMPBIF = {};    //< Low Byte Compare B Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x10, 4> LCMPAIF = {};    //< Low Byte Compare A Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x02, 1> HUNFIF = {};    //< High Byte Underflow Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x01, 0> LUNFIF = {};    //< Low Byte Underflow Interrupt Flag
    } INTFLAGS = {};

    /// Low Byte Count - 1 bytes
    static constexpr struct LCNT_t : reg_t<uint8_t, BASE_ADDRESS + 0x0020> {
    } LCNT = {};

    /// High Byte Count - 1 bytes
    static constexpr struct HCNT_t : reg_t<uint8_t, BASE_ADDRESS + 0x0021> {
    } HCNT = {};

    /// Low Byte Period - 1 bytes
    static constexpr struct LPER_t : reg_t<uint8_t, BASE_ADDRESS + 0x0026> {
    } LPER = {};

    /// High Byte Period - 1 bytes
    static constexpr struct HPER_t : reg_t<uint8_t, BASE_ADDRESS + 0x0027> {
    } HPER = {};

    /// Low Byte Compare A - 1 bytes
    static constexpr struct LCMPA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0028> {
    } LCMPA = {};

    /// High Byte Compare A - 1 bytes
    static constexpr struct HCMPA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0029> {
    } HCMPA = {};

    /// Low Byte Compare B - 1 bytes
    static constexpr struct LCMPB_t : reg_t<uint8_t, BASE_ADDRESS + 0x002A> {
    } LCMPB = {};

    /// High Byte Compare B - 1 bytes
    static constexpr struct HCMPB_t : reg_t<uint8_t, BASE_ADDRESS + 0x002B> {
    } HCMPB = {};

    /// Low Byte Compare C - 1 bytes
    static constexpr struct LCMPC_t : reg_t<uint8_t, BASE_ADDRESS + 0x002C> {
    } LCMPC = {};

    /// High Byte Compare C - 1 bytes
    static constexpr struct HCMPC_t : reg_t<uint8_t, BASE_ADDRESS + 0x002D> {
    } HCMPC = {};

    /// Low Byte Compare D - 1 bytes
    static constexpr struct LCMPD_t : reg_t<uint8_t, BASE_ADDRESS + 0x002E> {
    } LCMPD = {};

    /// High Byte Compare D - 1 bytes
    static constexpr struct HCMPD_t : reg_t<uint8_t, BASE_ADDRESS + 0x002F> {
    } HCMPD = {};

};

} // namespace device
