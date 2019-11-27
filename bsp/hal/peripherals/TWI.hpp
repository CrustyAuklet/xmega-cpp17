/**
 * XMEGAAU-TWI (id I6089)
 * Two-Wire Interface
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace TWI {

    // SDA Hold Time
    enum class SDAHOLDv : uint8_t {
        OFF = 0x00, // SDA Hold Time off
        _50NS = 0x01, // SDA Hold Time 50 ns
        _300NS = 0x02, // SDA Hold Time 300 ns
        _400NS = 0x03, // SDA Hold Time 400 ns
    };

    // Master Interrupt Level
    enum class MASTER_INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Inactive Timeout
    enum class MASTER_TIMEOUTv : uint8_t {
        DISABLED = 0x00, // Bus Timeout Disabled
        _50US = 0x01, // 50 Microseconds
        _100US = 0x02, // 100 Microseconds
        _200US = 0x03, // 200 Microseconds
    };

    // Master Command
    enum class MASTER_CMDv : uint8_t {
        NOACT = 0x00, // No Action
        REPSTART = 0x01, // Issue Repeated Start Condition
        RECVTRANS = 0x02, // Receive or Transmit Data
        STOP = 0x03, // Issue Stop Condition
    };

    // Master Bus State
    enum class MASTER_BUSSTATEv : uint8_t {
        UNKNOWN = 0x00, // Unknown Bus State
        IDLE = 0x01, // Bus is Idle
        OWNER = 0x02, // This Module Controls The Bus
        BUSY = 0x03, // The Bus is Busy
    };

    // Slave Interrupt Level
    enum class SLAVE_INTLVLv : uint8_t {
        OFF = 0x00, // Interrupt Disabled
        LO = 0x01, // Low Level
        MED = 0x02, // Medium Level
        HI = 0x03, // High Level
    };

    // Slave Command
    enum class SLAVE_CMDv : uint8_t {
        NOACT = 0x00, // No Action
        COMPTRANS = 0x02, // Used To Complete a Transaction
        RESPONSE = 0x03, // Used in Response to Address/Data Interrupt
    };

    // TWI ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        TWIS = 0, // TWI Slave Interrupt
        TWIM = 1, // TWI Master Interrupt
    };
}   // namespace TWI

/**
 * TWI_MASTER
 * 
 * Size: 7 bytes
 */
template <addressType BASE_ADDRESS>
struct TWI_MASTER_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRLA_t, 0xC0, 6, MASTER_INTLVLv> INTLVL = {};    //< Interrupt Level
        static constexpr bitfield_t<CTRLA_t, 0x20, 5> RIEN = {};    //< Read Interrupt Enable
        static constexpr bitfield_t<CTRLA_t, 0x10, 4> WIEN = {};    //< Write Interrupt Enable
        static constexpr bitfield_t<CTRLA_t, 0x08, 3> ENABLE = {};    //< Enable TWI Master
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<CTRLB_t, 0x0C, 2, MASTER_TIMEOUTv> TIMEOUT = {};    //< Inactive Bus Timeout
        static constexpr bitfield_t<CTRLB_t, 0x02, 1> QCEN = {};    //< Quick Command Enable
        static constexpr bitfield_t<CTRLB_t, 0x01, 0> SMEN = {};    //< Smart Mode Enable
    } CTRLB = {};

    /// Control Register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<CTRLC_t, 0x04, 2> ACKACT = {};    //< Acknowledge Action
        static constexpr bitfield_t<CTRLC_t, 0x03, 0, MASTER_CMDv> CMD = {};    //< Command
    } CTRLC = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<STATUS_t, 0x80, 7> RIF = {};    //< Read Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 0x40, 6> WIF = {};    //< Write Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 0x20, 5> CLKHOLD = {};    //< Clock Hold
        static constexpr bitfield_t<STATUS_t, 0x10, 4> RXACK = {};    //< Received Acknowledge
        static constexpr bitfield_t<STATUS_t, 0x08, 3> ARBLOST = {};    //< Arbitration Lost
        static constexpr bitfield_t<STATUS_t, 0x04, 2> BUSERR = {};    //< Bus Error
        static constexpr bitfield_t<STATUS_t, 0x03, 0, MASTER_BUSSTATEv> BUSSTATE = {};    //< Bus State
    } STATUS = {};

    /// Baurd Rate Control Register - 1 bytes
    static constexpr struct BAUD_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
    } BAUD = {};

    /// Address Register - 1 bytes
    static constexpr struct ADDR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
    } ADDR = {};

    /// Data Register - 1 bytes
    static constexpr struct DATA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
    } DATA = {};

};

/**
 * TWI_SLAVE
 * 
 * Size: 6 bytes
 */
template <addressType BASE_ADDRESS>
struct TWI_SLAVE_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRLA_t, 0xC0, 6, SLAVE_INTLVLv> INTLVL = {};    //< Interrupt Level
        static constexpr bitfield_t<CTRLA_t, 0x20, 5> DIEN = {};    //< Data Interrupt Enable
        static constexpr bitfield_t<CTRLA_t, 0x10, 4> APIEN = {};    //< Address/Stop Interrupt Enable
        static constexpr bitfield_t<CTRLA_t, 0x08, 3> ENABLE = {};    //< Enable TWI Slave
        static constexpr bitfield_t<CTRLA_t, 0x04, 2> PIEN = {};    //< Stop Interrupt Enable
        static constexpr bitfield_t<CTRLA_t, 0x02, 1> PMEN = {};    //< Promiscuous Mode Enable
        static constexpr bitfield_t<CTRLA_t, 0x01, 0> SMEN = {};    //< Smart Mode Enable
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<CTRLB_t, 0x04, 2> ACKACT = {};    //< Acknowledge Action
        static constexpr bitfield_t<CTRLB_t, 0x03, 0, SLAVE_CMDv> CMD = {};    //< Command
    } CTRLB = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<STATUS_t, 0x80, 7> DIF = {};    //< Data Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 0x40, 6> APIF = {};    //< Address/Stop Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 0x20, 5> CLKHOLD = {};    //< Clock Hold
        static constexpr bitfield_t<STATUS_t, 0x10, 4> RXACK = {};    //< Received Acknowledge
        static constexpr bitfield_t<STATUS_t, 0x08, 3> COLL = {};    //< Collision
        static constexpr bitfield_t<STATUS_t, 0x04, 2> BUSERR = {};    //< Bus Error
        static constexpr bitfield_t<STATUS_t, 0x02, 1> DIR = {};    //< Read/Write Direction
        static constexpr bitfield_t<STATUS_t, 0x01, 0> AP = {};    //< Slave Address or Stop
    } STATUS = {};

    /// Address Register - 1 bytes
    static constexpr struct ADDR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
    } ADDR = {};

    /// Data Register - 1 bytes
    static constexpr struct DATA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
    } DATA = {};

    /// Address Mask Register - 1 bytes
    static constexpr struct ADDRMASK_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        static constexpr bitfield_t<ADDRMASK_t, 0xFE, 1> ADDRMASK = {};    //< Address Mask
        static constexpr bitfield_t<ADDRMASK_t, 0x01, 0> ADDREN = {};    //< Address Enable
    } ADDRMASK = {};

};

/**
 * TWI
 * Two-Wire Interface
 * Size: 14 bytes
 */
template <addressType BASE_ADDRESS>
struct TWI_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// TWI Common Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        static constexpr bitfield_t<CTRL_t, 0x06, 1, SDAHOLDv> SDAHOLD = {};    //< SDA Hold Time Enable
        static constexpr bitfield_t<CTRL_t, 0x01, 0> EDIEN = {};    //< External Driver Interface Enable
    } CTRL = {};

    /// TWI master module
    static constexpr TWI_MASTER_t<BASE_ADDRESS + 0x0001> MASTER = {};

    /// TWI slave module
    static constexpr TWI_SLAVE_t<BASE_ADDRESS + 0x0008> SLAVE = {};

};

} // namespace device
