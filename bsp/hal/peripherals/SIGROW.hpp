/**
 * XMEGAAU-SIGROW (id I6570)
 * Signature Row
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace SIGROW {

}   // namespace SIGROW

/**
 * NVM_PROD_SIGNATURES
 * Production Signatures
 * Size: 72 bytes
 */
template <addressType BASE_ADDRESS>
struct NVM_PROD_SIGNATURES_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// RCOSC 2 MHz Calibration Value B - 1 bytes
    static constexpr struct RCOSC2M_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
    } RCOSC2M = {};

    /// RCOSC 2 MHz Calibration Value A - 1 bytes
    static constexpr struct RCOSC2MA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
    } RCOSC2MA = {};

    /// RCOSC 32.768 kHz Calibration Value - 1 bytes
    static constexpr struct RCOSC32K_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
    } RCOSC32K = {};

    /// RCOSC 32 MHz Calibration Value B - 1 bytes
    static constexpr struct RCOSC32M_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
    } RCOSC32M = {};

    /// RCOSC 32 MHz Calibration Value A - 1 bytes
    static constexpr struct RCOSC32MA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
    } RCOSC32MA = {};

    /// Lot Number Byte 0, ASCII - 1 bytes
    static constexpr struct LOTNUM0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
    } LOTNUM0 = {};

    /// Lot Number Byte 1, ASCII - 1 bytes
    static constexpr struct LOTNUM1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
    } LOTNUM1 = {};

    /// Lot Number Byte 2, ASCII - 1 bytes
    static constexpr struct LOTNUM2_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
    } LOTNUM2 = {};

    /// Lot Number Byte 3, ASCII - 1 bytes
    static constexpr struct LOTNUM3_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
    } LOTNUM3 = {};

    /// Lot Number Byte 4, ASCII - 1 bytes
    static constexpr struct LOTNUM4_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
    } LOTNUM4 = {};

    /// Lot Number Byte 5, ASCII - 1 bytes
    static constexpr struct LOTNUM5_t : reg_t<uint8_t, BASE_ADDRESS + 0x000D> {
    } LOTNUM5 = {};

    /// Wafer Number - 1 bytes
    static constexpr struct WAFNUM_t : reg_t<uint8_t, BASE_ADDRESS + 0x0010> {
    } WAFNUM = {};

    /// Wafer Coordinate X Byte 0 - 1 bytes
    static constexpr struct COORDX0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0012> {
    } COORDX0 = {};

    /// Wafer Coordinate X Byte 1 - 1 bytes
    static constexpr struct COORDX1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0013> {
    } COORDX1 = {};

    /// Wafer Coordinate Y Byte 0 - 1 bytes
    static constexpr struct COORDY0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0014> {
    } COORDY0 = {};

    /// Wafer Coordinate Y Byte 1 - 1 bytes
    static constexpr struct COORDY1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0015> {
    } COORDY1 = {};

    /// USB Calibration Byte 0 - 1 bytes
    static constexpr struct USBCAL0_t : reg_t<uint8_t, BASE_ADDRESS + 0x001A> {
    } USBCAL0 = {};

    /// USB Calibration Byte 1 - 1 bytes
    static constexpr struct USBCAL1_t : reg_t<uint8_t, BASE_ADDRESS + 0x001B> {
    } USBCAL1 = {};

    /// USB RCOSC Calibration Value B - 1 bytes
    static constexpr struct USBRCOSC_t : reg_t<uint8_t, BASE_ADDRESS + 0x001C> {
    } USBRCOSC = {};

    /// USB RCOSC Calibration Value A - 1 bytes
    static constexpr struct USBRCOSCA_t : reg_t<uint8_t, BASE_ADDRESS + 0x001D> {
    } USBRCOSCA = {};

    /// ADCA Calibration Byte 0 - 1 bytes
    static constexpr struct ADCACAL0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0020> {
    } ADCACAL0 = {};

    /// ADCA Calibration Byte 1 - 1 bytes
    static constexpr struct ADCACAL1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0021> {
    } ADCACAL1 = {};

    /// ADCB Calibration Byte 0 - 1 bytes
    static constexpr struct ADCBCAL0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0024> {
    } ADCBCAL0 = {};

    /// ADCB Calibration Byte 1 - 1 bytes
    static constexpr struct ADCBCAL1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0025> {
    } ADCBCAL1 = {};

    /// Temperature Sensor Calibration Byte 0 - 1 bytes
    static constexpr struct TEMPSENSE0_t : reg_t<uint8_t, BASE_ADDRESS + 0x002E> {
    } TEMPSENSE0 = {};

    /// Temperature Sensor Calibration Byte 1 - 1 bytes
    static constexpr struct TEMPSENSE1_t : reg_t<uint8_t, BASE_ADDRESS + 0x002F> {
    } TEMPSENSE1 = {};

    /// DACA0 Calibration Byte 0 - 1 bytes
    static constexpr struct DACA0OFFCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0030> {
    } DACA0OFFCAL = {};

    /// DACA0 Calibration Byte 1 - 1 bytes
    static constexpr struct DACA0GAINCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0031> {
    } DACA0GAINCAL = {};

    /// DACB0 Calibration Byte 0 - 1 bytes
    static constexpr struct DACB0OFFCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0032> {
    } DACB0OFFCAL = {};

    /// DACB0 Calibration Byte 1 - 1 bytes
    static constexpr struct DACB0GAINCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0033> {
    } DACB0GAINCAL = {};

    /// DACA1 Calibration Byte 0 - 1 bytes
    static constexpr struct DACA1OFFCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0034> {
    } DACA1OFFCAL = {};

    /// DACA1 Calibration Byte 1 - 1 bytes
    static constexpr struct DACA1GAINCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0035> {
    } DACA1GAINCAL = {};

    /// DACB1 Calibration Byte 0 - 1 bytes
    static constexpr struct DACB1OFFCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0036> {
    } DACB1OFFCAL = {};

    /// DACB1 Calibration Byte 1 - 1 bytes
    static constexpr struct DACB1GAINCAL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0037> {
    } DACB1GAINCAL = {};

};

} // namespace sfr
