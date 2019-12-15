/**
 * XMEGAAU-TC2 (id I6090)
 * 16-bit Timer/Counter type 2
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

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
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRLA_t, 3, 0, TC2::CLKSELv> CLKSEL = {};    //< Clock Selection
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<CTRLB_t, 7, 7, bool> HCMPDEN = {};    //< High Byte Compare D Enable
        static constexpr bitfield_t<CTRLB_t, 6, 6, bool> HCMPCEN = {};    //< High Byte Compare C Enable
        static constexpr bitfield_t<CTRLB_t, 5, 5, bool> HCMPBEN = {};    //< High Byte Compare B Enable
        static constexpr bitfield_t<CTRLB_t, 4, 4, bool> HCMPAEN = {};    //< High Byte Compare A Enable
        static constexpr bitfield_t<CTRLB_t, 3, 3, bool> LCMPDEN = {};    //< Low Byte Compare D Enable
        static constexpr bitfield_t<CTRLB_t, 2, 2, bool> LCMPCEN = {};    //< Low Byte Compare C Enable
        static constexpr bitfield_t<CTRLB_t, 1, 1, bool> LCMPBEN = {};    //< Low Byte Compare B Enable
        static constexpr bitfield_t<CTRLB_t, 0, 0, bool> LCMPAEN = {};    //< Low Byte Compare A Enable
    } CTRLB = {};

    /// Control register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<CTRLC_t, 7, 7, bool> HCMPD = {};    //< High Byte Compare D Output Value
        static constexpr bitfield_t<CTRLC_t, 6, 6, bool> HCMPC = {};    //< High Byte Compare C Output Value
        static constexpr bitfield_t<CTRLC_t, 5, 5, bool> HCMPB = {};    //< High Byte Compare B Output Value
        static constexpr bitfield_t<CTRLC_t, 4, 4, bool> HCMPA = {};    //< High Byte Compare A Output Value
        static constexpr bitfield_t<CTRLC_t, 3, 3, bool> LCMPD = {};    //< Low Byte Compare D Output Value
        static constexpr bitfield_t<CTRLC_t, 2, 2, bool> LCMPC = {};    //< Low Byte Compare C Output Value
        static constexpr bitfield_t<CTRLC_t, 1, 1, bool> LCMPB = {};    //< Low Byte Compare B Output Value
        static constexpr bitfield_t<CTRLC_t, 0, 0, bool> LCMPA = {};    //< Low Byte Compare A Output Value
    } CTRLC = {};

    /// Control Register E - 1 bytes
    static constexpr struct CTRLE_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<CTRLE_t, 1, 0, TC2::BYTEMv> BYTEM = {};    //< Byte Mode
    } CTRLE = {};

    /// Interrupt Control Register A - 1 bytes
    static constexpr struct INTCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
        static constexpr bitfield_t<INTCTRLA_t, 3, 2, TC2::HUNFINTLVLv> HUNFINTLVL = {};    //< High Byte Underflow Interrupt Level
        static constexpr bitfield_t<INTCTRLA_t, 1, 0, TC2::LUNFINTLVLv> LUNFINTLVL = {};    //< Low Byte Underflow interrupt level
    } INTCTRLA = {};

    /// Interrupt Control Register B - 1 bytes
    static constexpr struct INTCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0007>::operator=;
        static constexpr bitfield_t<INTCTRLB_t, 7, 6, TC2::LCMPDINTLVLv> LCMPDINTLVL = {};    //< Low Byte Compare D Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 5, 4, TC2::LCMPCINTLVLv> LCMPCINTLVL = {};    //< Low Byte Compare C Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 3, 2, TC2::LCMPBINTLVLv> LCMPBINTLVL = {};    //< Low Byte Compare B Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 1, 0, TC2::LCMPAINTLVLv> LCMPAINTLVL = {};    //< Low Byte Compare A Interrupt Level
    } INTCTRLB = {};

    /// Control Register F - 1 bytes
    static constexpr struct CTRLF_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0009>::operator=;
        static constexpr bitfield_t<CTRLF_t, 3, 2, TC2::CMDv> CMD = {};    //< Command
        static constexpr bitfield_t<CTRLF_t, 1, 0, TC2::CMDENv> CMDEN = {};    //< Command Enable
    } CTRLF = {};

    /// Interrupt Flag Register - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000C>::operator=;
        static constexpr bitfield_t<INTFLAGS_t, 7, 7, bool> LCMPDIF = {};    //< Low Byte Compare D Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 6, 6, bool> LCMPCIF = {};    //< Low Byte Compare C Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 5, 5, bool> LCMPBIF = {};    //< Low Byte Compare B Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 4, 4, bool> LCMPAIF = {};    //< Low Byte Compare A Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 1, 1, bool> HUNFIF = {};    //< High Byte Underflow Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0, 0, bool> LUNFIF = {};    //< Low Byte Underflow Interrupt Flag
    } INTFLAGS = {};

    /// Low Byte Count - 1 bytes
    static constexpr struct LCNT_t : reg_t<uint8_t, BASE_ADDRESS + 0x0020> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0020>::operator=;
    } LCNT = {};

    /// High Byte Count - 1 bytes
    static constexpr struct HCNT_t : reg_t<uint8_t, BASE_ADDRESS + 0x0021> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0021>::operator=;
    } HCNT = {};

    /// Low Byte Period - 1 bytes
    static constexpr struct LPER_t : reg_t<uint8_t, BASE_ADDRESS + 0x0026> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0026>::operator=;
    } LPER = {};

    /// High Byte Period - 1 bytes
    static constexpr struct HPER_t : reg_t<uint8_t, BASE_ADDRESS + 0x0027> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0027>::operator=;
    } HPER = {};

    /// Low Byte Compare A - 1 bytes
    static constexpr struct LCMPA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0028> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0028>::operator=;
    } LCMPA = {};

    /// High Byte Compare A - 1 bytes
    static constexpr struct HCMPA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0029> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0029>::operator=;
    } HCMPA = {};

    /// Low Byte Compare B - 1 bytes
    static constexpr struct LCMPB_t : reg_t<uint8_t, BASE_ADDRESS + 0x002A> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x002A>::operator=;
    } LCMPB = {};

    /// High Byte Compare B - 1 bytes
    static constexpr struct HCMPB_t : reg_t<uint8_t, BASE_ADDRESS + 0x002B> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x002B>::operator=;
    } HCMPB = {};

    /// Low Byte Compare C - 1 bytes
    static constexpr struct LCMPC_t : reg_t<uint8_t, BASE_ADDRESS + 0x002C> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x002C>::operator=;
    } LCMPC = {};

    /// High Byte Compare C - 1 bytes
    static constexpr struct HCMPC_t : reg_t<uint8_t, BASE_ADDRESS + 0x002D> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x002D>::operator=;
    } HCMPC = {};

    /// Low Byte Compare D - 1 bytes
    static constexpr struct LCMPD_t : reg_t<uint8_t, BASE_ADDRESS + 0x002E> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x002E>::operator=;
    } LCMPD = {};

    /// High Byte Compare D - 1 bytes
    static constexpr struct HCMPD_t : reg_t<uint8_t, BASE_ADDRESS + 0x002F> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x002F>::operator=;
    } HCMPD = {};

    // TC2 ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        LUNF = 0, // Low Byte Underflow Interrupt
        HUNF = 1, // High Byte Underflow Interrupt
        LCMPA = 2, // Low Byte Compare A Interrupt
        LCMPB = 3, // Low Byte Compare B Interrupt
        LCMPC = 4, // Low Byte Compare C Interrupt
        LCMPD = 5, // Low Byte Compare D Interrupt
    };
};

} // namespace sfr
