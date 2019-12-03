/**
 * XMEGAAU-TC (id I6090)
 * 16-bit Timer/Counter With PWM
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace TC {

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
    // Waveform Generation Mode
    enum class WGMODEv : uint8_t {
        NORMAL = 0x00, // Normal Mode
        FRQ = 0x01, // Frequency Generation Mode
        SINGLESLOPE = 0x03, // Single Slope
        SS = 0x03, // Single Slope
        DSTOP = 0x05, // Dual Slope, Update on TOP
        DS_T = 0x05, // Dual Slope, Update on TOP
        DSBOTH = 0x06, // Dual Slope, Update on both TOP and BOTTOM
        DS_TB = 0x06, // Dual Slope, Update on both TOP and BOTTOM
        DSBOTTOM = 0x07, // Dual Slope, Update on BOTTOM
        DS_B = 0x07, // Dual Slope, Update on BOTTOM
    };
    // Byte Mode
    enum class BYTEMv : uint8_t {
        NORMAL = 0x00, // 16-bit mode
        BYTEMODE = 0x01, // Timer/Counter operating in byte mode only
        SPLITMODE = 0x02, // Timer/Counter split into two 8-bit Counters (TC2)
    };
    // Event Action
    enum class EVACTv : uint8_t {
        OFF = 0x00, // No Event Action
        CAPT = 0x01, // Input Capture
        UPDOWN = 0x02, // Externally Controlled Up/Down Count
        QDEC = 0x03, // Quadrature Decode
        RESTART = 0x04, // Restart
        FRQ = 0x05, // Frequency Capture
        PW = 0x06, // Pulse-width Capture
    };
    // Event Selection
    enum class EVSELv : uint8_t {
        OFF = 0x00, // No Event Source
        CH0 = 0x08, // Event Channel 0
        CH1 = 0x09, // Event Channel 1
        CH2 = 0x0A, // Event Channel 2
        CH3 = 0x0B, // Event Channel 3
        CH4 = 0x0C, // Event Channel 4
        CH5 = 0x0D, // Event Channel 5
        CH6 = 0x0E, // Event Channel 6
        CH7 = 0x0F, // Event Channel 7
    };
    // Error Interrupt Level
    enum class ERRINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };
    // Overflow Interrupt Level
    enum class OVFINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };
    // Compare or Capture D Interrupt Level
    enum class CCDINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };
    // Compare or Capture C Interrupt Level
    enum class CCCINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };
    // Compare or Capture B Interrupt Level
    enum class CCBINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };
    // Compare or Capture A Interrupt Level
    enum class CCAINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };
    // Timer/Counter Command
    enum class CMDv : uint8_t {
        NONE = 0x00, // No Command
        UPDATE = 0x01, // Force Update
        RESTART = 0x02, // Force Restart
        RESET = 0x03, // Force Hard Reset
    };
}   // namespace TC

/**
 * TC0
 * 16-bit Timer/Counter 0
 * Size: 64 bytes
 */
template <addressType BASE_ADDRESS>
struct TC0_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control  Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRLA_t, 3, 0, TC::CLKSELv> CLKSEL = {};    //< Clock Selection
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<CTRLB_t, 7, 7, bool> CCDEN = {};    //< Compare or Capture D Enable
        static constexpr bitfield_t<CTRLB_t, 6, 6, bool> CCCEN = {};    //< Compare or Capture C Enable
        static constexpr bitfield_t<CTRLB_t, 5, 5, bool> CCBEN = {};    //< Compare or Capture B Enable
        static constexpr bitfield_t<CTRLB_t, 4, 4, bool> CCAEN = {};    //< Compare or Capture A Enable
        static constexpr bitfield_t<CTRLB_t, 2, 0, TC::WGMODEv> WGMODE = {};    //< Waveform generation mode
    } CTRLB = {};

    /// Control register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<CTRLC_t, 3, 3, bool> CMPD = {};    //< Compare D Output Value
        static constexpr bitfield_t<CTRLC_t, 2, 2, bool> CMPC = {};    //< Compare C Output Value
        static constexpr bitfield_t<CTRLC_t, 1, 1, bool> CMPB = {};    //< Compare B Output Value
        static constexpr bitfield_t<CTRLC_t, 0, 0, bool> CMPA = {};    //< Compare A Output Value
    } CTRLC = {};

    /// Control Register D - 1 bytes
    static constexpr struct CTRLD_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<CTRLD_t, 7, 5, TC::EVACTv> EVACT = {};    //< Event Action
        static constexpr bitfield_t<CTRLD_t, 4, 4, bool> EVDLY = {};    //< Event Delay
        static constexpr bitfield_t<CTRLD_t, 3, 0, TC::EVSELv> EVSEL = {};    //< Event Source Select
    } CTRLD = {};

    /// Control Register E - 1 bytes
    static constexpr struct CTRLE_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<CTRLE_t, 1, 0, TC::BYTEMv> BYTEM = {};    //< Byte Mode
    } CTRLE = {};

    /// Interrupt Control Register A - 1 bytes
    static constexpr struct INTCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
        static constexpr bitfield_t<INTCTRLA_t, 3, 2, TC::ERRINTLVLv> ERRINTLVL = {};    //< Error Interrupt Level
        static constexpr bitfield_t<INTCTRLA_t, 1, 0, TC::OVFINTLVLv> OVFINTLVL = {};    //< Overflow interrupt level
    } INTCTRLA = {};

    /// Interrupt Control Register B - 1 bytes
    static constexpr struct INTCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0007>::operator=;
        static constexpr bitfield_t<INTCTRLB_t, 7, 6, TC::CCDINTLVLv> CCDINTLVL = {};    //< Compare or Capture D Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 5, 4, TC::CCCINTLVLv> CCCINTLVL = {};    //< Compare or Capture C Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 3, 2, TC::CCBINTLVLv> CCBINTLVL = {};    //< Compare or Capture B Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 1, 0, TC::CCAINTLVLv> CCAINTLVL = {};    //< Compare or Capture A Interrupt Level
    } INTCTRLB = {};

    /// Control Register F Clear - 1 bytes
    static constexpr struct CTRLFCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0008>::operator=;
        static constexpr bitfield_t<CTRLFCLR_t, 3, 2> CMD = {};    //< Command
        static constexpr bitfield_t<CTRLFCLR_t, 1, 1, bool> LUPD = {};    //< Lock Update
        static constexpr bitfield_t<CTRLFCLR_t, 0, 0, bool> DIR = {};    //< Direction
    } CTRLFCLR = {};

    /// Control Register F Set - 1 bytes
    static constexpr struct CTRLFSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0009>::operator=;
        static constexpr bitfield_t<CTRLFSET_t, 3, 2, TC::CMDv> CMD = {};    //< Command
        static constexpr bitfield_t<CTRLFSET_t, 1, 1, bool> LUPD = {};    //< Lock Update
        static constexpr bitfield_t<CTRLFSET_t, 0, 0, bool> DIR = {};    //< Direction
    } CTRLFSET = {};

    /// Control Register G Clear - 1 bytes
    static constexpr struct CTRLGCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000A>::operator=;
        static constexpr bitfield_t<CTRLGCLR_t, 4, 4, bool> CCDBV = {};    //< Compare or Capture D Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 3, 3, bool> CCCBV = {};    //< Compare or Capture C Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 2, 2, bool> CCBBV = {};    //< Compare or Capture B Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 1, 1, bool> CCABV = {};    //< Compare or Capture A Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 0, 0, bool> PERBV = {};    //< Period Buffer Valid
    } CTRLGCLR = {};

    /// Control Register G Set - 1 bytes
    static constexpr struct CTRLGSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000B>::operator=;
        static constexpr bitfield_t<CTRLGSET_t, 4, 4, bool> CCDBV = {};    //< Compare or Capture D Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 3, 3, bool> CCCBV = {};    //< Compare or Capture C Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 2, 2, bool> CCBBV = {};    //< Compare or Capture B Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 1, 1, bool> CCABV = {};    //< Compare or Capture A Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 0, 0, bool> PERBV = {};    //< Period Buffer Valid
    } CTRLGSET = {};

    /// Interrupt Flag Register - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000C>::operator=;
        static constexpr bitfield_t<INTFLAGS_t, 7, 7, bool> CCDIF = {};    //< Compare or Capture D Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 6, 6, bool> CCCIF = {};    //< Compare or Capture C Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 5, 5, bool> CCBIF = {};    //< Compare or Capture B Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 4, 4, bool> CCAIF = {};    //< Compare or Capture A Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 1, 1, bool> ERRIF = {};    //< Error Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0, 0, bool> OVFIF = {};    //< Overflow Interrupt Flag
    } INTFLAGS = {};

    /// Temporary Register For 16-bit Access - 1 bytes
    static constexpr struct TEMP_t : reg_t<uint8_t, BASE_ADDRESS + 0x000F> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000F>::operator=;
    } TEMP = {};

    /// Count - 2 bytes
    static constexpr struct CNT_t : reg_t<uint16_t, BASE_ADDRESS + 0x0020> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0020>::operator=;
    } CNT = {};

    /// Period - 2 bytes
    static constexpr struct PER_t : reg_t<uint16_t, BASE_ADDRESS + 0x0026> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0026>::operator=;
    } PER = {};

    /// Compare or Capture A - 2 bytes
    static constexpr struct CCA_t : reg_t<uint16_t, BASE_ADDRESS + 0x0028> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0028>::operator=;
    } CCA = {};

    /// Compare or Capture B - 2 bytes
    static constexpr struct CCB_t : reg_t<uint16_t, BASE_ADDRESS + 0x002A> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x002A>::operator=;
    } CCB = {};

    /// Compare or Capture C - 2 bytes
    static constexpr struct CCC_t : reg_t<uint16_t, BASE_ADDRESS + 0x002C> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x002C>::operator=;
    } CCC = {};

    /// Compare or Capture D - 2 bytes
    static constexpr struct CCD_t : reg_t<uint16_t, BASE_ADDRESS + 0x002E> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x002E>::operator=;
    } CCD = {};

    /// Period Buffer - 2 bytes
    static constexpr struct PERBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x0036> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0036>::operator=;
    } PERBUF = {};

    /// Compare Or Capture A Buffer - 2 bytes
    static constexpr struct CCABUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x0038> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0038>::operator=;
    } CCABUF = {};

    /// Compare Or Capture B Buffer - 2 bytes
    static constexpr struct CCBBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x003A> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x003A>::operator=;
    } CCBBUF = {};

    /// Compare Or Capture C Buffer - 2 bytes
    static constexpr struct CCCBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x003C> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x003C>::operator=;
    } CCCBUF = {};

    /// Compare Or Capture D Buffer - 2 bytes
    static constexpr struct CCDBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x003E> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x003E>::operator=;
    } CCDBUF = {};

    // TC0 ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        OVF = 0, // Overflow Interrupt
        ERR = 1, // Error Interrupt
        CCA = 2, // Compare or Capture A Interrupt
        CCB = 3, // Compare or Capture B Interrupt
        CCC = 4, // Compare or Capture C Interrupt
        CCD = 5, // Compare or Capture D Interrupt
    };
};

/**
 * TC1
 * 16-bit Timer/Counter 1
 * Size: 60 bytes
 */
template <addressType BASE_ADDRESS>
struct TC1_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control  Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRLA_t, 3, 0, TC::CLKSELv> CLKSEL = {};    //< Clock Selection
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<CTRLB_t, 5, 5, bool> CCBEN = {};    //< Compare or Capture B Enable
        static constexpr bitfield_t<CTRLB_t, 4, 4, bool> CCAEN = {};    //< Compare or Capture A Enable
        static constexpr bitfield_t<CTRLB_t, 2, 0, TC::WGMODEv> WGMODE = {};    //< Waveform generation mode
    } CTRLB = {};

    /// Control register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<CTRLC_t, 1, 1, bool> CMPB = {};    //< Compare B Output Value
        static constexpr bitfield_t<CTRLC_t, 0, 0, bool> CMPA = {};    //< Compare A Output Value
    } CTRLC = {};

    /// Control Register D - 1 bytes
    static constexpr struct CTRLD_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<CTRLD_t, 7, 5, TC::EVACTv> EVACT = {};    //< Event Action
        static constexpr bitfield_t<CTRLD_t, 4, 4, bool> EVDLY = {};    //< Event Delay
        static constexpr bitfield_t<CTRLD_t, 3, 0, TC::EVSELv> EVSEL = {};    //< Event Source Select
    } CTRLD = {};

    /// Control Register E - 1 bytes
    static constexpr struct CTRLE_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<CTRLE_t, 0, 0, bool> BYTEM = {};    //< Byte Mode
    } CTRLE = {};

    /// Interrupt Control Register A - 1 bytes
    static constexpr struct INTCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
        static constexpr bitfield_t<INTCTRLA_t, 3, 2, TC::ERRINTLVLv> ERRINTLVL = {};    //< Error Interrupt Level
        static constexpr bitfield_t<INTCTRLA_t, 1, 0, TC::OVFINTLVLv> OVFINTLVL = {};    //< Overflow interrupt level
    } INTCTRLA = {};

    /// Interrupt Control Register B - 1 bytes
    static constexpr struct INTCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0007>::operator=;
        static constexpr bitfield_t<INTCTRLB_t, 3, 2, TC::CCBINTLVLv> CCBINTLVL = {};    //< Compare or Capture B Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 1, 0, TC::CCAINTLVLv> CCAINTLVL = {};    //< Compare or Capture A Interrupt Level
    } INTCTRLB = {};

    /// Control Register F Clear - 1 bytes
    static constexpr struct CTRLFCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0008>::operator=;
        static constexpr bitfield_t<CTRLFCLR_t, 3, 2> CMD = {};    //< Command
        static constexpr bitfield_t<CTRLFCLR_t, 1, 1, bool> LUPD = {};    //< Lock Update
        static constexpr bitfield_t<CTRLFCLR_t, 0, 0, bool> DIR = {};    //< Direction
    } CTRLFCLR = {};

    /// Control Register F Set - 1 bytes
    static constexpr struct CTRLFSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0009>::operator=;
        static constexpr bitfield_t<CTRLFSET_t, 3, 2, TC::CMDv> CMD = {};    //< Command
        static constexpr bitfield_t<CTRLFSET_t, 1, 1, bool> LUPD = {};    //< Lock Update
        static constexpr bitfield_t<CTRLFSET_t, 0, 0, bool> DIR = {};    //< Direction
    } CTRLFSET = {};

    /// Control Register G Clear - 1 bytes
    static constexpr struct CTRLGCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000A>::operator=;
        static constexpr bitfield_t<CTRLGCLR_t, 2, 2, bool> CCBBV = {};    //< Compare or Capture B Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 1, 1, bool> CCABV = {};    //< Compare or Capture A Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 0, 0, bool> PERBV = {};    //< Period Buffer Valid
    } CTRLGCLR = {};

    /// Control Register G Set - 1 bytes
    static constexpr struct CTRLGSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000B>::operator=;
        static constexpr bitfield_t<CTRLGSET_t, 2, 2, bool> CCBBV = {};    //< Compare or Capture B Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 1, 1, bool> CCABV = {};    //< Compare or Capture A Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 0, 0, bool> PERBV = {};    //< Period Buffer Valid
    } CTRLGSET = {};

    /// Interrupt Flag Register - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000C>::operator=;
        static constexpr bitfield_t<INTFLAGS_t, 5, 5, bool> CCBIF = {};    //< Compare or Capture B Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 4, 4, bool> CCAIF = {};    //< Compare or Capture A Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 1, 1, bool> ERRIF = {};    //< Error Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0, 0, bool> OVFIF = {};    //< Overflow Interrupt Flag
    } INTFLAGS = {};

    /// Temporary Register For 16-bit Access - 1 bytes
    static constexpr struct TEMP_t : reg_t<uint8_t, BASE_ADDRESS + 0x000F> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000F>::operator=;
    } TEMP = {};

    /// Count - 2 bytes
    static constexpr struct CNT_t : reg_t<uint16_t, BASE_ADDRESS + 0x0020> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0020>::operator=;
    } CNT = {};

    /// Period - 2 bytes
    static constexpr struct PER_t : reg_t<uint16_t, BASE_ADDRESS + 0x0026> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0026>::operator=;
    } PER = {};

    /// Compare or Capture A - 2 bytes
    static constexpr struct CCA_t : reg_t<uint16_t, BASE_ADDRESS + 0x0028> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0028>::operator=;
    } CCA = {};

    /// Compare or Capture B - 2 bytes
    static constexpr struct CCB_t : reg_t<uint16_t, BASE_ADDRESS + 0x002A> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x002A>::operator=;
    } CCB = {};

    /// Period Buffer - 2 bytes
    static constexpr struct PERBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x0036> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0036>::operator=;
    } PERBUF = {};

    /// Compare Or Capture A Buffer - 2 bytes
    static constexpr struct CCABUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x0038> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x0038>::operator=;
    } CCABUF = {};

    /// Compare Or Capture B Buffer - 2 bytes
    static constexpr struct CCBBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x003A> {
        using reg_t<uint16_t, BASE_ADDRESS + 0x003A>::operator=;
    } CCBBUF = {};

    // TC1 ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        OVF = 0, // Overflow Interrupt
        ERR = 1, // Error Interrupt
        CCA = 2, // Compare or Capture A Interrupt
        CCB = 3, // Compare or Capture B Interrupt
    };
};

} // namespace sfr
