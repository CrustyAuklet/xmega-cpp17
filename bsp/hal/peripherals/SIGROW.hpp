/**
 * XMEGAAU-SIGROW (id I6570)
 * Signature Row
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * NVM_PROD_SIGNATURES
 * Production Signatures
 * Size: 72 bytes
 */
template <addressType BASE_ADDRESS>
struct NVM_PROD_SIGNATURES_t {


    /// RCOSC 2 MHz Calibration Value B - 1 bytes
    struct RCOSC2M : public reg8_t<BASE_ADDRESS + 0x0000> {
    };

    /// RCOSC 2 MHz Calibration Value A - 1 bytes
    struct RCOSC2MA : public reg8_t<BASE_ADDRESS + 0x0001> {
    };

    /// RCOSC 32.768 kHz Calibration Value - 1 bytes
    struct RCOSC32K : public reg8_t<BASE_ADDRESS + 0x0002> {
    };

    /// RCOSC 32 MHz Calibration Value B - 1 bytes
    struct RCOSC32M : public reg8_t<BASE_ADDRESS + 0x0003> {
    };

    /// RCOSC 32 MHz Calibration Value A - 1 bytes
    struct RCOSC32MA : public reg8_t<BASE_ADDRESS + 0x0004> {
    };

    /// Lot Number Byte 0, ASCII - 1 bytes
    struct LOTNUM0 : public reg8_t<BASE_ADDRESS + 0x0008> {
    };

    /// Lot Number Byte 1, ASCII - 1 bytes
    struct LOTNUM1 : public reg8_t<BASE_ADDRESS + 0x0009> {
    };

    /// Lot Number Byte 2, ASCII - 1 bytes
    struct LOTNUM2 : public reg8_t<BASE_ADDRESS + 0x000A> {
    };

    /// Lot Number Byte 3, ASCII - 1 bytes
    struct LOTNUM3 : public reg8_t<BASE_ADDRESS + 0x000B> {
    };

    /// Lot Number Byte 4, ASCII - 1 bytes
    struct LOTNUM4 : public reg8_t<BASE_ADDRESS + 0x000C> {
    };

    /// Lot Number Byte 5, ASCII - 1 bytes
    struct LOTNUM5 : public reg8_t<BASE_ADDRESS + 0x000D> {
    };

    /// Wafer Number - 1 bytes
    struct WAFNUM : public reg8_t<BASE_ADDRESS + 0x0010> {
    };

    /// Wafer Coordinate X Byte 0 - 1 bytes
    struct COORDX0 : public reg8_t<BASE_ADDRESS + 0x0012> {
    };

    /// Wafer Coordinate X Byte 1 - 1 bytes
    struct COORDX1 : public reg8_t<BASE_ADDRESS + 0x0013> {
    };

    /// Wafer Coordinate Y Byte 0 - 1 bytes
    struct COORDY0 : public reg8_t<BASE_ADDRESS + 0x0014> {
    };

    /// Wafer Coordinate Y Byte 1 - 1 bytes
    struct COORDY1 : public reg8_t<BASE_ADDRESS + 0x0015> {
    };

    /// USB Calibration Byte 0 - 1 bytes
    struct USBCAL0 : public reg8_t<BASE_ADDRESS + 0x001A> {
    };

    /// USB Calibration Byte 1 - 1 bytes
    struct USBCAL1 : public reg8_t<BASE_ADDRESS + 0x001B> {
    };

    /// USB RCOSC Calibration Value B - 1 bytes
    struct USBRCOSC : public reg8_t<BASE_ADDRESS + 0x001C> {
    };

    /// USB RCOSC Calibration Value A - 1 bytes
    struct USBRCOSCA : public reg8_t<BASE_ADDRESS + 0x001D> {
    };

    /// ADCA Calibration Byte 0 - 1 bytes
    struct ADCACAL0 : public reg8_t<BASE_ADDRESS + 0x0020> {
    };

    /// ADCA Calibration Byte 1 - 1 bytes
    struct ADCACAL1 : public reg8_t<BASE_ADDRESS + 0x0021> {
    };

    /// ADCB Calibration Byte 0 - 1 bytes
    struct ADCBCAL0 : public reg8_t<BASE_ADDRESS + 0x0024> {
    };

    /// ADCB Calibration Byte 1 - 1 bytes
    struct ADCBCAL1 : public reg8_t<BASE_ADDRESS + 0x0025> {
    };

    /// Temperature Sensor Calibration Byte 0 - 1 bytes
    struct TEMPSENSE0 : public reg8_t<BASE_ADDRESS + 0x002E> {
    };

    /// Temperature Sensor Calibration Byte 1 - 1 bytes
    struct TEMPSENSE1 : public reg8_t<BASE_ADDRESS + 0x002F> {
    };

    /// DACA0 Calibration Byte 0 - 1 bytes
    struct DACA0OFFCAL : public reg8_t<BASE_ADDRESS + 0x0030> {
    };

    /// DACA0 Calibration Byte 1 - 1 bytes
    struct DACA0GAINCAL : public reg8_t<BASE_ADDRESS + 0x0031> {
    };

    /// DACB0 Calibration Byte 0 - 1 bytes
    struct DACB0OFFCAL : public reg8_t<BASE_ADDRESS + 0x0032> {
    };

    /// DACB0 Calibration Byte 1 - 1 bytes
    struct DACB0GAINCAL : public reg8_t<BASE_ADDRESS + 0x0033> {
    };

    /// DACA1 Calibration Byte 0 - 1 bytes
    struct DACA1OFFCAL : public reg8_t<BASE_ADDRESS + 0x0034> {
    };

    /// DACA1 Calibration Byte 1 - 1 bytes
    struct DACA1GAINCAL : public reg8_t<BASE_ADDRESS + 0x0035> {
    };

    /// DACB1 Calibration Byte 0 - 1 bytes
    struct DACB1OFFCAL : public reg8_t<BASE_ADDRESS + 0x0036> {
    };

    /// DACB1 Calibration Byte 1 - 1 bytes
    struct DACB1GAINCAL : public reg8_t<BASE_ADDRESS + 0x0037> {
    };
};

} // namespace device
