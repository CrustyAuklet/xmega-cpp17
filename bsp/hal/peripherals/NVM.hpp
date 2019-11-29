/**
 * XMEGAAU-NVM (id I6076)
 * Non Volatile Memory Controller
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace NVM {

    // NVM Command
    enum class CMDv : uint8_t {
        NO_OPERATION = 0x00, // Noop/Ordinary LPM
        READ_USER_SIG_ROW = 0x01, // Read user signature row
        READ_CALIB_ROW = 0x02, // Read calibration row
        READ_EEPROM = 0x06, // Read EEPROM
        READ_FUSES = 0x07, // Read fuse byte
        WRITE_LOCK_BITS = 0x08, // Write lock bits
        ERASE_USER_SIG_ROW = 0x18, // Erase user signature row
        WRITE_USER_SIG_ROW = 0x1A, // Write user signature row
        ERASE_APP = 0x20, // Erase Application Section
        ERASE_APP_PAGE = 0x22, // Erase Application Section page
        LOAD_FLASH_BUFFER = 0x23, // Load Flash page buffer
        WRITE_APP_PAGE = 0x24, // Write Application Section page
        ERASE_WRITE_APP_PAGE = 0x25, // Erase-and-write Application Section page
        ERASE_FLASH_BUFFER = 0x26, // Erase/flush Flash page buffer
        ERASE_BOOT_PAGE = 0x2A, // Erase Boot Section page
        ERASE_FLASH_PAGE = 0x2B, // Erase Flash Page
        WRITE_BOOT_PAGE = 0x2C, // Write Boot Section page
        ERASE_WRITE_BOOT_PAGE = 0x2D, // Erase-and-write Boot Section page
        WRITE_FLASH_PAGE = 0x2E, // Write Flash Page
        ERASE_WRITE_FLASH_PAGE = 0x2F, // Erase-and-write Flash Page
        ERASE_EEPROM = 0x30, // Erase EEPROM
        ERASE_EEPROM_PAGE = 0x32, // Erase EEPROM page
        LOAD_EEPROM_BUFFER = 0x33, // Load EEPROM page buffer
        WRITE_EEPROM_PAGE = 0x34, // Write EEPROM page
        ERASE_WRITE_EEPROM_PAGE = 0x35, // Erase-and-write EEPROM page
        ERASE_EEPROM_BUFFER = 0x36, // Erase/flush EEPROM page buffer
        APP_CRC = 0x38, // Application section CRC
        BOOT_CRC = 0x39, //  Boot Section CRC
        FLASH_RANGE_CRC = 0x3A, // Flash Range CRC
        CHIP_ERASE = 0x40, // Erase Chip
        READ_NVM = 0x43, // Read NVM
        WRITE_FUSE = 0x4C, // Write Fuse byte
        ERASE_BOOT = 0x68, // Erase Boot Section
        FLASH_CRC = 0x78, // Flash CRC
    };
    // SPM ready interrupt level
    enum class SPMLVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low level
        MED = 0x02, // Medium level
        HI = 0x03, // High level
    };
    // EEPROM ready interrupt level
    enum class EELVLv : uint8_t {
        OFF = 0x00, // Interrupt disabled
        LO = 0x01, // Low level
        MED = 0x02, // Medium level
        HI = 0x03, // High level
    };
    // Boot lock bits - boot setcion
    enum class BLBBv : uint8_t {
        RWLOCK = 0x00, // Read and write not allowed
        RLOCK = 0x01, // Read not allowed
        WLOCK = 0x02, // Write not allowed
        NOLOCK = 0x03, // No locks
    };
    // Boot lock bits - application section
    enum class BLBAv : uint8_t {
        RWLOCK = 0x00, // Read and write not allowed
        RLOCK = 0x01, // Read not allowed
        WLOCK = 0x02, // Write not allowed
        NOLOCK = 0x03, // No locks
    };
    // Boot lock bits - application table section
    enum class BLBATv : uint8_t {
        RWLOCK = 0x00, // Read and write not allowed
        RLOCK = 0x01, // Read not allowed
        WLOCK = 0x02, // Write not allowed
        NOLOCK = 0x03, // No locks
    };
    // Lock bits
    enum class LBv : uint8_t {
        RWLOCK = 0x00, // Read and write not allowed
        WLOCK = 0x02, // Write not allowed
        NOLOCK = 0x03, // No locks
    };
}   // namespace NVM

/**
 * NVM
 * Non-volatile Memory Controller
 * Size: 17 bytes
 */
template <addressType BASE_ADDRESS>
struct NVM_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Address Register 0 - 1 bytes
    static constexpr struct ADDR0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
    } ADDR0 = {};

    /// Address Register 1 - 1 bytes
    static constexpr struct ADDR1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
    } ADDR1 = {};

    /// Address Register 2 - 1 bytes
    static constexpr struct ADDR2_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
    } ADDR2 = {};

    /// Data Register 0 - 1 bytes
    static constexpr struct DATA0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
    } DATA0 = {};

    /// Data Register 1 - 1 bytes
    static constexpr struct DATA1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
    } DATA1 = {};

    /// Data Register 2 - 1 bytes
    static constexpr struct DATA2_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
    } DATA2 = {};

    /// Command - 1 bytes
    static constexpr struct CMD_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        static constexpr bitfield_t<CMD_t, 6, 0, NVM::CMDv> CMD = {};    //< Command
    } CMD = {};

    /// Control Register A - 1 bytes
    static constexpr struct CTRLA_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        static constexpr bitfield_t<CTRLA_t, 0, 0, bool> CMDEX = {};    //< Command Execute
    } CTRLA = {};

    /// Control Register B - 1 bytes
    static constexpr struct CTRLB_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        static constexpr bitfield_t<CTRLB_t, 3, 3, bool> EEMAPEN = {};    //< EEPROM Mapping Enable
        static constexpr bitfield_t<CTRLB_t, 2, 2, bool> FPRM = {};    //< Flash Power Reduction Enable
        static constexpr bitfield_t<CTRLB_t, 1, 1, bool> EPRM = {};    //< EEPROM Power Reduction Enable
        static constexpr bitfield_t<CTRLB_t, 0, 0, bool> SPMLOCK = {};    //< SPM Lock
    } CTRLB = {};

    /// Interrupt Control - 1 bytes
    static constexpr struct INTCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x000D> {
        static constexpr bitfield_t<INTCTRL_t, 3, 2, NVM::SPMLVLv> SPMLVL = {};    //< SPM Interrupt Level
        static constexpr bitfield_t<INTCTRL_t, 1, 0, NVM::EELVLv> EELVL = {};    //< EEPROM Interrupt Level
    } INTCTRL = {};

    /// Status - 1 bytes
    static constexpr struct STATUS_t : reg_t<uint8_t, BASE_ADDRESS + 0x000F> {
        static constexpr bitfield_t<STATUS_t, 7, 7, bool> NVMBUSY = {};    //< Non-volatile Memory Busy
        static constexpr bitfield_t<STATUS_t, 6, 6, bool> FBUSY = {};    //< Flash Memory Busy
        static constexpr bitfield_t<STATUS_t, 1, 1, bool> EELOAD = {};    //< EEPROM Page Buffer Active Loading
        static constexpr bitfield_t<STATUS_t, 0, 0, bool> FLOAD = {};    //< Flash Page Buffer Active Loading
    } STATUS = {};

    /// Lock Bits - 1 bytes
    static constexpr struct LOCKBITS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0010> {
        static constexpr bitfield_t<LOCKBITS_t, 7, 6, NVM::BLBBv> BLBB = {};    //< Boot Lock Bits - Boot Section
        static constexpr bitfield_t<LOCKBITS_t, 5, 4, NVM::BLBAv> BLBA = {};    //< Boot Lock Bits - Application Section
        static constexpr bitfield_t<LOCKBITS_t, 3, 2, NVM::BLBATv> BLBAT = {};    //< Boot Lock Bits - Application Table
        static constexpr bitfield_t<LOCKBITS_t, 1, 0, NVM::LBv> LB = {};    //< Lock Bits
    } LOCKBITS = {};

    // NVM ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        EE = 0, // EE Interrupt
        SPM = 1, // SPM Interrupt
    };
};

} // namespace sfr
