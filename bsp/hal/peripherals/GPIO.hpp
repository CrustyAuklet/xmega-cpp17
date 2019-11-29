/**
 * None-GPIO (id I6085)
 * General Purpose IO
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using seal::registers::reg_t;
    using seal::registers::bitfield_t;

namespace GPIO {

}   // namespace GPIO

/**
 * GPIO
 * General Purpose IO Registers
 * Size: 16 bytes
 */
template <addressType BASE_ADDRESS>
struct GPIO_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// General Purpose IO Register 0 - 1 bytes
    static constexpr struct GPIOR0_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
    } GPIOR0 = {};

    /// General Purpose IO Register 1 - 1 bytes
    static constexpr struct GPIOR1_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
    } GPIOR1 = {};

    /// General Purpose IO Register 2 - 1 bytes
    static constexpr struct GPIOR2_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
    } GPIOR2 = {};

    /// General Purpose IO Register 3 - 1 bytes
    static constexpr struct GPIOR3_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
    } GPIOR3 = {};

    /// General Purpose IO Register 4 - 1 bytes
    static constexpr struct GPIOR4_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
    } GPIOR4 = {};

    /// General Purpose IO Register 5 - 1 bytes
    static constexpr struct GPIOR5_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
    } GPIOR5 = {};

    /// General Purpose IO Register 6 - 1 bytes
    static constexpr struct GPIOR6_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
    } GPIOR6 = {};

    /// General Purpose IO Register 7 - 1 bytes
    static constexpr struct GPIOR7_t : reg_t<uint8_t, BASE_ADDRESS + 0x0007> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0007>::operator=;
    } GPIOR7 = {};

    /// General Purpose IO Register 8 - 1 bytes
    static constexpr struct GPIOR8_t : reg_t<uint8_t, BASE_ADDRESS + 0x0008> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0008>::operator=;
    } GPIOR8 = {};

    /// General Purpose IO Register 9 - 1 bytes
    static constexpr struct GPIOR9_t : reg_t<uint8_t, BASE_ADDRESS + 0x0009> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0009>::operator=;
    } GPIOR9 = {};

    /// General Purpose IO Register 10 - 1 bytes
    static constexpr struct GPIORA_t : reg_t<uint8_t, BASE_ADDRESS + 0x000A> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000A>::operator=;
    } GPIORA = {};

    /// General Purpose IO Register 11 - 1 bytes
    static constexpr struct GPIORB_t : reg_t<uint8_t, BASE_ADDRESS + 0x000B> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000B>::operator=;
    } GPIORB = {};

    /// General Purpose IO Register 12 - 1 bytes
    static constexpr struct GPIORC_t : reg_t<uint8_t, BASE_ADDRESS + 0x000C> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000C>::operator=;
    } GPIORC = {};

    /// General Purpose IO Register 13 - 1 bytes
    static constexpr struct GPIORD_t : reg_t<uint8_t, BASE_ADDRESS + 0x000D> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000D>::operator=;
    } GPIORD = {};

    /// General Purpose IO Register 14 - 1 bytes
    static constexpr struct GPIORE_t : reg_t<uint8_t, BASE_ADDRESS + 0x000E> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000E>::operator=;
    } GPIORE = {};

    /// General Purpose IO Register 15 - 1 bytes
    static constexpr struct GPIORF_t : reg_t<uint8_t, BASE_ADDRESS + 0x000F> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x000F>::operator=;
    } GPIORF = {};

};

} // namespace sfr
