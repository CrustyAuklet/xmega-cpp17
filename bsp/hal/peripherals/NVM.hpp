/**
 * XMEGAAU-NVM (id I6076)
 * Non Volatile Memory Controller
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * NVM
 * Non-volatile Memory Controller
 * Size: 17 bytes
 */
template <addressType BASE_ADDRESS>
struct NVM_t {

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

    // NVM ISR Vector Offsets (two bytes each)
    enum class INTERRUPTS {
        EE = 0, // EE Interrupt
        SPM = 1, // SPM Interrupt
    };

    /// Address Register 0 - 1 bytes
    struct ADDR0 : public reg8_t<BASE_ADDRESS + 0x0000> {
    };

    /// Address Register 1 - 1 bytes
    struct ADDR1 : public reg8_t<BASE_ADDRESS + 0x0001> {
    };

    /// Address Register 2 - 1 bytes
    struct ADDR2 : public reg8_t<BASE_ADDRESS + 0x0002> {
    };

    /// Data Register 0 - 1 bytes
    struct DATA0 : public reg8_t<BASE_ADDRESS + 0x0004> {
    };

    /// Data Register 1 - 1 bytes
    struct DATA1 : public reg8_t<BASE_ADDRESS + 0x0005> {
    };

    /// Data Register 2 - 1 bytes
    struct DATA2 : public reg8_t<BASE_ADDRESS + 0x0006> {
    };

    /// Command - 1 bytes
    struct CMD : public reg8_t<BASE_ADDRESS + 0x000A> {
        using CMDf = reg_field_t<BASE_ADDRESS + 0x000A, 0x7F, 0, CMDv>;    //< Command
    };

    /// Control Register A - 1 bytes
    struct CTRLA : public reg8_t<BASE_ADDRESS + 0x000B> {
        using CMDEX = reg_field_t<BASE_ADDRESS + 0x000B, 0x01, 0>;    //< Command Execute
    };

    /// Control Register B - 1 bytes
    struct CTRLB : public reg8_t<BASE_ADDRESS + 0x000C> {
        using EEMAPEN = reg_field_t<BASE_ADDRESS + 0x000C, 0x08, 3>;    //< EEPROM Mapping Enable
        using FPRM = reg_field_t<BASE_ADDRESS + 0x000C, 0x04, 2>;    //< Flash Power Reduction Enable
        using EPRM = reg_field_t<BASE_ADDRESS + 0x000C, 0x02, 1>;    //< EEPROM Power Reduction Enable
        using SPMLOCK = reg_field_t<BASE_ADDRESS + 0x000C, 0x01, 0>;    //< SPM Lock
    };

    /// Interrupt Control - 1 bytes
    struct INTCTRL : public reg8_t<BASE_ADDRESS + 0x000D> {
        using SPMLVL = reg_field_t<BASE_ADDRESS + 0x000D, 0x0C, 2, SPMLVLv>;    //< SPM Interrupt Level
        using EELVL = reg_field_t<BASE_ADDRESS + 0x000D, 0x03, 0, EELVLv>;    //< EEPROM Interrupt Level
    };

    /// Status - 1 bytes
    struct STATUS : public reg8_t<BASE_ADDRESS + 0x000F> {
        using NVMBUSY = reg_field_t<BASE_ADDRESS + 0x000F, 0x80, 7>;    //< Non-volatile Memory Busy
        using FBUSY = reg_field_t<BASE_ADDRESS + 0x000F, 0x40, 6>;    //< Flash Memory Busy
        using EELOAD = reg_field_t<BASE_ADDRESS + 0x000F, 0x02, 1>;    //< EEPROM Page Buffer Active Loading
        using FLOAD = reg_field_t<BASE_ADDRESS + 0x000F, 0x01, 0>;    //< Flash Page Buffer Active Loading
    };

    /// Lock Bits - 1 bytes
    struct LOCKBITS : public reg8_t<BASE_ADDRESS + 0x0010> {
        using BLBB = reg_field_t<BASE_ADDRESS + 0x0010, 0xC0, 6, BLBBv>;    //< Boot Lock Bits - Boot Section
        using BLBA = reg_field_t<BASE_ADDRESS + 0x0010, 0x30, 4, BLBAv>;    //< Boot Lock Bits - Application Section
        using BLBAT = reg_field_t<BASE_ADDRESS + 0x0010, 0x0C, 2, BLBATv>;    //< Boot Lock Bits - Application Table
        using LB = reg_field_t<BASE_ADDRESS + 0x0010, 0x03, 0, LBv>;    //< Lock Bits
    };
};

} // namespace device
