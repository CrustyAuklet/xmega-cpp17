/**
 * XMEGAAU-TC (id I6090)
 * 16-bit Timer/Counter With PWM
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

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

    // TC0 ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        OVF = 0, // Overflow Interrupt
        ERR = 1, // Error Interrupt
        CCA = 2, // Compare or Capture A Interrupt
        CCB = 3, // Compare or Capture B Interrupt
        CCC = 4, // Compare or Capture C Interrupt
        CCD = 5, // Compare or Capture D Interrupt
    };
    // TC1 ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        OVF = 0, // Overflow Interrupt
        ERR = 1, // Error Interrupt
        CCA = 2, // Compare or Capture A Interrupt
        CCB = 3, // Compare or Capture B Interrupt
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
        static constexpr bitfield_t<CTRLA_t, 0x0F, 0, CLKSELv> CLKSEL = {};    //< Clock Selection
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<CTRLB_t, 0x80, 7> CCDEN = {};    //< Compare or Capture D Enable
        static constexpr bitfield_t<CTRLB_t, 0x40, 6> CCCEN = {};    //< Compare or Capture C Enable
        static constexpr bitfield_t<CTRLB_t, 0x20, 5> CCBEN = {};    //< Compare or Capture B Enable
        static constexpr bitfield_t<CTRLB_t, 0x10, 4> CCAEN = {};    //< Compare or Capture A Enable
        static constexpr bitfield_t<CTRLB_t, 0x07, 0, WGMODEv> WGMODE = {};    //< Waveform generation mode
    } CTRLB = {};

    /// Control register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<CTRLC_t, 0x08, 3> CMPD = {};    //< Compare D Output Value
        static constexpr bitfield_t<CTRLC_t, 0x04, 2> CMPC = {};    //< Compare C Output Value
        static constexpr bitfield_t<CTRLC_t, 0x02, 1> CMPB = {};    //< Compare B Output Value
        static constexpr bitfield_t<CTRLC_t, 0x01, 0> CMPA = {};    //< Compare A Output Value
    } CTRLC = {};

    /// Control Register D - 1 bytes
    static constexpr struct CTRLD_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<CTRLD_t, 0xE0, 5, EVACTv> EVACT = {};    //< Event Action
        static constexpr bitfield_t<CTRLD_t, 0x10, 4> EVDLY = {};    //< Event Delay
        static constexpr bitfield_t<CTRLD_t, 0x0F, 0, EVSELv> EVSEL = {};    //< Event Source Select
    } CTRLD = {};

    /// Control Register E - 1 bytes
    static constexpr struct CTRLE_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        static constexpr bitfield_t<CTRLE_t, 0x03, 0, BYTEMv> BYTEM = {};    //< Byte Mode
    } CTRLE = {};

    /// Interrupt Control Register A - 1 bytes
    static constexpr struct INTCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        static constexpr bitfield_t<INTCTRLA_t, 0x0C, 2, ERRINTLVLv> ERRINTLVL = {};    //< Error Interrupt Level
        static constexpr bitfield_t<INTCTRLA_t, 0x03, 0, OVFINTLVLv> OVFINTLVL = {};    //< Overflow interrupt level
    } INTCTRLA = {};

    /// Interrupt Control Register B - 1 bytes
    static constexpr struct INTCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        static constexpr bitfield_t<INTCTRLB_t, 0xC0, 6, CCDINTLVLv> CCDINTLVL = {};    //< Compare or Capture D Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 0x30, 4, CCCINTLVLv> CCCINTLVL = {};    //< Compare or Capture C Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 0x0C, 2, CCBINTLVLv> CCBINTLVL = {};    //< Compare or Capture B Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 0x03, 0, CCAINTLVLv> CCAINTLVL = {};    //< Compare or Capture A Interrupt Level
    } INTCTRLB = {};

    /// Control Register F Clear - 1 bytes
    static constexpr struct CTRLFCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        static constexpr bitfield_t<CTRLFCLR_t, 0x0C, 2> CMD = {};    //< Command
        static constexpr bitfield_t<CTRLFCLR_t, 0x02, 1> LUPD = {};    //< Lock Update
        static constexpr bitfield_t<CTRLFCLR_t, 0x01, 0> DIR = {};    //< Direction
    } CTRLFCLR = {};

    /// Control Register F Set - 1 bytes
    static constexpr struct CTRLFSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        static constexpr bitfield_t<CTRLFSET_t, 0x0C, 2, CMDv> CMD = {};    //< Command
        static constexpr bitfield_t<CTRLFSET_t, 0x02, 1> LUPD = {};    //< Lock Update
        static constexpr bitfield_t<CTRLFSET_t, 0x01, 0> DIR = {};    //< Direction
    } CTRLFSET = {};

    /// Control Register G Clear - 1 bytes
    static constexpr struct CTRLGCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        static constexpr bitfield_t<CTRLGCLR_t, 0x10, 4> CCDBV = {};    //< Compare or Capture D Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 0x08, 3> CCCBV = {};    //< Compare or Capture C Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 0x04, 2> CCBBV = {};    //< Compare or Capture B Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 0x02, 1> CCABV = {};    //< Compare or Capture A Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 0x01, 0> PERBV = {};    //< Period Buffer Valid
    } CTRLGCLR = {};

    /// Control Register G Set - 1 bytes
    static constexpr struct CTRLGSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        static constexpr bitfield_t<CTRLGSET_t, 0x10, 4> CCDBV = {};    //< Compare or Capture D Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 0x08, 3> CCCBV = {};    //< Compare or Capture C Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 0x04, 2> CCBBV = {};    //< Compare or Capture B Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 0x02, 1> CCABV = {};    //< Compare or Capture A Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 0x01, 0> PERBV = {};    //< Period Buffer Valid
    } CTRLGSET = {};

    /// Interrupt Flag Register - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        static constexpr bitfield_t<INTFLAGS_t, 0x80, 7> CCDIF = {};    //< Compare or Capture D Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x40, 6> CCCIF = {};    //< Compare or Capture C Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x20, 5> CCBIF = {};    //< Compare or Capture B Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x10, 4> CCAIF = {};    //< Compare or Capture A Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x02, 1> ERRIF = {};    //< Error Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x01, 0> OVFIF = {};    //< Overflow Interrupt Flag
    } INTFLAGS = {};

    /// Temporary Register For 16-bit Access - 1 bytes
    static constexpr struct TEMP_t : reg_t<uint8_t, BASE_ADDRESS + 0x000F> {
    } TEMP = {};

    /// Count - 2 bytes
    static constexpr struct CNT_t : reg_t<uint16_t, BASE_ADDRESS + 0x0020> {
    } CNT = {};

    /// Period - 2 bytes
    static constexpr struct PER_t : reg_t<uint16_t, BASE_ADDRESS + 0x0026> {
    } PER = {};

    /// Compare or Capture A - 2 bytes
    static constexpr struct CCA_t : reg_t<uint16_t, BASE_ADDRESS + 0x0028> {
    } CCA = {};

    /// Compare or Capture B - 2 bytes
    static constexpr struct CCB_t : reg_t<uint16_t, BASE_ADDRESS + 0x002A> {
    } CCB = {};

    /// Compare or Capture C - 2 bytes
    static constexpr struct CCC_t : reg_t<uint16_t, BASE_ADDRESS + 0x002C> {
    } CCC = {};

    /// Compare or Capture D - 2 bytes
    static constexpr struct CCD_t : reg_t<uint16_t, BASE_ADDRESS + 0x002E> {
    } CCD = {};

    /// Period Buffer - 2 bytes
    static constexpr struct PERBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x0036> {
    } PERBUF = {};

    /// Compare Or Capture A Buffer - 2 bytes
    static constexpr struct CCABUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x0038> {
    } CCABUF = {};

    /// Compare Or Capture B Buffer - 2 bytes
    static constexpr struct CCBBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x003A> {
    } CCBBUF = {};

    /// Compare Or Capture C Buffer - 2 bytes
    static constexpr struct CCCBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x003C> {
    } CCCBUF = {};

    /// Compare Or Capture D Buffer - 2 bytes
    static constexpr struct CCDBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x003E> {
    } CCDBUF = {};

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
        static constexpr bitfield_t<CTRLA_t, 0x0F, 0, CLKSELv> CLKSEL = {};    //< Clock Selection
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<CTRLB_t, 0x20, 5> CCBEN = {};    //< Compare or Capture B Enable
        static constexpr bitfield_t<CTRLB_t, 0x10, 4> CCAEN = {};    //< Compare or Capture A Enable
        static constexpr bitfield_t<CTRLB_t, 0x07, 0, WGMODEv> WGMODE = {};    //< Waveform generation mode
    } CTRLB = {};

    /// Control register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<CTRLC_t, 0x02, 1> CMPB = {};    //< Compare B Output Value
        static constexpr bitfield_t<CTRLC_t, 0x01, 0> CMPA = {};    //< Compare A Output Value
    } CTRLC = {};

    /// Control Register D - 1 bytes
    static constexpr struct CTRLD_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<CTRLD_t, 0xE0, 5, EVACTv> EVACT = {};    //< Event Action
        static constexpr bitfield_t<CTRLD_t, 0x10, 4> EVDLY = {};    //< Event Delay
        static constexpr bitfield_t<CTRLD_t, 0x0F, 0, EVSELv> EVSEL = {};    //< Event Source Select
    } CTRLD = {};

    /// Control Register E - 1 bytes
    static constexpr struct CTRLE_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        static constexpr bitfield_t<CTRLE_t, 0x01, 0> BYTEM = {};    //< Byte Mode
    } CTRLE = {};

    /// Interrupt Control Register A - 1 bytes
    static constexpr struct INTCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        static constexpr bitfield_t<INTCTRLA_t, 0x0C, 2, ERRINTLVLv> ERRINTLVL = {};    //< Error Interrupt Level
        static constexpr bitfield_t<INTCTRLA_t, 0x03, 0, OVFINTLVLv> OVFINTLVL = {};    //< Overflow interrupt level
    } INTCTRLA = {};

    /// Interrupt Control Register B - 1 bytes
    static constexpr struct INTCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        static constexpr bitfield_t<INTCTRLB_t, 0x0C, 2, CCBINTLVLv> CCBINTLVL = {};    //< Compare or Capture B Interrupt Level
        static constexpr bitfield_t<INTCTRLB_t, 0x03, 0, CCAINTLVLv> CCAINTLVL = {};    //< Compare or Capture A Interrupt Level
    } INTCTRLB = {};

    /// Control Register F Clear - 1 bytes
    static constexpr struct CTRLFCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        static constexpr bitfield_t<CTRLFCLR_t, 0x0C, 2> CMD = {};    //< Command
        static constexpr bitfield_t<CTRLFCLR_t, 0x02, 1> LUPD = {};    //< Lock Update
        static constexpr bitfield_t<CTRLFCLR_t, 0x01, 0> DIR = {};    //< Direction
    } CTRLFCLR = {};

    /// Control Register F Set - 1 bytes
    static constexpr struct CTRLFSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        static constexpr bitfield_t<CTRLFSET_t, 0x0C, 2, CMDv> CMD = {};    //< Command
        static constexpr bitfield_t<CTRLFSET_t, 0x02, 1> LUPD = {};    //< Lock Update
        static constexpr bitfield_t<CTRLFSET_t, 0x01, 0> DIR = {};    //< Direction
    } CTRLFSET = {};

    /// Control Register G Clear - 1 bytes
    static constexpr struct CTRLGCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        static constexpr bitfield_t<CTRLGCLR_t, 0x04, 2> CCBBV = {};    //< Compare or Capture B Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 0x02, 1> CCABV = {};    //< Compare or Capture A Buffer Valid
        static constexpr bitfield_t<CTRLGCLR_t, 0x01, 0> PERBV = {};    //< Period Buffer Valid
    } CTRLGCLR = {};

    /// Control Register G Set - 1 bytes
    static constexpr struct CTRLGSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        static constexpr bitfield_t<CTRLGSET_t, 0x04, 2> CCBBV = {};    //< Compare or Capture B Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 0x02, 1> CCABV = {};    //< Compare or Capture A Buffer Valid
        static constexpr bitfield_t<CTRLGSET_t, 0x01, 0> PERBV = {};    //< Period Buffer Valid
    } CTRLGSET = {};

    /// Interrupt Flag Register - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        static constexpr bitfield_t<INTFLAGS_t, 0x20, 5> CCBIF = {};    //< Compare or Capture B Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x10, 4> CCAIF = {};    //< Compare or Capture A Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x02, 1> ERRIF = {};    //< Error Interrupt Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x01, 0> OVFIF = {};    //< Overflow Interrupt Flag
    } INTFLAGS = {};

    /// Temporary Register For 16-bit Access - 1 bytes
    static constexpr struct TEMP_t : reg_t<uint8_t, BASE_ADDRESS + 0x000F> {
    } TEMP = {};

    /// Count - 2 bytes
    static constexpr struct CNT_t : reg_t<uint16_t, BASE_ADDRESS + 0x0020> {
    } CNT = {};

    /// Period - 2 bytes
    static constexpr struct PER_t : reg_t<uint16_t, BASE_ADDRESS + 0x0026> {
    } PER = {};

    /// Compare or Capture A - 2 bytes
    static constexpr struct CCA_t : reg_t<uint16_t, BASE_ADDRESS + 0x0028> {
    } CCA = {};

    /// Compare or Capture B - 2 bytes
    static constexpr struct CCB_t : reg_t<uint16_t, BASE_ADDRESS + 0x002A> {
    } CCB = {};

    /// Period Buffer - 2 bytes
    static constexpr struct PERBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x0036> {
    } PERBUF = {};

    /// Compare Or Capture A Buffer - 2 bytes
    static constexpr struct CCABUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x0038> {
    } CCABUF = {};

    /// Compare Or Capture B Buffer - 2 bytes
    static constexpr struct CCBBUF_t : reg_t<uint16_t, BASE_ADDRESS + 0x003A> {
    } CCBBUF = {};

};

} // namespace device
