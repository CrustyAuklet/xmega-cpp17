/**
 * XMEGAAU-TWI (id I6089)
 * Two-Wire Interface
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

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
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRLA_t, 7, 6, TWI::MASTER_INTLVLv> INTLVL = {};    //< Interrupt Level
        static constexpr bitfield_t<CTRLA_t, 5, 5, bool> RIEN = {};    //< Read Interrupt Enable
        static constexpr bitfield_t<CTRLA_t, 4, 4, bool> WIEN = {};    //< Write Interrupt Enable
        static constexpr bitfield_t<CTRLA_t, 3, 3, bool> ENABLE = {};    //< Enable TWI Master
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<CTRLB_t, 3, 2, TWI::MASTER_TIMEOUTv> TIMEOUT = {};    //< Inactive Bus Timeout
        static constexpr bitfield_t<CTRLB_t, 1, 1, bool> QCEN = {};    //< Quick Command Enable
        static constexpr bitfield_t<CTRLB_t, 0, 0, bool> SMEN = {};    //< Smart Mode Enable
    } CTRLB = {};

    /// Control Register C - 1 bytes
    static constexpr struct CTRLC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<CTRLC_t, 2, 2, bool> ACKACT = {};    //< Acknowledge Action
        static constexpr bitfield_t<CTRLC_t, 1, 0, TWI::MASTER_CMDv> CMD = {};    //< Command
    } CTRLC = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<STATUS_t, 7, 7, bool> RIF = {};    //< Read Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 6, 6, bool> WIF = {};    //< Write Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 5, 5, bool> CLKHOLD = {};    //< Clock Hold
        static constexpr bitfield_t<STATUS_t, 4, 4, bool> RXACK = {};    //< Received Acknowledge
        static constexpr bitfield_t<STATUS_t, 3, 3, bool> ARBLOST = {};    //< Arbitration Lost
        static constexpr bitfield_t<STATUS_t, 2, 2, bool> BUSERR = {};    //< Bus Error
        static constexpr bitfield_t<STATUS_t, 1, 0, TWI::MASTER_BUSSTATEv> BUSSTATE = {};    //< Bus State
    } STATUS = {};

    /// Baurd Rate Control Register - 1 bytes
    static constexpr struct BAUD_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
    } BAUD = {};

    /// Address Register - 1 bytes
    static constexpr struct ADDR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
    } ADDR = {};

    /// Data Register - 1 bytes
    static constexpr struct DATA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
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
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRLA_t, 7, 6, TWI::SLAVE_INTLVLv> INTLVL = {};    //< Interrupt Level
        static constexpr bitfield_t<CTRLA_t, 5, 5, bool> DIEN = {};    //< Data Interrupt Enable
        static constexpr bitfield_t<CTRLA_t, 4, 4, bool> APIEN = {};    //< Address/Stop Interrupt Enable
        static constexpr bitfield_t<CTRLA_t, 3, 3, bool> ENABLE = {};    //< Enable TWI Slave
        static constexpr bitfield_t<CTRLA_t, 2, 2, bool> PIEN = {};    //< Stop Interrupt Enable
        static constexpr bitfield_t<CTRLA_t, 1, 1, bool> PMEN = {};    //< Promiscuous Mode Enable
        static constexpr bitfield_t<CTRLA_t, 0, 0, bool> SMEN = {};    //< Smart Mode Enable
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<CTRLB_t, 2, 2, bool> ACKACT = {};    //< Acknowledge Action
        static constexpr bitfield_t<CTRLB_t, 1, 0, TWI::SLAVE_CMDv> CMD = {};    //< Command
    } CTRLB = {};

    /// Status Register - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<STATUS_t, 7, 7, bool> DIF = {};    //< Data Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 6, 6, bool> APIF = {};    //< Address/Stop Interrupt Flag
        static constexpr bitfield_t<STATUS_t, 5, 5, bool> CLKHOLD = {};    //< Clock Hold
        static constexpr bitfield_t<STATUS_t, 4, 4, bool> RXACK = {};    //< Received Acknowledge
        static constexpr bitfield_t<STATUS_t, 3, 3, bool> COLL = {};    //< Collision
        static constexpr bitfield_t<STATUS_t, 2, 2, bool> BUSERR = {};    //< Bus Error
        static constexpr bitfield_t<STATUS_t, 1, 1, bool> DIR = {};    //< Read/Write Direction
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> AP = {};    //< Slave Address or Stop
    } STATUS = {};

    /// Address Register - 1 bytes
    static constexpr struct ADDR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
    } ADDR = {};

    /// Data Register - 1 bytes
    static constexpr struct DATA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
    } DATA = {};

    /// Address Mask Register - 1 bytes
    static constexpr struct ADDRMASK_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
        static constexpr bitfield_t<ADDRMASK_t, 7, 1> ADDRMASK = {};    //< Address Mask
        static constexpr bitfield_t<ADDRMASK_t, 0, 0, bool> ADDREN = {};    //< Address Enable
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
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRL_t, 2, 1, TWI::SDAHOLDv> SDAHOLD = {};    //< SDA Hold Time Enable
        static constexpr bitfield_t<CTRL_t, 0, 0, bool> EDIEN = {};    //< External Driver Interface Enable
    } CTRL = {};

    /// TWI master module
    static constexpr TWI_MASTER_t<BASE_ADDRESS + 0x0001> MASTER = {};

    /// TWI slave module
    static constexpr TWI_SLAVE_t<BASE_ADDRESS + 0x0008> SLAVE = {};

    // TWI ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        TWIS = 0, // TWI Slave Interrupt
        TWIM = 1, // TWI Master Interrupt
    };
};

} // namespace sfr
