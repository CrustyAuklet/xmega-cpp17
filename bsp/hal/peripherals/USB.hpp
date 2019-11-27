/**
 * XMEGAAU-USB (id I3005)
 * USB
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace USB {

    // Interrupt level
    enum class INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low level
        MED = 0x02, // Medium level
        HI = 0x03, // High level
    };

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

    // USB ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        BUSEVENT = 0, // SOF, suspend, resume, reset bus event interrupts, crc, underflow, overflow and stall error interrupts
        TRNCOMPL = 1, // Transaction complete interrupt
    };
}   // namespace USB

/**
 * USB_EP
 * USB Endpoint
 * Size: 8 bytes
 */
template <addressType BASE_ADDRESS>
struct USB_EP_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Endpoint Status - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<STATUS_t, 0x80, 7> STALLF = {};    //< Endpoint Stall Flag
        static constexpr bitfield_t<STATUS_t, 0x80, 7> CRC = {};    //< CRC Error Flag
        static constexpr bitfield_t<STATUS_t, 0x40, 6> UNF = {};    //< Underflow Enpoint FLag
        static constexpr bitfield_t<STATUS_t, 0x40, 6> OVF = {};    //< Overflow Enpoint Flag for Output Endpoints
        static constexpr bitfield_t<STATUS_t, 0x20, 5> TRNCOMPL0 = {};    //< Transaction Complete 0 Flag
        static constexpr bitfield_t<STATUS_t, 0x10, 4> TRNCOMPL1 = {};    //< Transaction Complete 1 Flag
        static constexpr bitfield_t<STATUS_t, 0x10, 4> SETUP = {};    //< SETUP Transaction Complete Flag
        static constexpr bitfield_t<STATUS_t, 0x08, 3> BANK = {};    //< Bank Select
        static constexpr bitfield_t<STATUS_t, 0x04, 2> BUSNACK1 = {};    //< Data Buffer 1 Not Acknowledge
        static constexpr bitfield_t<STATUS_t, 0x02, 1> BUSNACK0 = {};    //< Data Buffer 0 Not Acknowledge
        static constexpr bitfield_t<STATUS_t, 0x01, 0> TOGGLE = {};    //< Data Toggle
    } STATUS = {};

    /// Endpoint Control - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<CTRL_t, 0xC0, 6, EP_TYPEv> TYPE = {};    //< Endpoint Type
        static constexpr bitfield_t<CTRL_t, 0x20, 5> MULTIPKT = {};    //< Multi Packet Transfer Enable
        static constexpr bitfield_t<CTRL_t, 0x10, 4> PINGPONG = {};    //< Ping-Pong Enable
        static constexpr bitfield_t<CTRL_t, 0x08, 3> INTDSBL = {};    //< Interrupt Disable
        static constexpr bitfield_t<CTRL_t, 0x04, 2> STALL = {};    //< Data Stall
        static constexpr bitfield_t<CTRL_t, 0x07, 0, EP_BUFSIZEv> BUFSIZE = {};    //< Data Buffer Size
    } CTRL = {};

    /// USB Endpoint Counter - 2 bytes
    static constexpr struct CNT_t : reg_t<uint16_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<CNT_t, 0x8000, 15> ZLP = {};    //< Zero Length Packet
    } CNT = {};

    /// Data Pointer - 2 bytes
    static constexpr struct DATAPTR_t : reg_t<uint16_t, BASE_ADDRESS + 0x0004> {
    } DATAPTR = {};

    /// Auxiliary Data - 2 bytes
    static constexpr struct AUXDATA_t : reg_t<uint16_t, BASE_ADDRESS + 0x0006> {
    } AUXDATA = {};

};

/**
 * USB
 * Universal Serial Bus
 * Size: 60 bytes
 */
template <addressType BASE_ADDRESS>
struct USB_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRLA_t, 0x80, 7> ENABLE = {};    //< USB Enable
        static constexpr bitfield_t<CTRLA_t, 0x40, 6> SPEED = {};    //< Speed Select
        static constexpr bitfield_t<CTRLA_t, 0x20, 5> FIFOEN = {};    //< USB FIFO Enable
        static constexpr bitfield_t<CTRLA_t, 0x10, 4> STFRNUM = {};    //< Store Frame Number Enable
        static constexpr bitfield_t<CTRLA_t, 0x0F, 0> MAXEP = {};    //< Maximum Endpoint Addresses
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<CTRLB_t, 0x10, 4> PULLRST = {};    //< Pull during Reset
        static constexpr bitfield_t<CTRLB_t, 0x04, 2> RWAKEUP = {};    //< Remote Wake-up
        static constexpr bitfield_t<CTRLB_t, 0x02, 1> GNACK = {};    //< Global NACK
        static constexpr bitfield_t<CTRLB_t, 0x01, 0> ATTACH = {};    //< Attach
    } CTRLB = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<STATUS_t, 0x08, 3> URESUME = {};    //< Upstream Resume
        static constexpr bitfield_t<STATUS_t, 0x04, 2> RESUME = {};    //< Resume
        static constexpr bitfield_t<STATUS_t, 0x02, 1> SUSPEND = {};    //< Bus Suspended
        static constexpr bitfield_t<STATUS_t, 0x01, 0> BUSRST = {};    //< Bus Reset
    } STATUS = {};

    /// Address Register - 1 bytes
    static constexpr struct ADDR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<ADDR_t, 0x7F, 0> ADDR = {};    //< Device Address
    } ADDR = {};

    /// FIFO Write Pointer Register - 1 bytes
    static constexpr struct FIFOWP_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        static constexpr bitfield_t<FIFOWP_t, 0x1F, 0> FIFOWP = {};    //< FIFO Write Pointer
    } FIFOWP = {};

    /// FIFO Read Pointer Register - 1 bytes
    static constexpr struct FIFORP_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        static constexpr bitfield_t<FIFORP_t, 0x1F, 0> FIFORP = {};    //< FIFO Read Pointer
    } FIFORP = {};

    /// Endpoint Configuration Table Pointer - 2 bytes
    static constexpr struct EPPTR_t : reg_t<uint16_t, BASE_ADDRESS + 0x0006> {
    } EPPTR = {};

    /// Interrupt Control Register A - 1 bytes
    static constexpr struct INTCTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        static constexpr bitfield_t<INTCTRLA_t, 0x80, 7> SOFIE = {};    //< Start Of Frame Interrupt Enable
        static constexpr bitfield_t<INTCTRLA_t, 0x40, 6> BUSEVIE = {};    //< Bus Event Interrupt Enable
        static constexpr bitfield_t<INTCTRLA_t, 0x20, 5> BUSERRIE = {};    //< Bus Error Interrupt Enable
        static constexpr bitfield_t<INTCTRLA_t, 0x10, 4> STALLIE = {};    //< STALL Interrupt Enable
        static constexpr bitfield_t<INTCTRLA_t, 0x03, 0, INTLVLv> INTLVL = {};    //< Interrupt Level
    } INTCTRLA = {};

    /// Interrupt Control Register B - 1 bytes
    static constexpr struct INTCTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        static constexpr bitfield_t<INTCTRLB_t, 0x02, 1> TRNIE = {};    //< Transaction Complete Interrupt Enable
        static constexpr bitfield_t<INTCTRLB_t, 0x01, 0> SETUPIE = {};    //< SETUP Transaction Complete Interrupt Enable
    } INTCTRLB = {};

    /// Clear Interrupt Flag Register A - 1 bytes
    static constexpr struct INTFLAGSACLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        static constexpr bitfield_t<INTFLAGSACLR_t, 0x80, 7> SOFIF = {};    //< Start Of Frame Interrupt Flag
        static constexpr bitfield_t<INTFLAGSACLR_t, 0x40, 6> SUSPENDIF = {};    //< Suspend Interrupt Flag
        static constexpr bitfield_t<INTFLAGSACLR_t, 0x20, 5> RESUMEIF = {};    //< Resume Interrupt Flag
        static constexpr bitfield_t<INTFLAGSACLR_t, 0x10, 4> RSTIF = {};    //< Reset Interrupt Flag
        static constexpr bitfield_t<INTFLAGSACLR_t, 0x08, 3> CRCIF = {};    //< Isochronous CRC Error Interrupt Flag
        static constexpr bitfield_t<INTFLAGSACLR_t, 0x04, 2> UNFIF = {};    //< Underflow Interrupt Flag
        static constexpr bitfield_t<INTFLAGSACLR_t, 0x02, 1> OVFIF = {};    //< Overflow Interrupt Flag
        static constexpr bitfield_t<INTFLAGSACLR_t, 0x01, 0> STALLIF = {};    //< STALL Interrupt Flag
    } INTFLAGSACLR = {};

    /// Set Interrupt Flag Register A - 1 bytes
    static constexpr struct INTFLAGSASET_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        static constexpr bitfield_t<INTFLAGSASET_t, 0x80, 7> SOFIF = {};    //< Start Of Frame Interrupt Flag
        static constexpr bitfield_t<INTFLAGSASET_t, 0x40, 6> SUSPENDIF = {};    //< Suspend Interrupt Flag
        static constexpr bitfield_t<INTFLAGSASET_t, 0x20, 5> RESUMEIF = {};    //< Resume Interrupt Flag
        static constexpr bitfield_t<INTFLAGSASET_t, 0x10, 4> RSTIF = {};    //< Reset Interrupt Flag
        static constexpr bitfield_t<INTFLAGSASET_t, 0x08, 3> CRCIF = {};    //< Isochronous CRC Error Interrupt Flag
        static constexpr bitfield_t<INTFLAGSASET_t, 0x04, 2> UNFIF = {};    //< Underflow Interrupt Flag
        static constexpr bitfield_t<INTFLAGSASET_t, 0x02, 1> OVFIF = {};    //< Overflow Interrupt Flag
        static constexpr bitfield_t<INTFLAGSASET_t, 0x01, 0> STALLIF = {};    //< STALL Interrupt Flag
    } INTFLAGSASET = {};

    /// Clear Interrupt Flag Register B - 1 bytes
    static constexpr struct INTFLAGSBCLR_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        static constexpr bitfield_t<INTFLAGSBCLR_t, 0x02, 1> TRNIF = {};    //< Transaction Complete Interrupt Flag
        static constexpr bitfield_t<INTFLAGSBCLR_t, 0x01, 0> SETUPIF = {};    //< SETUP Transaction Complete Interrupt Flag
    } INTFLAGSBCLR = {};

    /// Set Interrupt Flag Register B - 1 bytes
    static constexpr struct INTFLAGSBSET_t : reg_t<uint8_t, BASE_ADDRESS + 0x000D> {
        static constexpr bitfield_t<INTFLAGSBSET_t, 0x02, 1> TRNIF = {};    //< Transaction Complete Interrupt Flag
        static constexpr bitfield_t<INTFLAGSBSET_t, 0x01, 0> SETUPIF = {};    //< SETUP Transaction Complete Interrupt Flag
    } INTFLAGSBSET = {};

    /// Calibration Byte 0 - 1 bytes
    static constexpr struct CAL0_t : reg_t<uint8_t, BASE_ADDRESS + 0x003A> {
    } CAL0 = {};

    /// Calibration Byte 1 - 1 bytes
    static constexpr struct CAL1_t : reg_t<uint8_t, BASE_ADDRESS + 0x003B> {
    } CAL1 = {};

};

/**
 * USB_EP_TABLE
 * USB Endpoint Table
 * Size: 274 bytes
 */
template <addressType BASE_ADDRESS>
struct USB_EP_TABLE_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Frame Number Low Byte - 1 bytes
    static constexpr struct FRAMENUML_t : reg_t<uint8_t, BASE_ADDRESS + 0x0110> {
    } FRAMENUML = {};

    /// Frame Number High Byte - 1 bytes
    static constexpr struct FRAMENUMH_t : reg_t<uint8_t, BASE_ADDRESS + 0x0111> {
    } FRAMENUMH = {};

    /// Endpoint 0
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0000> EP0OUT = {};

    /// Endpoint 0
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0008> EP0IN = {};

    /// Endpoint 1
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0010> EP1OUT = {};

    /// Endpoint 1
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0018> EP1IN = {};

    /// Endpoint 2
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0020> EP2OUT = {};

    /// Endpoint 2
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0028> EP2IN = {};

    /// Endpoint 3
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0030> EP3OUT = {};

    /// Endpoint 3
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0038> EP3IN = {};

    /// Endpoint 4
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0040> EP4OUT = {};

    /// Endpoint 4
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0048> EP4IN = {};

    /// Endpoint 5
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0050> EP5OUT = {};

    /// Endpoint 5
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0058> EP5IN = {};

    /// Endpoint 6
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0060> EP6OUT = {};

    /// Endpoint 6
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0068> EP6IN = {};

    /// Endpoint 7
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0070> EP7OUT = {};

    /// Endpoint 7
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0078> EP7IN = {};

    /// Endpoint 8
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0080> EP8OUT = {};

    /// Endpoint 8
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0088> EP8IN = {};

    /// Endpoint 9
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0090> EP9OUT = {};

    /// Endpoint 9
    static constexpr USB_EP_t<BASE_ADDRESS + 0x0098> EP9IN = {};

    /// Endpoint 10
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00A0> EP10OUT = {};

    /// Endpoint 10
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00A8> EP10IN = {};

    /// Endpoint 11
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00B0> EP11OUT = {};

    /// Endpoint 11
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00B8> EP11IN = {};

    /// Endpoint 12
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00C0> EP12OUT = {};

    /// Endpoint 12
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00C8> EP12IN = {};

    /// Endpoint 13
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00D0> EP13OUT = {};

    /// Endpoint 13
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00D8> EP13IN = {};

    /// Endpoint 14
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00E0> EP14OUT = {};

    /// Endpoint 14
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00E8> EP14IN = {};

    /// Endpoint 15
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00F0> EP15OUT = {};

    /// Endpoint 15
    static constexpr USB_EP_t<BASE_ADDRESS + 0x00F8> EP15IN = {};

};

} // namespace device
