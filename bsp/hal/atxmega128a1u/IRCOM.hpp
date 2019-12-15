/**
 * XMEGAAU-IRCOM (id I6090)
 * IR Communication Module
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace IRCOM {

    // Event channel selection
    enum class EVSELv : uint8_t {
        OFF = 0x00, // No Event Source
        _0 = 0x08, // Event Channel 0
        _1 = 0x09, // Event Channel 1
        _2 = 0x0A, // Event Channel 2
        _3 = 0x0B, // Event Channel 3
        _4 = 0x0C, // Event Channel 4
        _5 = 0x0D, // Event Channel 5
        _6 = 0x0E, // Event Channel 6
        _7 = 0x0F, // Event Channel 7
    };
}   // namespace IRCOM

/**
 * IRCOM
 * IR Communication Module
 * Size: 3 bytes
 */
template <addressType BASE_ADDRESS>
struct IRCOM_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// Control Register - 1 bytes
    static constexpr struct CTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<CTRL_t, 3, 0, IRCOM::EVSELv> EVSEL = {};    //< Event Channel Select
    } CTRL = {};

    /// IrDA Transmitter Pulse Length Control Register - 1 bytes
    static constexpr struct TXPLCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
    } TXPLCTRL = {};

    /// IrDA Receiver Pulse Length Control Register - 1 bytes
    static constexpr struct RXPLCTRL_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
    } RXPLCTRL = {};

};

} // namespace sfr
