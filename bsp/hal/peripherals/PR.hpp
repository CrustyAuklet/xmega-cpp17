/**
 * XMEGAAU-PR (id I6073)
 * Power Reduction
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * PR
 * Power Reduction
 * Size: 7 bytes
 */
template <addressType BASE_ADDRESS>
struct PR_t {


    /// General Power Reduction - 1 bytes
    struct PRGEN : public reg8_t<BASE_ADDRESS + 0x0000> {
        using USB = reg_field_t<BASE_ADDRESS + 0x0000, 0x40, 6>;    //< USB
        using AES = reg_field_t<BASE_ADDRESS + 0x0000, 0x10, 4>;    //< AES
        using EBI = reg_field_t<BASE_ADDRESS + 0x0000, 0x08, 3>;    //< External Bus Interface
        using RTC = reg_field_t<BASE_ADDRESS + 0x0000, 0x04, 2>;    //< Real-time Counter
        using EVSYS = reg_field_t<BASE_ADDRESS + 0x0000, 0x02, 1>;    //< Event System
        using DMA = reg_field_t<BASE_ADDRESS + 0x0000, 0x01, 0>;    //< DMA-Controller
    };

    /// Power Reduction Port A - 1 bytes
    struct PRPA : public reg8_t<BASE_ADDRESS + 0x0001> {
        using DAC = reg_field_t<BASE_ADDRESS + 0x0001, 0x04, 2>;    //< Port A DAC
        using ADC = reg_field_t<BASE_ADDRESS + 0x0001, 0x02, 1>;    //< Port A ADC
        using AC = reg_field_t<BASE_ADDRESS + 0x0001, 0x01, 0>;    //< Port A Analog Comparator
    };

    /// Power Reduction Port B - 1 bytes
    struct PRPB : public reg8_t<BASE_ADDRESS + 0x0002> {
        using DAC = reg_field_t<BASE_ADDRESS + 0x0002, 0x04, 2>;    //< Port B DAC
        using ADC = reg_field_t<BASE_ADDRESS + 0x0002, 0x02, 1>;    //< Port B ADC
        using AC = reg_field_t<BASE_ADDRESS + 0x0002, 0x01, 0>;    //< Port B Analog Comparator
    };

    /// Power Reduction Port C - 1 bytes
    struct PRPC : public reg8_t<BASE_ADDRESS + 0x0003> {
        using TWI = reg_field_t<BASE_ADDRESS + 0x0003, 0x40, 6>;    //< Port C Two-wire Interface
        using USART1 = reg_field_t<BASE_ADDRESS + 0x0003, 0x20, 5>;    //< Port C USART1
        using USART0 = reg_field_t<BASE_ADDRESS + 0x0003, 0x10, 4>;    //< Port C USART0
        using SPI = reg_field_t<BASE_ADDRESS + 0x0003, 0x08, 3>;    //< Port C SPI
        using HIRES = reg_field_t<BASE_ADDRESS + 0x0003, 0x04, 2>;    //< Port C AWEX
        using TC1 = reg_field_t<BASE_ADDRESS + 0x0003, 0x02, 1>;    //< Port C Timer/Counter1
        using TC0 = reg_field_t<BASE_ADDRESS + 0x0003, 0x01, 0>;    //< Port C Timer/Counter0
    };

    /// Power Reduction Port D - 1 bytes
    struct PRPD : public reg8_t<BASE_ADDRESS + 0x0004> {
        using TWI = reg_field_t<BASE_ADDRESS + 0x0004, 0x40, 6>;    //< Port D Two-wire Interface
        using USART1 = reg_field_t<BASE_ADDRESS + 0x0004, 0x20, 5>;    //< Port D USART1
        using USART0 = reg_field_t<BASE_ADDRESS + 0x0004, 0x10, 4>;    //< Port D USART0
        using SPI = reg_field_t<BASE_ADDRESS + 0x0004, 0x08, 3>;    //< Port D SPI
        using HIRES = reg_field_t<BASE_ADDRESS + 0x0004, 0x04, 2>;    //< Port D AWEX
        using TC1 = reg_field_t<BASE_ADDRESS + 0x0004, 0x02, 1>;    //< Port D Timer/Counter1
        using TC0 = reg_field_t<BASE_ADDRESS + 0x0004, 0x01, 0>;    //< Port D Timer/Counter0
    };

    /// Power Reduction Port E - 1 bytes
    struct PRPE : public reg8_t<BASE_ADDRESS + 0x0005> {
        using TWI = reg_field_t<BASE_ADDRESS + 0x0005, 0x40, 6>;    //< Port E Two-wire Interface
        using USART1 = reg_field_t<BASE_ADDRESS + 0x0005, 0x20, 5>;    //< Port E USART1
        using USART0 = reg_field_t<BASE_ADDRESS + 0x0005, 0x10, 4>;    //< Port E USART0
        using SPI = reg_field_t<BASE_ADDRESS + 0x0005, 0x08, 3>;    //< Port E SPI
        using HIRES = reg_field_t<BASE_ADDRESS + 0x0005, 0x04, 2>;    //< Port E AWEX
        using TC1 = reg_field_t<BASE_ADDRESS + 0x0005, 0x02, 1>;    //< Port E Timer/Counter1
        using TC0 = reg_field_t<BASE_ADDRESS + 0x0005, 0x01, 0>;    //< Port E Timer/Counter0
    };

    /// Power Reduction Port F - 1 bytes
    struct PRPF : public reg8_t<BASE_ADDRESS + 0x0006> {
        using TWI = reg_field_t<BASE_ADDRESS + 0x0006, 0x40, 6>;    //< Port F Two-wire Interface
        using USART1 = reg_field_t<BASE_ADDRESS + 0x0006, 0x20, 5>;    //< Port F USART1
        using USART0 = reg_field_t<BASE_ADDRESS + 0x0006, 0x10, 4>;    //< Port F USART0
        using SPI = reg_field_t<BASE_ADDRESS + 0x0006, 0x08, 3>;    //< Port F SPI
        using HIRES = reg_field_t<BASE_ADDRESS + 0x0006, 0x04, 2>;    //< Port F AWEX
        using TC1 = reg_field_t<BASE_ADDRESS + 0x0006, 0x02, 1>;    //< Port F Timer/Counter1
        using TC0 = reg_field_t<BASE_ADDRESS + 0x0006, 0x01, 0>;    //< Port F Timer/Counter0
    };
};

} // namespace device
