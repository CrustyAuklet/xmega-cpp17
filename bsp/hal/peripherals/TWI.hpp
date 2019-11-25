/**
 * XMEGAAU-TWI (id I6089)
 * Two-Wire Interface
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * TWI_MASTER
 *
 * Size: 7 bytes
 */
template <addressType BASE_ADDRESS>
struct TWI_MASTER_t {
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

    /// Control Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using INTLVL = reg_field_t<BASE_ADDRESS + 0x0000, 0xC0, 6, MASTER_INTLVLv>;    //< Interrupt Level
        using RIEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< Read Interrupt Enable
        using WIEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Write Interrupt Enable
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x08, 3>;    //< Enable TWI Master
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0001> {
        using TIMEOUT = reg_field_t<BASE_ADDRESS + 0x0001, 0x0C, 2, MASTER_TIMEOUTv>;    //< Inactive Bus Timeout
        using QCEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x02, 1>;    //< Quick Command Enable
        using SMEN = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Smart Mode Enable
    };

    /// Control Register C - 1 bytes
    struct CTRLC : public reg8_t<BASE_ADDRESS + 0x0002> {
        using ACKACT = reg_field_t<BASE_ADDRESS + 0x0002, 0x04, 2>;    //< Acknowledge Action
        using CMD = reg_field_t<BASE_ADDRESS + 0x0002, 0x03, 0, MASTER_CMDv>;    //< Command
    };

    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0003> {
        using RIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x80, 7>;    //< Read Interrupt Flag
        using WIF = reg_field_t<BASE_ADDRESS + 0x0003, 0x40, 6>;    //< Write Interrupt Flag
        using CLKHOLD = reg_field_t<BASE_ADDRESS + 0x0003, 0x20, 5>;    //< Clock Hold
        using RXACK = reg_field_t<BASE_ADDRESS + 0x0003, 0x10, 4>;    //< Received Acknowledge
        using ARBLOST = reg_field_t<BASE_ADDRESS + 0x0003, 0x08, 3>;    //< Arbitration Lost
        using BUSERR = reg_field_t<BASE_ADDRESS + 0x0003, 0x04, 2>;    //< Bus Error
        using BUSSTATE = reg_field_t<BASE_ADDRESS + 0x0003, 0x03, 0, MASTER_BUSSTATEv>;    //< Bus State
    };

    /// Baurd Rate Control Register - 1 bytes
    struct BAUD : public reg8_t<BASE_ADDRESS + 0x0004> {
    };

    /// Address Register - 1 bytes
    struct ADDR : public reg8_t<BASE_ADDRESS + 0x0005> {
    };

    /// Data Register - 1 bytes
    struct DATA : public reg8_t<BASE_ADDRESS + 0x0006> {
    };
};

/**
 * TWI_SLAVE
 *
 * Size: 6 bytes
 */
template <addressType BASE_ADDRESS>
struct TWI_SLAVE_t {
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

    /// Control Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x0000> {
        using INTLVL = reg_field_t<BASE_ADDRESS + 0x0000, 0xC0, 6, SLAVE_INTLVLv>;    //< Interrupt Level
        using DIEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x20, 5>;    //< Data Interrupt Enable
        using APIEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< Address/Stop Interrupt Enable
        using ENABLE = reg_field_t<BASE_ADDRESS + 0x0000, 0x08, 3>;    //< Enable TWI Slave
        using PIEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< Stop Interrupt Enable
        using PMEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x02, 1>;    //< Promiscuous Mode Enable
        using SMEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< Smart Mode Enable
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x0001> {
        using ACKACT = reg_field_t<BASE_ADDRESS + 0x0001, 0x04, 2>;    //< Acknowledge Action
        using CMD = reg_field_t<BASE_ADDRESS + 0x0001, 0x03, 0, SLAVE_CMDv>;    //< Command
    };

    /// Status Register - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x0002> {
        using DIF = reg_field_t<BASE_ADDRESS + 0x0002, 0x80, 7>;    //< Data Interrupt Flag
        using APIF = reg_field_t<BASE_ADDRESS + 0x0002, 0x40, 6>;    //< Address/Stop Interrupt Flag
        using CLKHOLD = reg_field_t<BASE_ADDRESS + 0x0002, 0x20, 5>;    //< Clock Hold
        using RXACK = reg_field_t<BASE_ADDRESS + 0x0002, 0x10, 4>;    //< Received Acknowledge
        using COLL = reg_field_t<BASE_ADDRESS + 0x0002, 0x08, 3>;    //< Collision
        using BUSERR = reg_field_t<BASE_ADDRESS + 0x0002, 0x04, 2>;    //< Bus Error
        using DIR = reg_field_t<BASE_ADDRESS + 0x0002, 0x02, 1>;    //< Read/Write Direction
        using AP = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Slave Address or Stop
    };

    /// Address Register - 1 bytes
    struct ADDR : public reg8_t<BASE_ADDRESS + 0x0003> {
    };

    /// Data Register - 1 bytes
    struct DATA : public reg8_t<BASE_ADDRESS + 0x0004> {
    };

    /// Address Mask Register - 1 bytes
    struct ADDRMASK : public reg8_t<BASE_ADDRESS + 0x0005> {
        using ADDRMASKf = reg_field_t<BASE_ADDRESS + 0x0005, 0xFE, 1>;    //< Address Mask
        using ADDREN = reg_field_t<BASE_ADDRESS + 0x0005, 0x01, 0>;    //< Address Enable
    };
};

/**
 * TWI
 * Two-Wire Interface
 * Size: 14 bytes
 */
template <addressType BASE_ADDRESS>
struct TWI_t {

    // SDA Hold Time
    enum class SDAHOLDv : uint8_t {
        OFF = 0x00, // SDA Hold Time off
        _50NS = 0x01, // SDA Hold Time 50 ns
        _300NS = 0x02, // SDA Hold Time 300 ns
        _400NS = 0x03, // SDA Hold Time 400 ns
    };

    // TWI ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        TWIS = 0, // TWI Slave Interrupt
        TWIM = 1, // TWI Master Interrupt
    };

    /// TWI Common Control Register - 1 bytes
    struct CTRL : public reg8_t<BASE_ADDRESS + 0x0000> {
        using SDAHOLD = reg_field_t<BASE_ADDRESS + 0x0000, 0x06, 1, SDAHOLDv>;    //< SDA Hold Time Enable
        using EDIEN = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< External Driver Interface Enable
    };
    /// TWI master module
    TWI_MASTER_t<BASE_ADDRESS + 0x0001> MASTER;

    /// TWI slave module
    TWI_SLAVE_t<BASE_ADDRESS + 0x0008> SLAVE;

};

} // namespace device
