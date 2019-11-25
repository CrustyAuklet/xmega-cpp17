/**
 * None-DMA (id I3000)
 * DMA Controller
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * DMA_CH
 * DMA Channel
 * Size: 16 bytes
 */
template <addressType BASE_ADDRESS>
struct DMA_CH_t {
    // Interrupt level
    enum class CH_ERRINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low level
        MED = 0x02, // Medium level
        HI = 0x03, // High level
    };

    // Interrupt level
    enum class CH_TRNINTLVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low level
        MED = 0x02, // Medium level
        HI = 0x03, // High level
    };

        // Burst mode
    enum class CH_BURSTLENv : uint8_t {
        _1BYTE = 0x00, // 1-byte burst mode
        _2BYTE = 0x01, // 2-byte burst mode
        _4BYTE = 0x02, // 4-byte burst mode
        _8BYTE = 0x03, // 8-byte burst mode
    };

    // Source address reload mode
    enum class CH_SRCRELOADv : uint8_t {
        NONE = 0x00, // No reload
        BLOCK = 0x01, // Reload at end of block
        BURST = 0x02, // Reload at end of burst
        TRANSACTION = 0x03, // Reload at end of transaction
    };

    // Source addressing mode
    enum class CH_SRCDIRv : uint8_t {
        FIXED = 0x00, // Fixed
        INC = 0x01, // Increment
        DEC = 0x02, // Decrement
    };

    // Destination adress reload mode
    enum class CH_DESTRELOADv : uint8_t {
        NONE = 0x00, // No reload
        BLOCK = 0x01, // Reload at end of block
        BURST = 0x02, // Reload at end of burst
        TRANSACTION = 0x03, // Reload at end of transaction
    };

    // Destination adressing mode
    enum class CH_DESTDIRv : uint8_t {
        FIXED = 0x00, // Fixed
        INC = 0x01, // Increment
        DEC = 0x02, // Decrement
    };

    // Transfer trigger source
    enum class CH_TRIGSRCv : uint8_t {
        OFF = 0x00, // Off software triggers only
        EVSYS_CH0 = 0x01, // Event System Channel 0
        EVSYS_CH1 = 0x02, // Event System Channel 1
        EVSYS_CH2 = 0x03, // Event System Channel 2
        AES = 0x04, // AES
        ADCA_CH0 = 0x10, // ADCA Channel 0
        ADCA_CH1 = 0x11, // ADCA Channel 1
        ADCA_CH2 = 0x12, // ADCA Channel 2
        ADCA_CH3 = 0x13, // ADCA Channel 3
        ADCA_CH4 = 0x14, // ADCA Channel 0,1,2,3 combined
        DACA_CH0 = 0x15, // DACA Channel 0
        DACA_CH1 = 0x16, // DACA Channel 1
        ADCB_CH0 = 0x20, // ADCB Channel 0
        ADCB_CH1 = 0x21, // ADCB Channel 1
        ADCB_CH2 = 0x22, // ADCB Channel 2
        ADCB_CH3 = 0x23, // ADCB Channel 3
        ADCB_CH4 = 0x24, // ADCB Channel 0,1,2,3 combined
        DACB_CH0 = 0x25, // DACB Channel 0
        DACB_CH1 = 0x26, // DACB Channel 1
        TCC0_OVF = 0x40, // Timer/Counter C0 Overflow
        TCC0_ERR = 0x41, // Timer/Counter C0 Error
        TCC0_CCA = 0x42, // Timer/Counter C0 Compare or Capture A
        TCC0_CCB = 0x43, // Timer/Counter C0 Compare or Capture B
        TCC0_CCC = 0x44, // Timer/Counter C0 Compare or Capture C
        TCC0_CCD = 0x45, // Timer/Counter C0 Compare or Capture D
        TCC1_OVF = 0x46, // Timer/Counter C1 Overflow
        TCC1_ERR = 0x47, // Timer/Counter C1 Error
        TCC1_CCA = 0x48, // Timer/Counter C1 Compare or Capture A
        TCC1_CCB = 0x49, // Timer/Counter C1 Compare or Capture B
        SPIC = 0x4A, // SPI C Transfer Complete
        USARTC0_RXC = 0x4B, // USART C0 Receive Complete
        USARTC0_DRE = 0x4C, // USART C0 Data Register Empty
        USARTC1_RXC = 0x4E, // USART C1 Receive Complete
        USARTC1_DRE = 0x4F, // USART C1 Data Register Empty
        TCD0_OVF = 0x60, // Timer/Counter D0 Overflow
        TCD0_ERR = 0x61, // Timer/Counter D0 Error
        TCD0_CCA = 0x62, // Timer/Counter D0 Compare or Capture A
        TCD0_CCB = 0x63, // Timer/Counter D0 Compare or Capture B
        TCD0_CCC = 0x64, // Timer/Counter D0 Compare or Capture C
        TCD0_CCD = 0x65, // Timer/Counter D0 Compare or Capture D
        TCD1_OVF = 0x66, // Timer/Counter D1 Overflow
        TCD1_ERR = 0x67, // Timer/Counter D1 Error
        TCD1_CCA = 0x68, // Timer/Counter D1 Compare or Capture A
        TCD1_CCB = 0x69, // Timer/Counter D1 Compare or Capture B
        SPID = 0x6A, // SPI D Transfer Complete
        USARTD0_RXC = 0x6B, // USART D0 Receive Complete
        USARTD0_DRE = 0x6C, // USART D0 Data Register Empty
        USARTD1_RXC = 0x6E, // USART D1 Receive Complete
        USARTD1_DRE = 0x6F, // USART D1 Data Register Empty
        TCE0_OVF = 0x80, // Timer/Counter E0 Overflow
        TCE0_ERR = 0x81, // Timer/Counter E0 Error
        TCE0_CCA = 0x82, // Timer/Counter E0 Compare or Capture A
        TCE0_CCB = 0x83, // Timer/Counter E0 Compare or Capture B
        TCE0_CCC = 0x84, // Timer/Counter E0 Compare or Capture C
        TCE0_CCD = 0x85, // Timer/Counter E0 Compare or Capture D
        TCE1_OVF = 0x86, // Timer/Counter E1 Overflow
        TCE1_ERR = 0x87, // Timer/Counter E1 Error
        TCE1_CCA = 0x88, // Timer/Counter E1 Compare or Capture A
        TCE1_CCB = 0x89, // Timer/Counter E1 Compare or Capture B
        SPIE = 0x8A, // SPI E Transfer Complete
        USARTE0_RXC = 0x8B, // USART E0 Receive Complete
        USARTE0_DRE = 0x8C, // USART E0 Data Register Empty
        USARTE1_RXC = 0x8E, // USART E1 Receive Complete
        USARTE1_DRE = 0x8F, // USART E1 Data Register Empty
        TCF0_OVF = 0xA0, // Timer/Counter F0 Overflow
        TCF0_ERR = 0xA1, // Timer/Counter F0 Error
        TCF0_CCA = 0xA2, // Timer/Counter F0 Compare or Capture A
        TCF0_CCB = 0xA3, // Timer/Counter F0 Compare or Capture B
        TCF0_CCC = 0xA4, // Timer/Counter F0 Compare or Capture C
        TCF0_CCD = 0xA5, // Timer/Counter F0 Compare or Capture D
        TCF1_OVF = 0xA6, // Timer/Counter F1 Overflow
        TCF1_ERR = 0xA7, // Timer/Counter F1 Error
        TCF1_CCA = 0xA8, // Timer/Counter F1 Compare or Capture A
        TCF1_CCB = 0xA9, // Timer/Counter F1 Compare or Capture B
        SPIF = 0xAA, // SPI F Transfer Complete
        USARTF0_RXC = 0xAB, // USART F0 Receive Complete
        USARTF0_DRE = 0xAC, // USART F0 Data Register Empty
        USARTF1_RXC = 0xAE, // USART F1 Receive Complete
        USARTF1_DRE = 0xAF, // USART F1 Data Register Empty
    };

    /// Channel Control - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x80, 7>;    //< Channel Enable
        using RESET = reg_field_t<BASE_ADDRESS + 0x0000, 0x40, 6>;    //< Channel Software Reset
        using REPEAT = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< Channel Repeat Mode
        using TRFREQ = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Channel Transfer Request
        using SINGLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< Channel Single Shot Data Transfer
        using BURSTLEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x03, 0, CH_BURSTLENv>;    //< Channel Transfer Mode
    };

    /// Channel Control - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0001> {
        using CHBUSY = reg_field_t<BASE_ADDRESS + 0x0001, 0x80, 7>;    //< Block Transfer Busy
        using CHPEND = reg_field_t<BASE_ADDRESS + 0x0001, 0x40, 6>;    //< Block Transfer Pending
        using ERRIF = reg_field_t<BASE_ADDRESS + 0x0001, 0x20, 5>;    //< Block Transfer Error Interrupt Flag
        using TRNIF = reg_field_t<BASE_ADDRESS + 0x0001, 0x10, 4>;    //< Transaction Complete Interrup Flag
        using ERRINTLVL = reg_field_t<BASE_ADDRESS + 0x0001, 0x0C, 2, CH_ERRINTLVLv>;    //< Transfer Error Interrupt Level
        using TRNINTLVL = reg_field_t<BASE_ADDRESS + 0x0001, 0x03, 0, CH_TRNINTLVLv>;    //< Transaction Complete Interrupt Level
    };

    /// Address Control - 1 bytes
    struct ADDRCTRL : public reg8_t<BASE_ADDRESS + 0x0002> {
        using SRCRELOAD = reg_field_t<BASE_ADDRESS + 0x0002, 0xC0, 6, CH_SRCRELOADv>;    //< Channel Source Address Reload
        using SRCDIR = reg_field_t<BASE_ADDRESS + 0x0002, 0x30, 4, CH_SRCDIRv>;    //< Channel Source Address Mode
        using DESTRELOAD = reg_field_t<BASE_ADDRESS + 0x0002, 0x0C, 2, CH_DESTRELOADv>;    //< Channel Destination Address Reload
        using DESTDIR = reg_field_t<BASE_ADDRESS + 0x0002, 0x03, 0, CH_DESTDIRv>;    //< Channel Destination Address Mode
    };

    /// Channel Trigger Source - 1 bytes
    struct TRIGSRC : public reg8_t<BASE_ADDRESS + 0x0003> {
        using TRIGSRCf = reg_field_t<BASE_ADDRESS + 0x0003, 0xFF, 0, CH_TRIGSRCv>;    //< Channel Trigger Source
    };

    /// Channel Block Transfer Count - 2 bytes
    struct TRFCNT : public reg16_t<BASE_ADDRESS + 0x0004> {
    };

    /// Channel Repeat Count - 1 bytes
    struct REPCNT : public reg8_t<BASE_ADDRESS + 0x0006> {
    };

    /// Channel Source Address 0 - 1 bytes
    struct SRCADDR0 : public reg8_t<BASE_ADDRESS + 0x0008> {
    };

    /// Channel Source Address 1 - 1 bytes
    struct SRCADDR1 : public reg8_t<BASE_ADDRESS + 0x0009> {
    };

    /// Channel Source Address 2 - 1 bytes
    struct SRCADDR2 : public reg8_t<BASE_ADDRESS + 0x000A> {
    };

    /// Channel Destination Address 0 - 1 bytes
    struct DESTADDR0 : public reg8_t<BASE_ADDRESS + 0x000C> {
    };

    /// Channel Destination Address 1 - 1 bytes
    struct DESTADDR1 : public reg8_t<BASE_ADDRESS + 0x000D> {
    };

    /// Channel Destination Address 2 - 1 bytes
    struct DESTADDR2 : public reg8_t<BASE_ADDRESS + 0x000E> {
    };
};

/**
 * DMA
 * DMA Controller
 * Size: 80 bytes
 */
template <addressType BASE_ADDRESS>
struct DMA_t {
    // Double buffering mode
    enum class DBUFMODEv : uint8_t {
        DISABLED = 0x00, // Double buffering disabled
        CH01 = 0x01, // Double buffering enabled on channel 0/1
        CH23 = 0x02, // Double buffering enabled on channel 2/3
        CH01CH23 = 0x03, // Double buffering enabled on ch. 0/1 and ch. 2/3
    };

    // Priority mode
    enum class PRIMODEv : uint8_t {
        RR0123 = 0x00, // Round Robin
        CH0RR123 = 0x01, // Channel 0 > Round Robin on channel 1/2/3
        CH01RR23 = 0x02, // Channel 0 > channel 1 > Round Robin on channel 2/3
        CH0123 = 0x03, // Channel 0 > channel 1 > channel 2 > channel 3
    };

    // DMA ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        CH0 = 0, // Channel 0 Interrupt
        CH1 = 1, // Channel 1 Interrupt
        CH2 = 2, // Channel 2 Interrupt
        CH3 = 3, // Channel 3 Interrupt
    };

    /// Control - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x80, 7>;    //< Enable
        using RESET = reg_field_t<BASE_ADDRESS + 0x0000, 0x40, 6>;    //< Software Reset
        using DBUFMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x0C, 2, DBUFMODEv>;    //< Double Buffering Mode
        using PRIMODE = reg_field_t<BASE_ADDRESS + 0x0000, 0x03, 0, PRIMODEv>;    //< Channel Priority Mode
    };

    /// Transfer Interrupt Status - 1 bytes
    struct INTFLAGS : public reg8_t<BASE_ADDRESS + 0x0003> {
        using CH3ERRIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x80, 7>;    //< Channel 3 Block Transfer Error Interrupt Flag
        using CH2ERRIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x40, 6>;    //< Channel 2 Block Transfer Error Interrupt Flag
        using CH1ERRIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x20, 5>;    //< Channel 1 Block Transfer Error Interrupt Flag
        using CH0ERRIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x10, 4>;    //< Channel 0 Block Transfer Error Interrupt Flag
        using CH3TRNIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x08, 3>;    //< Channel 3 Transaction Complete Interrupt Flag
        using CH2TRNIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x04, 2>;    //< Channel 2 Transaction Complete Interrupt Flag
        using CH1TRNIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x02, 1>;    //< Channel 1 Transaction Complete Interrupt Flag
        using CH0TRNIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x01, 0>;    //< Channel 0 Transaction Complete Interrupt Flag
    };

    /// Status - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0004> {
        using CH3BUSY = reg_field_t<BASE_ADDRESS + 0x0004, 0x80, 7>;    //< Channel 3 Block Transfer Busy
        using CH2BUSY = reg_field_t<BASE_ADDRESS + 0x0004, 0x40, 6>;    //< Channel 2 Block Transfer Busy
        using CH1BUSY = reg_field_t<BASE_ADDRESS + 0x0004, 0x20, 5>;    //< Channel 1 Block Transfer Busy
        using CH0BUSY = reg_field_t<BASE_ADDRESS + 0x0004, 0x10, 4>;    //< Channel 0 Block Transfer Busy
        using CH3PEND = reg_field_t<BASE_ADDRESS + 0x0004, 0x08, 3>;    //< Channel 3 Block Transfer Pending
        using CH2PEND = reg_field_t<BASE_ADDRESS + 0x0004, 0x04, 2>;    //< Channel 2 Block Transfer Pending
        using CH1PEND = reg_field_t<BASE_ADDRESS + 0x0004, 0x02, 1>;    //< Channel 1 Block Transfer Pending
        using CH0PEND = reg_field_t<BASE_ADDRESS + 0x0004, 0x01, 0>;    //< Channel 0 Block Transfer Pending
    };

    /// Temporary Register For 16/24-bit Access - 2 bytes
    struct TEMP : public reg16_t<BASE_ADDRESS + 0x0006> {
    };

    /// DMA Channel 0
    DMA_CH_t<BASE_ADDRESS + 0x0010> CH0;

    /// DMA Channel 1
    DMA_CH_t<BASE_ADDRESS + 0x0020> CH1;

    /// DMA Channel 2
    DMA_CH_t<BASE_ADDRESS + 0x0030> CH2;

    /// DMA Channel 3
    DMA_CH_t<BASE_ADDRESS + 0x0040> CH3;

};

} // namespace device
