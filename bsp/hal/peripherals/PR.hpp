/**
 * XMEGAAU-PR (id I6073)
 * Power Reduction
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

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
        static constexpr bitfield_t<PRGEN_t, 0x40, 6> USB = {};    //< USB
        static constexpr bitfield_t<PRGEN_t, 0x10, 4> AES = {};    //< AES
        static constexpr bitfield_t<PRGEN_t, 0x08, 3> EBI = {};    //< External Bus Interface
        static constexpr bitfield_t<PRGEN_t, 0x04, 2> RTC = {};    //< Real-time Counter
        static constexpr bitfield_t<PRGEN_t, 0x02, 1> EVSYS = {};    //< Event System
        static constexpr bitfield_t<PRGEN_t, 0x01, 0> DMA = {};    //< DMA-Controller
    } PRGEN = {};

    /// Power Reduction Port A - 1 bytes
    static constexpr struct PRPA_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
        static constexpr bitfield_t<PRPA_t, 0x04, 2> DAC = {};    //< Port A DAC
        static constexpr bitfield_t<PRPA_t, 0x02, 1> ADC = {};    //< Port A ADC
        static constexpr bitfield_t<PRPA_t, 0x01, 0> AC = {};    //< Port A Analog Comparator
    } PRPA = {};

    /// Power Reduction Port B - 1 bytes
    static constexpr struct PRPB_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
        static constexpr bitfield_t<PRPB_t, 0x04, 2> DAC = {};    //< Port B DAC
        static constexpr bitfield_t<PRPB_t, 0x02, 1> ADC = {};    //< Port B ADC
        static constexpr bitfield_t<PRPB_t, 0x01, 0> AC = {};    //< Port B Analog Comparator
    } PRPB = {};

    /// Power Reduction Port C - 1 bytes
    static constexpr struct PRPC_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<PRPC_t, 0x40, 6> TWI = {};    //< Port C Two-wire Interface
        static constexpr bitfield_t<PRPC_t, 0x20, 5> USART1 = {};    //< Port C USART1
        static constexpr bitfield_t<PRPC_t, 0x10, 4> USART0 = {};    //< Port C USART0
        static constexpr bitfield_t<PRPC_t, 0x08, 3> SPI = {};    //< Port C SPI
        static constexpr bitfield_t<PRPC_t, 0x04, 2> HIRES = {};    //< Port C AWEX
        static constexpr bitfield_t<PRPC_t, 0x02, 1> TC1 = {};    //< Port C Timer/Counter1
        static constexpr bitfield_t<PRPC_t, 0x01, 0> TC0 = {};    //< Port C Timer/Counter0
    } PRPC = {};

    /// Power Reduction Port D - 1 bytes
    static constexpr struct PRPD_t : reg_t<uint8_t, BASE_ADDRESS + 0x0004> {
        static constexpr bitfield_t<PRPD_t, 0x40, 6> TWI = {};    //< Port D Two-wire Interface
        static constexpr bitfield_t<PRPD_t, 0x20, 5> USART1 = {};    //< Port D USART1
        static constexpr bitfield_t<PRPD_t, 0x10, 4> USART0 = {};    //< Port D USART0
        static constexpr bitfield_t<PRPD_t, 0x08, 3> SPI = {};    //< Port D SPI
        static constexpr bitfield_t<PRPD_t, 0x04, 2> HIRES = {};    //< Port D AWEX
        static constexpr bitfield_t<PRPD_t, 0x02, 1> TC1 = {};    //< Port D Timer/Counter1
        static constexpr bitfield_t<PRPD_t, 0x01, 0> TC0 = {};    //< Port D Timer/Counter0
    } PRPD = {};

    /// Power Reduction Port E - 1 bytes
    static constexpr struct PRPE_t : reg_t<uint8_t, BASE_ADDRESS + 0x0005> {
        static constexpr bitfield_t<PRPE_t, 0x40, 6> TWI = {};    //< Port E Two-wire Interface
        static constexpr bitfield_t<PRPE_t, 0x20, 5> USART1 = {};    //< Port E USART1
        static constexpr bitfield_t<PRPE_t, 0x10, 4> USART0 = {};    //< Port E USART0
        static constexpr bitfield_t<PRPE_t, 0x08, 3> SPI = {};    //< Port E SPI
        static constexpr bitfield_t<PRPE_t, 0x04, 2> HIRES = {};    //< Port E AWEX
        static constexpr bitfield_t<PRPE_t, 0x02, 1> TC1 = {};    //< Port E Timer/Counter1
        static constexpr bitfield_t<PRPE_t, 0x01, 0> TC0 = {};    //< Port E Timer/Counter0
    } PRPE = {};

    /// Power Reduction Port F - 1 bytes
    static constexpr struct PRPF_t : reg_t<uint8_t, BASE_ADDRESS + 0x0006> {
        static constexpr bitfield_t<PRPF_t, 0x40, 6> TWI = {};    //< Port F Two-wire Interface
        static constexpr bitfield_t<PRPF_t, 0x20, 5> USART1 = {};    //< Port F USART1
        static constexpr bitfield_t<PRPF_t, 0x10, 4> USART0 = {};    //< Port F USART0
        static constexpr bitfield_t<PRPF_t, 0x08, 3> SPI = {};    //< Port F SPI
        static constexpr bitfield_t<PRPF_t, 0x04, 2> HIRES = {};    //< Port F AWEX
        static constexpr bitfield_t<PRPF_t, 0x02, 1> TC1 = {};    //< Port F Timer/Counter1
        static constexpr bitfield_t<PRPF_t, 0x01, 0> TC0 = {};    //< Port F Timer/Counter0
    } PRPF = {};

};

} // namespace device
