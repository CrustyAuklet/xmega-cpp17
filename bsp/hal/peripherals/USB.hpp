/**
 * XMEGAAU-USB (id I3005)
 * USB
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * USB_EP
 * USB Endpoint
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct USB_EP_t {
    // USB Endpoint Type
    enum class EP_TYPEv : uint8_t {
        DISABLE = 0x00, // Endpoint Disabled
        CONTROL = 0x01, // Control
        BULK = 0x02, // Bulk/Interrupt
        ISOCHRONOUS = 0x03, // Isochronous
    };

    // USB Endpoint Buffersize
    enum class EP_BUFSIZEv : uint8_t {
        _8 = 0x00, // 8 bytes buffer size
        _16 = 0x01, // 16 bytes buffer size
        _32 = 0x02, // 32 bytes buffer size
        _64 = 0x03, // 64 bytes buffer size
        _128 = 0x04, // 128 bytes buffer size
        _256 = 0x05, // 256 bytes buffer size
        _512 = 0x06, // 512 bytes buffer size
        _1023 = 0x07, // 1023 bytes buffer size
    };

    /// Endpoint Status - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0000> {
        using STALLF = reg_field_t<BASE_ADDRESS + 0x0000, 0x80, 7>;    //< Endpoint Stall Flag
        using CRC = reg_field_t<BASE_ADDRESS + 0x0000, 0x80, 7>;    //< CRC Error Flag
        using UNF = reg_field_t<BASE_ADDRESS + 0x0000, 0x40, 6>;    //< Underflow Enpoint FLag
        using OVF = reg_field_t<BASE_ADDRESS + 0x0000, 0x40, 6>;    //< Overflow Enpoint Flag for Output Endpoints
        using TRNCOMPL0 = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< Transaction Complete 0 Flag
        using TRNCOMPL1 = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Transaction Complete 1 Flag
        using SETUP = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< SETUP Transaction Complete Flag
        using BANK = reg_field_t<BASE_ADDRESS + 0x0000, 0x08, 3>;    //< Bank Select
        using BUSNACK1 = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< Data Buffer 1 Not Acknowledge
        using BUSNACK0 = reg_field_t<BASE_ADDRESS + 0x0000, 0x02, 1>;    //< Data Buffer 0 Not Acknowledge
        using TOGGLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Data Toggle
    };

    /// Endpoint Control - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0001> {
        using TYPE = reg_field_t<BASE_ADDRESS + 0x0001, 0xC0, 6, EP_TYPEv>;    //< Endpoint Type
        using MULTIPKT = reg_field_t<BASE_ADDRESS + 0x0001, 0x20, 5>;    //< Multi Packet Transfer Enable
        using PINGPONG = reg_field_t<BASE_ADDRESS + 0x0001, 0x10, 4>;    //< Ping-Pong Enable
        using INTDSBL = reg_field_t<BASE_ADDRESS + 0x0001, 0x08, 3>;    //< Interrupt Disable
        using STALL = reg_field_t<BASE_ADDRESS + 0x0001, 0x04, 2>;    //< Data Stall
        using BUFSIZE = reg_field_t<BASE_ADDRESS + 0x0001, 0x07, 0, EP_BUFSIZEv>;    //< Data Buffer Size
    };

    /// USB Endpoint Counter - 2 bytes
    struct CNT : public reg16_t<BASE_ADDRESS + 0x0002> {
        using ZLP = reg_field_t<BASE_ADDRESS + 0x0002, 0x80, 7>;    //< Zero Length Packet
    };

    /// Data Pointer - 2 bytes
    struct DATAPTR : public reg16_t<BASE_ADDRESS + 0x0004> {
    };

    /// Auxiliary Data - 2 bytes
    struct AUXDATA : public reg16_t<BASE_ADDRESS + 0x0006> {
    };
};

/**
 * USB
 * Universal Serial Bus
 * Size: 60 bytes
 */
template <addressType BASE_ADDRESS>
struct USB_t {
    // Interrupt level
    enum class INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low level
        MED = 0x02, // Medium level
        HI = 0x03, // High level
    };

    // Interrupt level
    enum class INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low level
        MED = 0x02, // Medium level
        HI = 0x03, // High level
    };

    // USB ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        BUSEVENT = 0, // SOF, suspend, resume, reset bus event interrupts, crc, underflow, overflow and stall error interrupts
        TRNCOMPL = 1, // Transaction complete interrupt
    };

    /// Control Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x80, 7>;    //< USB Enable
        using SPEED = reg_field_t<BASE_ADDRESS + 0x0000, 0x40, 6>;    //< Speed Select
        using FIFOEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< USB FIFO Enable
        using STFRNUM = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Store Frame Number Enable
        using MAXEP = reg_field_t<BASE_ADDRESS + 0x0000, 0x0F, 0>;    //< Maximum Endpoint Addresses
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0001> {
        using PULLRST = reg_field_t<BASE_ADDRESS + 0x0001, 0x10, 4>;    //< Pull during Reset
        using RWAKEUP = reg_field_t<BASE_ADDRESS + 0x0001, 0x04, 2>;    //< Remote Wake-up
        using GNACK = reg_field_t<BASE_ADDRESS + 0x0001, 0x02, 1>;    //< Global NACK
        using ATTACH = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Attach
    };

    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0002> {
        using URESUME = reg_field_t<BASE_ADDRESS + 0x0002, 0x08, 3>;    //< Upstream Resume
        using RESUME = reg_field_t<BASE_ADDRESS + 0x0002, 0x04, 2>;    //< Resume
        using SUSPEND = reg_field_t<BASE_ADDRESS + 0x0002, 0x02, 1>;    //< Bus Suspended
        using BUSRST = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Bus Reset
    };

    /// Address Register - 1 bytes
    struct ADDR : public reg8_t<BASE_ADDRESS + 0x0003> {
        using ADDRf = reg_field_t<BASE_ADDRESS + 0x0003, 0x7F, 0>;    //< Device Address
    };

    /// FIFO Write Pointer Register - 1 bytes
    struct FIFOWP : public reg8_t<BASE_ADDRESS + 0x0004> {
        using FIFOWPf = reg_field_t<BASE_ADDRESS + 0x0004, 0x1F, 0>;    //< FIFO Write Pointer
    };

    /// FIFO Read Pointer Register - 1 bytes
    struct FIFORP : public reg8_t<BASE_ADDRESS + 0x0005> {
        using FIFORPf = reg_field_t<BASE_ADDRESS + 0x0005, 0x1F, 0>;    //< FIFO Read Pointer
    };

    /// Endpoint Configuration Table Pointer - 2 bytes
    struct EPPTR : public reg16_t<BASE_ADDRESS + 0x0006> {
    };

    /// Interrupt Control Register A - 1 bytes
    struct INTCTRLA : public reg8_t<BASE_ADDRESS + 0x0008> {
        using SOFIE = reg_field_t<BASE_ADDRESS + 0x0008, 0x80, 7>;    //< Start Of Frame Interrupt Enable
        using BUSEVIE = reg_field_t<BASE_ADDRESS + 0x0008, 0x40, 6>;    //< Bus Event Interrupt Enable
        using BUSERRIE = reg_field_t<BASE_ADDRESS + 0x0008, 0x20, 5>;    //< Bus Error Interrupt Enable
        using STALLIE = reg_field_t<BASE_ADDRESS + 0x0008, 0x10, 4>;    //< STALL Interrupt Enable
        using INTLVL = reg_field_t<BASE_ADDRESS + 0x0008, 0x03, 0, INTLVLv>;    //< Interrupt Level
    };

    /// Interrupt Control Register B - 1 bytes
    struct INTCTRLB : public reg8_t<BASE_ADDRESS + 0x0009> {
        using TRNIE = reg_field_t<BASE_ADDRESS + 0x0009, 0x02, 1>;    //< Transaction Complete Interrupt Enable
        using SETUPIE = reg_field_t<BASE_ADDRESS + 0x0009, 0x01, 0>;    //< SETUP Transaction Complete Interrupt Enable
    };

    /// Clear Interrupt Flag Register A - 1 bytes
    struct INTFLAGSACLR : public reg8_t<BASE_ADDRESS + 0x000A> {
        using SOFIF = reg_field_t<BASE_ADDRESS + 0x000A, 0x80, 7>;    //< Start Of Frame Interrupt Flag
        using SUSPENDIF = reg_field_t<BASE_ADDRESS + 0x000A, 0x40, 6>;    //< Suspend Interrupt Flag
        using RESUMEIF = reg_field_t<BASE_ADDRESS + 0x000A, 0x20, 5>;    //< Resume Interrupt Flag
        using RSTIF = reg_field_t<BASE_ADDRESS + 0x000A, 0x10, 4>;    //< Reset Interrupt Flag
        using CRCIF = reg_field_t<BASE_ADDRESS + 0x000A, 0x08, 3>;    //< Isochronous CRC Error Interrupt Flag
        using UNFIF = reg_field_t<BASE_ADDRESS + 0x000A, 0x04, 2>;    //< Underflow Interrupt Flag
        using OVFIF = reg_field_t<BASE_ADDRESS + 0x000A, 0x02, 1>;    //< Overflow Interrupt Flag
        using STALLIF = reg_field_t<BASE_ADDRESS + 0x000A, 0x01, 0>;    //< STALL Interrupt Flag
    };

    /// Set Interrupt Flag Register A - 1 bytes
    struct INTFLAGSASET : public reg8_t<BASE_ADDRESS + 0x000B> {
        using SOFIF = reg_field_t<BASE_ADDRESS + 0x000B, 0x80, 7>;    //< Start Of Frame Interrupt Flag
        using SUSPENDIF = reg_field_t<BASE_ADDRESS + 0x000B, 0x40, 6>;    //< Suspend Interrupt Flag
        using RESUMEIF = reg_field_t<BASE_ADDRESS + 0x000B, 0x20, 5>;    //< Resume Interrupt Flag
        using RSTIF = reg_field_t<BASE_ADDRESS + 0x000B, 0x10, 4>;    //< Reset Interrupt Flag
        using CRCIF = reg_field_t<BASE_ADDRESS + 0x000B, 0x08, 3>;    //< Isochronous CRC Error Interrupt Flag
        using UNFIF = reg_field_t<BASE_ADDRESS + 0x000B, 0x04, 2>;    //< Underflow Interrupt Flag
        using OVFIF = reg_field_t<BASE_ADDRESS + 0x000B, 0x02, 1>;    //< Overflow Interrupt Flag
        using STALLIF = reg_field_t<BASE_ADDRESS + 0x000B, 0x01, 0>;    //< STALL Interrupt Flag
    };

    /// Clear Interrupt Flag Register B - 1 bytes
    struct INTFLAGSBCLR : public reg8_t<BASE_ADDRESS + 0x000C> {
        using TRNIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x02, 1>;    //< Transaction Complete Interrupt Flag
        using SETUPIF = reg_field_t<BASE_ADDRESS + 0x000C, 0x01, 0>;    //< SETUP Transaction Complete Interrupt Flag
    };

    /// Set Interrupt Flag Register B - 1 bytes
    struct INTFLAGSBSET : public reg8_t<BASE_ADDRESS + 0x000D> {
        using TRNIF = reg_field_t<BASE_ADDRESS + 0x000D, 0x02, 1>;    //< Transaction Complete Interrupt Flag
        using SETUPIF = reg_field_t<BASE_ADDRESS + 0x000D, 0x01, 0>;    //< SETUP Transaction Complete Interrupt Flag
    };

    /// Calibration Byte 0 - 1 bytes
    struct CAL0 : public reg8_t<BASE_ADDRESS + 0x003A> {
    };

    /// Calibration Byte 1 - 1 bytes
    struct CAL1 : public reg8_t<BASE_ADDRESS + 0x003B> {
    };
};

/**
 * USB_EP_TABLE
 * USB Endpoint Table
 * Size: 274 bytes
 */
template <addressType BASE_ADDRESS>
struct USB_EP_TABLE_t {
    /// Frame Number Low Byte - 1 bytes
    struct FRAMENUML : public reg8_t<BASE_ADDRESS + 0x0110> {
    };

    /// Frame Number High Byte - 1 bytes
    struct FRAMENUMH : public reg8_t<BASE_ADDRESS + 0x0111> {
    };

    /// Endpoint 0
    USB_EP_t<BASE_ADDRESS + 0x0000> EP0OUT;

    /// Endpoint 0
    USB_EP_t<BASE_ADDRESS + 0x0008> EP0IN;

    /// Endpoint 1
    USB_EP_t<BASE_ADDRESS + 0x0010> EP1OUT;

    /// Endpoint 1
    USB_EP_t<BASE_ADDRESS + 0x0018> EP1IN;

    /// Endpoint 2
    USB_EP_t<BASE_ADDRESS + 0x0020> EP2OUT;

    /// Endpoint 2
    USB_EP_t<BASE_ADDRESS + 0x0028> EP2IN;

    /// Endpoint 3
    USB_EP_t<BASE_ADDRESS + 0x0030> EP3OUT;

    /// Endpoint 3
    USB_EP_t<BASE_ADDRESS + 0x0038> EP3IN;

    /// Endpoint 4
    USB_EP_t<BASE_ADDRESS + 0x0040> EP4OUT;

    /// Endpoint 4
    USB_EP_t<BASE_ADDRESS + 0x0048> EP4IN;

    /// Endpoint 5
    USB_EP_t<BASE_ADDRESS + 0x0050> EP5OUT;

    /// Endpoint 5
    USB_EP_t<BASE_ADDRESS + 0x0058> EP5IN;

    /// Endpoint 6
    USB_EP_t<BASE_ADDRESS + 0x0060> EP6OUT;

    /// Endpoint 6
    USB_EP_t<BASE_ADDRESS + 0x0068> EP6IN;

    /// Endpoint 7
    USB_EP_t<BASE_ADDRESS + 0x0070> EP7OUT;

    /// Endpoint 7
    USB_EP_t<BASE_ADDRESS + 0x0078> EP7IN;

    /// Endpoint 8
    USB_EP_t<BASE_ADDRESS + 0x0080> EP8OUT;

    /// Endpoint 8
    USB_EP_t<BASE_ADDRESS + 0x0088> EP8IN;

    /// Endpoint 9
    USB_EP_t<BASE_ADDRESS + 0x0090> EP9OUT;

    /// Endpoint 9
    USB_EP_t<BASE_ADDRESS + 0x0098> EP9IN;

    /// Endpoint 10
    USB_EP_t<BASE_ADDRESS + 0x00A0> EP10OUT;

    /// Endpoint 10
    USB_EP_t<BASE_ADDRESS + 0x00A8> EP10IN;

    /// Endpoint 11
    USB_EP_t<BASE_ADDRESS + 0x00B0> EP11OUT;

    /// Endpoint 11
    USB_EP_t<BASE_ADDRESS + 0x00B8> EP11IN;

    /// Endpoint 12
    USB_EP_t<BASE_ADDRESS + 0x00C0> EP12OUT;

    /// Endpoint 12
    USB_EP_t<BASE_ADDRESS + 0x00C8> EP12IN;

    /// Endpoint 13
    USB_EP_t<BASE_ADDRESS + 0x00D0> EP13OUT;

    /// Endpoint 13
    USB_EP_t<BASE_ADDRESS + 0x00D8> EP13IN;

    /// Endpoint 14
    USB_EP_t<BASE_ADDRESS + 0x00E0> EP14OUT;

    /// Endpoint 14
    USB_EP_t<BASE_ADDRESS + 0x00E8> EP14IN;

    /// Endpoint 15
    USB_EP_t<BASE_ADDRESS + 0x00F0> EP15OUT;

    /// Endpoint 15
    USB_EP_t<BASE_ADDRESS + 0x00F8> EP15IN;

};

} // namespace device
