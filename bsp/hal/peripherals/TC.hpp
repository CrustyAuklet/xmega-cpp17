/**
 * XMEGAAU-TC (id I6090)
 * 16-bit Timer/Counter With PWM
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * TC1
 * 16-bit Timer/Counter 1
 * Size: 60 bytes
 */
template <addressType BASE_ADDRESS>
struct TC1_t {
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

    /// Control  Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using CLKSEL = reg_field_t<BASE_ADDRESS + 0x0000, 0x0F, 0, CLKSELv>;    //< Clock Selection
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0001> {
        using CCBEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x20, 5>;    //< Compare or Capture B Enable
        using CCAEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x10, 4>;    //< Compare or Capture A Enable
        using WGMODE = reg_field_t<BASE_ADDRESS + 0x0001, 0x07, 0, WGMODEv>;    //< Waveform generation mode
    };

    /// Control register C - 1 bytes
    struct CTRLC : public reg8_t<BASE_ADDRESS + 0x0002> {
        using CMPB = reg_field_t<BASE_ADDRESS + 0x0002, 0x02, 1>;    //< Compare B Output Value
        using CMPA = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Compare A Output Value
    };

    /// Control Register D - 1 bytes
    struct CTRLD : public reg8_t<BASE_ADDRESS + 0x0003> {
        using EVACT = reg_field_t<BASE_ADDRESS + 0x0003, 0xE0, 5, EVACTv>;    //< Event Action
        using EVDLY = reg_field_t<BASE_ADDRESS + 0x0003, 0x10, 4>;    //< Event Delay
        using EVSEL = reg_field_t<BASE_ADDRESS + 0x0003, 0x0F, 0, EVSELv>;    //< Event Source Select
    };

    /// Control Register E - 1 bytes
    struct CTRLE : public reg8_t<BASE_ADDRESS + 0x0004> {
        using BYTEM = reg_field_t<BASE_ADDRESS + 0x0004, 0x01, 0>;    //< Byte Mode
    };

    /// Interrupt Control Register A - 1 bytes
    struct INTCTRLA : public reg8_t<BASE_ADDRESS + 0x0006> {
        using ERRINTLVL = reg_field_t<BASE_ADDRESS + 0x0006, 0x0C, 2, ERRINTLVLv>;    //< Error Interrupt Level
        using OVFINTLVL = reg_field_t<BASE_ADDRESS + 0x0006, 0x03, 0, OVFINTLVLv>;    //< Overflow interrupt level
    };

    /// Interrupt Control Register B - 1 bytes
    struct INTCTRLB : public reg8_t<BASE_ADDRESS + 0x0007> {
        using CCBINTLVL = reg_field_t<BASE_ADDRESS + 0x0007, 0x0C, 2, CCBINTLVLv>;    //< Compare or Capture B Interrupt Level
        using CCAINTLVL = reg_field_t<BASE_ADDRESS + 0x0007, 0x03, 0, CCAINTLVLv>;    //< Compare or Capture A Interrupt Level
    };

    /// Control Register F Clear - 1 bytes
    struct CTRLFCLR : public reg8_t<BASE_ADDRESS + 0x0008> {
        using CMD = reg_field_t<BASE_ADDRESS + 0x0008, 0x0C, 2>;    //< Command
        using LUPD = reg_field_t<BASE_ADDRESS + 0x0008, 0x02, 1>;    //< Lock Update
        using DIR = reg_field_t<BASE_ADDRESS + 0x0008, 0x01, 0>;    //< Direction
    };

    /// Control Register F Set - 1 bytes
    struct CTRLFSET : public reg8_t<BASE_ADDRESS + 0x0009> {
        using CMD = reg_field_t<BASE_ADDRESS + 0x0009, 0x0C, 2, CMDv>;    //< Command
        using LUPD = reg_field_t<BASE_ADDRESS + 0x0009, 0x02, 1>;    //< Lock Update
        using DIR = reg_field_t<BASE_ADDRESS + 0x0009, 0x01, 0>;    //< Direction
    };

    /// Control Register G Clear - 1 bytes
    struct CTRLGCLR : public reg8_t<BASE_ADDRESS + 0x000A> {
        using CCBBV = reg_field_t<BASE_ADDRESS + 0x000A, 0x04, 2>;    //< Compare or Capture B Buffer Valid
        using CCABV = reg_field_t<BASE_ADDRESS + 0x000A, 0x02, 1>;    //< Compare or Capture A Buffer Valid
        using PERBV = reg_field_t<BASE_ADDRESS + 0x000A, 0x01, 0>;    //< Period Buffer Valid
    };

    /// Control Register G Set - 1 bytes
    struct CTRLGSET : public reg8_t<BASE_ADDRESS + 0x000B> {
        using CCBBV = reg_field_t<BASE_ADDRESS + 0x000B, 0x04, 2>;    //< Compare or Capture B Buffer Valid
        using CCABV = reg_field_t<BASE_ADDRESS + 0x000B, 0x02, 1>;    //< Compare or Capture A Buffer Valid
        using PERBV = reg_field_t<BASE_ADDRESS + 0x000B, 0x01, 0>;    //< Period Buffer Valid
    };

    /// Interrupt Flag Register - 1 bytes
    struct INTFLAGS : public reg8_t<BASE_ADDRESS + 0x000C> {
        using CCBIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x20, 5>;    //< Compare or Capture B Interrupt Flag
        using CCAIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x10, 4>;    //< Compare or Capture A Interrupt Flag
        using ERRIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x02, 1>;    //< Error Interrupt Flag
        using OVFIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x01, 0>;    //< Overflow Interrupt Flag
    };

    /// Temporary Register For 16-bit Access - 1 bytes
    struct TEMP : public reg8_t<BASE_ADDRESS + 0x000F> {
    };

    /// Count - 2 bytes
    struct CNT : public reg16_t<BASE_ADDRESS + 0x0020> {
    };

    /// Period - 2 bytes
    struct PER : public reg16_t<BASE_ADDRESS + 0x0026> {
    };

    /// Compare or Capture A - 2 bytes
    struct CCA : public reg16_t<BASE_ADDRESS + 0x0028> {
    };

    /// Compare or Capture B - 2 bytes
    struct CCB : public reg16_t<BASE_ADDRESS + 0x002A> {
    };

    /// Period Buffer - 2 bytes
    struct PERBUF : public reg16_t<BASE_ADDRESS + 0x0036> {
    };

    /// Compare Or Capture A Buffer - 2 bytes
    struct CCABUF : public reg16_t<BASE_ADDRESS + 0x0038> {
    };

    /// Compare Or Capture B Buffer - 2 bytes
    struct CCBBUF : public reg16_t<BASE_ADDRESS + 0x003A> {
    };
};

/**
 * TC0
 * 16-bit Timer/Counter 0
 * Size: 64 bytes
 */
template <addressType BASE_ADDRESS>
struct TC0_t {
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

    /// Control  Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using CLKSEL = reg_field_t<BASE_ADDRESS + 0x0000, 0x0F, 0, CLKSELv>;    //< Clock Selection
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0001> {
        using CCDEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x80, 7>;    //< Compare or Capture D Enable
        using CCCEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x40, 6>;    //< Compare or Capture C Enable
        using CCBEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x20, 5>;    //< Compare or Capture B Enable
        using CCAEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x10, 4>;    //< Compare or Capture A Enable
        using WGMODE = reg_field_t<BASE_ADDRESS + 0x0001, 0x07, 0, WGMODEv>;    //< Waveform generation mode
    };

    /// Control register C - 1 bytes
    struct CTRLC : public reg8_t<BASE_ADDRESS + 0x0002> {
        using CMPD = reg_field_t<BASE_ADDRESS + 0x0002, 0x08, 3>;    //< Compare D Output Value
        using CMPC = reg_field_t<BASE_ADDRESS + 0x0002, 0x04, 2>;    //< Compare C Output Value
        using CMPB = reg_field_t<BASE_ADDRESS + 0x0002, 0x02, 1>;    //< Compare B Output Value
        using CMPA = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Compare A Output Value
    };

    /// Control Register D - 1 bytes
    struct CTRLD : public reg8_t<BASE_ADDRESS + 0x0003> {
        using EVACT = reg_field_t<BASE_ADDRESS + 0x0003, 0xE0, 5, EVACTv>;    //< Event Action
        using EVDLY = reg_field_t<BASE_ADDRESS + 0x0003, 0x10, 4>;    //< Event Delay
        using EVSEL = reg_field_t<BASE_ADDRESS + 0x0003, 0x0F, 0, EVSELv>;    //< Event Source Select
    };

    /// Control Register E - 1 bytes
    struct CTRLE : public reg8_t<BASE_ADDRESS + 0x0004> {
        using BYTEM = reg_field_t<BASE_ADDRESS + 0x0004, 0x03, 0, BYTEMv>;    //< Byte Mode
    };

    /// Interrupt Control Register A - 1 bytes
    struct INTCTRLA : public reg8_t<BASE_ADDRESS + 0x0006> {
        using ERRINTLVL = reg_field_t<BASE_ADDRESS + 0x0006, 0x0C, 2, ERRINTLVLv>;    //< Error Interrupt Level
        using OVFINTLVL = reg_field_t<BASE_ADDRESS + 0x0006, 0x03, 0, OVFINTLVLv>;    //< Overflow interrupt level
    };

    /// Interrupt Control Register B - 1 bytes
    struct INTCTRLB : public reg8_t<BASE_ADDRESS + 0x0007> {
        using CCDINTLVL = reg_field_t<BASE_ADDRESS + 0x0007, 0xC0, 6, CCDINTLVLv>;    //< Compare or Capture D Interrupt Level
        using CCCINTLVL = reg_field_t<BASE_ADDRESS + 0x0007, 0x30, 4, CCCINTLVLv>;    //< Compare or Capture C Interrupt Level
        using CCBINTLVL = reg_field_t<BASE_ADDRESS + 0x0007, 0x0C, 2, CCBINTLVLv>;    //< Compare or Capture B Interrupt Level
        using CCAINTLVL = reg_field_t<BASE_ADDRESS + 0x0007, 0x03, 0, CCAINTLVLv>;    //< Compare or Capture A Interrupt Level
    };

    /// Control Register F Clear - 1 bytes
    struct CTRLFCLR : public reg8_t<BASE_ADDRESS + 0x0008> {
        using CMD = reg_field_t<BASE_ADDRESS + 0x0008, 0x0C, 2>;    //< Command
        using LUPD = reg_field_t<BASE_ADDRESS + 0x0008, 0x02, 1>;    //< Lock Update
        using DIR = reg_field_t<BASE_ADDRESS + 0x0008, 0x01, 0>;    //< Direction
    };

    /// Control Register F Set - 1 bytes
    struct CTRLFSET : public reg8_t<BASE_ADDRESS + 0x0009> {
        using CMD = reg_field_t<BASE_ADDRESS + 0x0009, 0x0C, 2, CMDv>;    //< Command
        using LUPD = reg_field_t<BASE_ADDRESS + 0x0009, 0x02, 1>;    //< Lock Update
        using DIR = reg_field_t<BASE_ADDRESS + 0x0009, 0x01, 0>;    //< Direction
    };

    /// Control Register G Clear - 1 bytes
    struct CTRLGCLR : public reg8_t<BASE_ADDRESS + 0x000A> {
        using CCDBV = reg_field_t<BASE_ADDRESS + 0x000A, 0x10, 4>;    //< Compare or Capture D Buffer Valid
        using CCCBV = reg_field_t<BASE_ADDRESS + 0x000A, 0x08, 3>;    //< Compare or Capture C Buffer Valid
        using CCBBV = reg_field_t<BASE_ADDRESS + 0x000A, 0x04, 2>;    //< Compare or Capture B Buffer Valid
        using CCABV = reg_field_t<BASE_ADDRESS + 0x000A, 0x02, 1>;    //< Compare or Capture A Buffer Valid
        using PERBV = reg_field_t<BASE_ADDRESS + 0x000A, 0x01, 0>;    //< Period Buffer Valid
    };

    /// Control Register G Set - 1 bytes
    struct CTRLGSET : public reg8_t<BASE_ADDRESS + 0x000B> {
        using CCDBV = reg_field_t<BASE_ADDRESS + 0x000B, 0x10, 4>;    //< Compare or Capture D Buffer Valid
        using CCCBV = reg_field_t<BASE_ADDRESS + 0x000B, 0x08, 3>;    //< Compare or Capture C Buffer Valid
        using CCBBV = reg_field_t<BASE_ADDRESS + 0x000B, 0x04, 2>;    //< Compare or Capture B Buffer Valid
        using CCABV = reg_field_t<BASE_ADDRESS + 0x000B, 0x02, 1>;    //< Compare or Capture A Buffer Valid
        using PERBV = reg_field_t<BASE_ADDRESS + 0x000B, 0x01, 0>;    //< Period Buffer Valid
    };

    /// Interrupt Flag Register - 1 bytes
    struct INTFLAGS : public reg8_t<BASE_ADDRESS + 0x000C> {
        using CCDIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x80, 7>;    //< Compare or Capture D Interrupt Flag
        using CCCIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x40, 6>;    //< Compare or Capture C Interrupt Flag
        using CCBIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x20, 5>;    //< Compare or Capture B Interrupt Flag
        using CCAIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x10, 4>;    //< Compare or Capture A Interrupt Flag
        using ERRIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x02, 1>;    //< Error Interrupt Flag
        using OVFIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x01, 0>;    //< Overflow Interrupt Flag
    };

    /// Temporary Register For 16-bit Access - 1 bytes
    struct TEMP : public reg8_t<BASE_ADDRESS + 0x000F> {
    };

    /// Count - 2 bytes
    struct CNT : public reg16_t<BASE_ADDRESS + 0x0020> {
    };

    /// Period - 2 bytes
    struct PER : public reg16_t<BASE_ADDRESS + 0x0026> {
    };

    /// Compare or Capture A - 2 bytes
    struct CCA : public reg16_t<BASE_ADDRESS + 0x0028> {
    };

    /// Compare or Capture B - 2 bytes
    struct CCB : public reg16_t<BASE_ADDRESS + 0x002A> {
    };

    /// Compare or Capture C - 2 bytes
    struct CCC : public reg16_t<BASE_ADDRESS + 0x002C> {
    };

    /// Compare or Capture D - 2 bytes
    struct CCD : public reg16_t<BASE_ADDRESS + 0x002E> {
    };

    /// Period Buffer - 2 bytes
    struct PERBUF : public reg16_t<BASE_ADDRESS + 0x0036> {
    };

    /// Compare Or Capture A Buffer - 2 bytes
    struct CCABUF : public reg16_t<BASE_ADDRESS + 0x0038> {
    };

    /// Compare Or Capture B Buffer - 2 bytes
    struct CCBBUF : public reg16_t<BASE_ADDRESS + 0x003A> {
    };

    /// Compare Or Capture C Buffer - 2 bytes
    struct CCCBUF : public reg16_t<BASE_ADDRESS + 0x003C> {
    };

    /// Compare Or Capture D Buffer - 2 bytes
    struct CCDBUF : public reg16_t<BASE_ADDRESS + 0x003E> {
    };
};

} // namespace device
