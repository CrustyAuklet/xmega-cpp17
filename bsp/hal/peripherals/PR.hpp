/**
 * XMEGAAU-PR (id I6073)
 * Power Reduction
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace sfr {
    using ucpp::registers::reg_t;
    using ucpp::registers::bitfield_t;
    using ucpp::registers::registerType;
    using ucpp::registers::addressType;

namespace PR {

}   // namespace PR

/**
 * PR
 * Power Reduction
 * Size: 7 bytes
 */
template <addressType BASE_ADDRESS>
struct PR_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// General Power Reduction - 1 bytes
    static constexpr struct PRGEN_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0000>::operator=;
        static constexpr bitfield_t<PRGEN_t, 6, 6, bool> USB = {};    //< USB
        static constexpr bitfield_t<PRGEN_t, 4, 4, bool> AES = {};    //< AES
        static constexpr bitfield_t<PRGEN_t, 3, 3, bool> EBI = {};    //< External Bus Interface
        static constexpr bitfield_t<PRGEN_t, 2, 2, bool> RTC = {};    //< Real-time Counter
        static constexpr bitfield_t<PRGEN_t, 1, 1, bool> EVSYS = {};    //< Event System
        static constexpr bitfield_t<PRGEN_t, 0, 0, bool> DMA = {};    //< DMA-Controller
    } PRGEN = {};

    /// Power Reduction Port A - 1 bytes
    static constexpr struct PRPA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0001>::operator=;
        static constexpr bitfield_t<PRPA_t, 2, 2, bool> DAC = {};    //< Port A DAC
        static constexpr bitfield_t<PRPA_t, 1, 1, bool> ADC = {};    //< Port A ADC
        static constexpr bitfield_t<PRPA_t, 0, 0, bool> AC = {};    //< Port A Analog Comparator
    } PRPA = {};

    /// Power Reduction Port B - 1 bytes
    static constexpr struct PRPB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0002>::operator=;
        static constexpr bitfield_t<PRPB_t, 2, 2, bool> DAC = {};    //< Port B DAC
        static constexpr bitfield_t<PRPB_t, 1, 1, bool> ADC = {};    //< Port B ADC
        static constexpr bitfield_t<PRPB_t, 0, 0, bool> AC = {};    //< Port B Analog Comparator
    } PRPB = {};

    /// Power Reduction Port C - 1 bytes
    static constexpr struct PRPC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0003>::operator=;
        static constexpr bitfield_t<PRPC_t, 6, 6, bool> TWI = {};    //< Port C Two-wire Interface
        static constexpr bitfield_t<PRPC_t, 5, 5, bool> USART1 = {};    //< Port C USART1
        static constexpr bitfield_t<PRPC_t, 4, 4, bool> USART0 = {};    //< Port C USART0
        static constexpr bitfield_t<PRPC_t, 3, 3, bool> SPI = {};    //< Port C SPI
        static constexpr bitfield_t<PRPC_t, 2, 2, bool> HIRES = {};    //< Port C AWEX
        static constexpr bitfield_t<PRPC_t, 1, 1, bool> TC1 = {};    //< Port C Timer/Counter1
        static constexpr bitfield_t<PRPC_t, 0, 0, bool> TC0 = {};    //< Port C Timer/Counter0
    } PRPC = {};

    /// Power Reduction Port D - 1 bytes
    static constexpr struct PRPD_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0004>::operator=;
        static constexpr bitfield_t<PRPD_t, 6, 6, bool> TWI = {};    //< Port D Two-wire Interface
        static constexpr bitfield_t<PRPD_t, 5, 5, bool> USART1 = {};    //< Port D USART1
        static constexpr bitfield_t<PRPD_t, 4, 4, bool> USART0 = {};    //< Port D USART0
        static constexpr bitfield_t<PRPD_t, 3, 3, bool> SPI = {};    //< Port D SPI
        static constexpr bitfield_t<PRPD_t, 2, 2, bool> HIRES = {};    //< Port D AWEX
        static constexpr bitfield_t<PRPD_t, 1, 1, bool> TC1 = {};    //< Port D Timer/Counter1
        static constexpr bitfield_t<PRPD_t, 0, 0, bool> TC0 = {};    //< Port D Timer/Counter0
    } PRPD = {};

    /// Power Reduction Port E - 1 bytes
    static constexpr struct PRPE_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0005>::operator=;
        static constexpr bitfield_t<PRPE_t, 6, 6, bool> TWI = {};    //< Port E Two-wire Interface
        static constexpr bitfield_t<PRPE_t, 5, 5, bool> USART1 = {};    //< Port E USART1
        static constexpr bitfield_t<PRPE_t, 4, 4, bool> USART0 = {};    //< Port E USART0
        static constexpr bitfield_t<PRPE_t, 3, 3, bool> SPI = {};    //< Port E SPI
        static constexpr bitfield_t<PRPE_t, 2, 2, bool> HIRES = {};    //< Port E AWEX
        static constexpr bitfield_t<PRPE_t, 1, 1, bool> TC1 = {};    //< Port E Timer/Counter1
        static constexpr bitfield_t<PRPE_t, 0, 0, bool> TC0 = {};    //< Port E Timer/Counter0
    } PRPE = {};

    /// Power Reduction Port F - 1 bytes
    static constexpr struct PRPF_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        using reg_t<uint8_t, BASE_ADDRESS + 0x0006>::operator=;
        static constexpr bitfield_t<PRPF_t, 6, 6, bool> TWI = {};    //< Port F Two-wire Interface
        static constexpr bitfield_t<PRPF_t, 5, 5, bool> USART1 = {};    //< Port F USART1
        static constexpr bitfield_t<PRPF_t, 4, 4, bool> USART0 = {};    //< Port F USART0
        static constexpr bitfield_t<PRPF_t, 3, 3, bool> SPI = {};    //< Port F SPI
        static constexpr bitfield_t<PRPF_t, 2, 2, bool> HIRES = {};    //< Port F AWEX
        static constexpr bitfield_t<PRPF_t, 1, 1, bool> TC1 = {};    //< Port F Timer/Counter1
        static constexpr bitfield_t<PRPF_t, 0, 0, bool> TC0 = {};    //< Port F Timer/Counter0
    } PRPF = {};

};

} // namespace sfr
