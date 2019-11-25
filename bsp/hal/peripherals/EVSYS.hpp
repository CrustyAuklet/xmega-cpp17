/**
 * XMEGAAU-EVSYS (id I6061)
 * Event System
 *
 *
 */
#pragma once

#include "register.hpp"
#include <cstdint>

namespace device {

/**
 * EVSYS
 * Event System
 * Size: 18 bytes
 */
template <addressType BASE_ADDRESS>
struct EVSYS_t {

    // Quadrature Decoder Index Recognition Mode
    enum class QDIRMv : uint8_t {
        _00 = 0x00, // QDPH0 = 0, QDPH90 = 0
        _01 = 0x01, // QDPH0 = 0, QDPH90 = 1
        _10 = 0x02, // QDPH0 = 1, QDPH90 = 0
        _11 = 0x03, // QDPH0 = 1, QDPH90 = 1
    };

    // Digital filter coefficient
    enum class DIGFILTv : uint8_t {
        _1SAMPLE = 0x00, // 1 SAMPLE
        _2SAMPLES = 0x01, // 2 SAMPLES
        _3SAMPLES = 0x02, // 3 SAMPLES
        _4SAMPLES = 0x03, // 4 SAMPLES
        _5SAMPLES = 0x04, // 5 SAMPLES
        _6SAMPLES = 0x05, // 6 SAMPLES
        _7SAMPLES = 0x06, // 7 SAMPLES
        _8SAMPLES = 0x07, // 8 SAMPLES
    };

    // Event Channel multiplexer input selection
    enum class CHMUXv : uint8_t {
        OFF = 0x00, // Off
        RTC_OVF = 0x08, // RTC Overflow
        RTC_CMP = 0x09, // RTC Compare Match
        USB = 0x0A, // USB Setup, SOF, CRC error and UNF/OVF
        ACA_CH0 = 0x10, // Analog Comparator A Channel 0
        ACA_CH1 = 0x11, // Analog Comparator A Channel 1
        ACA_WIN = 0x12, // Analog Comparator A Window
        ACB_CH0 = 0x13, // Analog Comparator B Channel 0
        ACB_CH1 = 0x14, // Analog Comparator B Channel 1
        ACB_WIN = 0x15, // Analog Comparator B Window
        ADCA_CH0 = 0x20, // ADC A Channel 0
        ADCA_CH1 = 0x21, // ADC A Channel 1
        ADCA_CH2 = 0x22, // ADC A Channel 2
        ADCA_CH3 = 0x23, // ADC A Channel 3
        ADCB_CH0 = 0x24, // ADC B Channel 0
        ADCB_CH1 = 0x25, // ADC B Channel 1
        ADCB_CH2 = 0x26, // ADC B Channel 2
        ADCB_CH3 = 0x27, // ADC B Channel 3
        PORTA_PIN0 = 0x50, // Port A, Pin0
        PORTA_PIN1 = 0x51, // Port A, Pin1
        PORTA_PIN2 = 0x52, // Port A, Pin2
        PORTA_PIN3 = 0x53, // Port A, Pin3
        PORTA_PIN4 = 0x54, // Port A, Pin4
        PORTA_PIN5 = 0x55, // Port A, Pin5
        PORTA_PIN6 = 0x56, // Port A, Pin6
        PORTA_PIN7 = 0x57, // Port A, Pin7
        PORTB_PIN0 = 0x58, // Port B, Pin0
        PORTB_PIN1 = 0x59, // Port B, Pin1
        PORTB_PIN2 = 0x5A, // Port B, Pin2
        PORTB_PIN3 = 0x5B, // Port B, Pin3
        PORTB_PIN4 = 0x5C, // Port B, Pin4
        PORTB_PIN5 = 0x5D, // Port B, Pin5
        PORTB_PIN6 = 0x5E, // Port B, Pin6
        PORTB_PIN7 = 0x5F, // Port B, Pin7
        PORTC_PIN0 = 0x60, // Port C, Pin0
        PORTC_PIN1 = 0x61, // Port C, Pin1
        PORTC_PIN2 = 0x62, // Port C, Pin2
        PORTC_PIN3 = 0x63, // Port C, Pin3
        PORTC_PIN4 = 0x64, // Port C, Pin4
        PORTC_PIN5 = 0x65, // Port C, Pin5
        PORTC_PIN6 = 0x66, // Port C, Pin6
        PORTC_PIN7 = 0x67, // Port C, Pin7
        PORTD_PIN0 = 0x68, // Port D, Pin0
        PORTD_PIN1 = 0x69, // Port D, Pin1
        PORTD_PIN2 = 0x6A, // Port D, Pin2
        PORTD_PIN3 = 0x6B, // Port D, Pin3
        PORTD_PIN4 = 0x6C, // Port D, Pin4
        PORTD_PIN5 = 0x6D, // Port D, Pin5
        PORTD_PIN6 = 0x6E, // Port D, Pin6
        PORTD_PIN7 = 0x6F, // Port D, Pin7
        PORTE_PIN0 = 0x70, // Port E, Pin0
        PORTE_PIN1 = 0x71, // Port E, Pin1
        PORTE_PIN2 = 0x72, // Port E, Pin2
        PORTE_PIN3 = 0x73, // Port E, Pin3
        PORTE_PIN4 = 0x74, // Port E, Pin4
        PORTE_PIN5 = 0x75, // Port E, Pin5
        PORTE_PIN6 = 0x76, // Port E, Pin6
        PORTE_PIN7 = 0x77, // Port E, Pin7
        PORTF_PIN0 = 0x78, // Port F, Pin0
        PORTF_PIN1 = 0x79, // Port F, Pin1
        PORTF_PIN2 = 0x7A, // Port F, Pin2
        PORTF_PIN3 = 0x7B, // Port F, Pin3
        PORTF_PIN4 = 0x7C, // Port F, Pin4
        PORTF_PIN5 = 0x7D, // Port F, Pin5
        PORTF_PIN6 = 0x7E, // Port F, Pin6
        PORTF_PIN7 = 0x7F, // Port F, Pin7
        PRESCALER_1 = 0x80, // Prescaler, divide by 1
        PRESCALER_2 = 0x81, // Prescaler, divide by 2
        PRESCALER_4 = 0x82, // Prescaler, divide by 4
        PRESCALER_8 = 0x83, // Prescaler, divide by 8
        PRESCALER_16 = 0x84, // Prescaler, divide by 16
        PRESCALER_32 = 0x85, // Prescaler, divide by 32
        PRESCALER_64 = 0x86, // Prescaler, divide by 64
        PRESCALER_128 = 0x87, // Prescaler, divide by 128
        PRESCALER_256 = 0x88, // Prescaler, divide by 256
        PRESCALER_512 = 0x89, // Prescaler, divide by 512
        PRESCALER_1024 = 0x8A, // Prescaler, divide by 1024
        PRESCALER_2048 = 0x8B, // Prescaler, divide by 2048
        PRESCALER_4096 = 0x8C, // Prescaler, divide by 4096
        PRESCALER_8192 = 0x8D, // Prescaler, divide by 8192
        PRESCALER_16384 = 0x8E, // Prescaler, divide by 16384
        PRESCALER_32768 = 0x8F, // Prescaler, divide by 32768
        TCC0_OVF = 0xC0, // Timer/Counter C0 Overflow
        TCC0_ERR = 0xC1, // Timer/Counter C0 Error
        TCC0_CCA = 0xC4, // Timer/Counter C0 Compare or Capture A
        TCC0_CCB = 0xC5, // Timer/Counter C0 Compare or Capture B
        TCC0_CCC = 0xC6, // Timer/Counter C0 Compare or Capture C
        TCC0_CCD = 0xC7, // Timer/Counter C0 Compare or Capture D
        TCC1_OVF = 0xC8, // Timer/Counter C1 Overflow
        TCC1_ERR = 0xC9, // Timer/Counter C1 Error
        TCC1_CCA = 0xCC, // Timer/Counter C1 Compare or Capture A
        TCC1_CCB = 0xCD, // Timer/Counter C1 Compare or Capture B
        TCD0_OVF = 0xD0, // Timer/Counter D0 Overflow
        TCD0_ERR = 0xD1, // Timer/Counter D0 Error
        TCD0_CCA = 0xD4, // Timer/Counter D0 Compare or Capture A
        TCD0_CCB = 0xD5, // Timer/Counter D0 Compare or Capture B
        TCD0_CCC = 0xD6, // Timer/Counter D0 Compare or Capture C
        TCD0_CCD = 0xD7, // Timer/Counter D0 Compare or Capture D
        TCD1_OVF = 0xD8, // Timer/Counter D1 Overflow
        TCD1_ERR = 0xD9, // Timer/Counter D1 Error
        TCD1_CCA = 0xDC, // Timer/Counter D1 Compare or Capture A
        TCD1_CCB = 0xDD, // Timer/Counter D1 Compare or Capture B
        TCE0_OVF = 0xE0, // Timer/Counter E0 Overflow
        TCE0_ERR = 0xE1, // Timer/Counter E0 Error
        TCE0_CCA = 0xE4, // Timer/Counter E0 Compare or Capture A
        TCE0_CCB = 0xE5, // Timer/Counter E0 Compare or Capture B
        TCE0_CCC = 0xE6, // Timer/Counter E0 Compare or Capture C
        TCE0_CCD = 0xE7, // Timer/Counter E0 Compare or Capture D
        TCE1_OVF = 0xE8, // Timer/Counter E1 Overflow
        TCE1_ERR = 0xE9, // Timer/Counter E1 Error
        TCE1_CCA = 0xEC, // Timer/Counter E1 Compare or Capture A
        TCE1_CCB = 0xED, // Timer/Counter E1 Compare or Capture B
        TCF0_OVF = 0xF0, // Timer/Counter F0 Overflow
        TCF0_ERR = 0xF1, // Timer/Counter F0 Error
        TCF0_CCA = 0xF4, // Timer/Counter F0 Compare or Capture A
        TCF0_CCB = 0xF5, // Timer/Counter F0 Compare or Capture B
        TCF0_CCC = 0xF6, // Timer/Counter F0 Compare or Capture C
        TCF0_CCD = 0xF7, // Timer/Counter F0 Compare or Capture D
        TCF1_OVF = 0xF8, // Timer/Counter F1 Overflow
        TCF1_ERR = 0xF9, // Timer/Counter F1 Error
        TCF1_CCA = 0xFC, // Timer/Counter F1 Compare or Capture A
        TCF1_CCB = 0xFD, // Timer/Counter F1 Compare or Capture B
    };


    /// Event Channel 0 Multiplexer - 1 bytes
    struct CH0MUX : public reg8_t<BASE_ADDRESS + 0x0000> {
        using CHMUX = reg_field_t<BASE_ADDRESS + 0x0000, 0xFF, 0, CHMUXv>;    //< Event Channel 0 Multiplexer
    };

    /// Event Channel 1 Multiplexer - 1 bytes
    struct CH1MUX : public reg8_t<BASE_ADDRESS + 0x0001> {
        using CHMUX = reg_field_t<BASE_ADDRESS + 0x0001, 0xFF, 0, CHMUXv>;    //< Event Channel 1 Multiplexer
    };

    /// Event Channel 2 Multiplexer - 1 bytes
    struct CH2MUX : public reg8_t<BASE_ADDRESS + 0x0002> {
        using CHMUX = reg_field_t<BASE_ADDRESS + 0x0002, 0xFF, 0, CHMUXv>;    //< Event Channel 2 Multiplexer
    };

    /// Event Channel 3 Multiplexer - 1 bytes
    struct CH3MUX : public reg8_t<BASE_ADDRESS + 0x0003> {
        using CHMUX = reg_field_t<BASE_ADDRESS + 0x0003, 0xFF, 0, CHMUXv>;    //< Event Channel 3 Multiplexer
    };

    /// Event Channel 4 Multiplexer - 1 bytes
    struct CH4MUX : public reg8_t<BASE_ADDRESS + 0x0004> {
        using CHMUX = reg_field_t<BASE_ADDRESS + 0x0004, 0xFF, 0, CHMUXv>;    //< Event Channel 4 Multiplexer
    };

    /// Event Channel 5 Multiplexer - 1 bytes
    struct CH5MUX : public reg8_t<BASE_ADDRESS + 0x0005> {
        using CHMUX = reg_field_t<BASE_ADDRESS + 0x0005, 0xFF, 0, CHMUXv>;    //< Event Channel 5 Multiplexer
    };

    /// Event Channel 6 Multiplexer - 1 bytes
    struct CH6MUX : public reg8_t<BASE_ADDRESS + 0x0006> {
        using CHMUX = reg_field_t<BASE_ADDRESS + 0x0006, 0xFF, 0, CHMUXv>;    //< Event Channel 6 Multiplexer
    };

    /// Event Channel 7 Multiplexer - 1 bytes
    struct CH7MUX : public reg8_t<BASE_ADDRESS + 0x0007> {
        using CHMUX = reg_field_t<BASE_ADDRESS + 0x0007, 0xFF, 0, CHMUXv>;    //< Event Channel 7 Multiplexer
    };

    /// Channel 0 Control Register - 1 bytes
    struct CH0CTRL : public reg8_t<BASE_ADDRESS + 0x0008> {
        using QDIRM = reg_field_t<BASE_ADDRESS + 0x0008, 0x60, 5>;    //< Quadrature Decoder Index Recognition Mode
        using QDIEN = reg_field_t<BASE_ADDRESS + 0x0008, 0x10, 4>;    //< Quadrature Decoder Index Enable
        using QDEN = reg_field_t<BASE_ADDRESS + 0x0008, 0x08, 3>;    //< Quadrature Decoder Enable
        using DIGFILT = reg_field_t<BASE_ADDRESS + 0x0008, 0x07, 0, DIGFILTv>;    //< Digital Filter
    };

    /// Channel 1 Control Register - 1 bytes
    struct CH1CTRL : public reg8_t<BASE_ADDRESS + 0x0009> {
        using DIGFILT = reg_field_t<BASE_ADDRESS + 0x0009, 0x07, 0, DIGFILTv>;    //< Digital Filter
    };

    /// Channel 2 Control Register - 1 bytes
    struct CH2CTRL : public reg8_t<BASE_ADDRESS + 0x000A> {
        using QDIRM = reg_field_t<BASE_ADDRESS + 0x000A, 0x60, 5, QDIRMv>;    //< Quadrature Decoder Index Recognition Mode
        using QDIEN = reg_field_t<BASE_ADDRESS + 0x000A, 0x10, 4>;    //< Quadrature Decoder Index Enable
        using QDEN = reg_field_t<BASE_ADDRESS + 0x000A, 0x08, 3>;    //< Quadrature Decoder Enable
        using DIGFILT = reg_field_t<BASE_ADDRESS + 0x000A, 0x07, 0, DIGFILTv>;    //< Digital Filter
    };

    /// Channel 3 Control Register - 1 bytes
    struct CH3CTRL : public reg8_t<BASE_ADDRESS + 0x000B> {
        using DIGFILT = reg_field_t<BASE_ADDRESS + 0x000B, 0x07, 0, DIGFILTv>;    //< Digital Filter
    };

    /// Channel 4 Control Register - 1 bytes
    struct CH4CTRL : public reg8_t<BASE_ADDRESS + 0x000C> {
        using QDIRM = reg_field_t<BASE_ADDRESS + 0x000C, 0x60, 5, QDIRMv>;    //< Quadrature Decoder Index Recognition Mode
        using QDIEN = reg_field_t<BASE_ADDRESS + 0x000C, 0x10, 4>;    //< Quadrature Decoder Index Enable
        using QDEN = reg_field_t<BASE_ADDRESS + 0x000C, 0x08, 3>;    //< Quadrature Decoder Enable
        using DIGFILT = reg_field_t<BASE_ADDRESS + 0x000C, 0x07, 0, DIGFILTv>;    //< Digital Filter
    };

    /// Channel 5 Control Register - 1 bytes
    struct CH5CTRL : public reg8_t<BASE_ADDRESS + 0x000D> {
        using DIGFILT = reg_field_t<BASE_ADDRESS + 0x000D, 0x07, 0, DIGFILTv>;    //< Digital Filter
    };

    /// Channel 6 Control Register - 1 bytes
    struct CH6CTRL : public reg8_t<BASE_ADDRESS + 0x000E> {
        using DIGFILT = reg_field_t<BASE_ADDRESS + 0x000E, 0x07, 0, DIGFILTv>;    //< Digital Filter
    };

    /// Channel 7 Control Register - 1 bytes
    struct CH7CTRL : public reg8_t<BASE_ADDRESS + 0x000F> {
        using DIGFILT = reg_field_t<BASE_ADDRESS + 0x000F, 0x07, 0, DIGFILTv>;    //< Digital Filter
    };

    /// Event Strobe - 1 bytes
    struct STROBE : public reg8_t<BASE_ADDRESS + 0x0010> {
    };

    /// Event Data - 1 bytes
    struct DATA : public reg8_t<BASE_ADDRESS + 0x0011> {
    };
};

} // namespace device
