#pragma once

#include "peripherals/AC.hpp"
#include "peripherals/ADC.hpp"
#include "peripherals/AES.hpp"
#include "peripherals/AWEX.hpp"
#include "peripherals/CLK.hpp"
#include "peripherals/CPU.hpp"
#include "peripherals/CRC.hpp"
#include "peripherals/DAC.hpp"
#include "peripherals/DFLL.hpp"
#include "peripherals/DMA.hpp"
#include "peripherals/EBI.hpp"
#include "peripherals/EVSYS.hpp"
#include "peripherals/FUSE.hpp"
#include "peripherals/GPIO.hpp"
#include "peripherals/HIRES.hpp"
#include "peripherals/IRCOM.hpp"
#include "peripherals/LOCKBIT.hpp"
#include "peripherals/MCU.hpp"
#include "peripherals/NVM.hpp"
#include "peripherals/OSC.hpp"
#include "peripherals/PMIC.hpp"
#include "peripherals/PORT.hpp"
#include "peripherals/PORTCFG.hpp"
#include "peripherals/PR.hpp"
#include "peripherals/RST.hpp"
#include "peripherals/RTC.hpp"
#include "peripherals/SIGROW.hpp"
#include "peripherals/SLEEP.hpp"
#include "peripherals/SPI.hpp"
#include "peripherals/TC.hpp"
#include "peripherals/TC2.hpp"
#include "peripherals/TWI.hpp"
#include "peripherals/USART.hpp"
#include "peripherals/USB.hpp"
#include "peripherals/VPORT.hpp"
#include "peripherals/WDT.hpp"
#include "peripherals/XOCD.hpp"
#include "gpio.hpp"

//static constexpr UART_t<0x08A0, 0> UART_C0 = {};

namespace device {
    /********** Peripheral Instances. Mapped to memory. **********/
    static constexpr GPIO_t< 0x0000 > GPIO = {}        //  General Purpose IO Registers
    static constexpr VPORT_t< 0x0010 > VPORT0 = {}        //  Virtual Port 0
    static constexpr VPORT_t< 0x0014 > VPORT1 = {}        //  Virtual Port 1
    static constexpr VPORT_t< 0x0018 > VPORT2 = {}        //  Virtual Port 2
    static constexpr VPORT_t< 0x001C > VPORT3 = {}        //  Virtual Port 3
    static constexpr OCD_t< 0x002E > OCD = {}        //  On-Chip Debug System
    static constexpr CPU_t< 0x0030 > CPU = {}        //  CPU registers
    static constexpr CLK_t< 0x0040 > CLK = {}        //  Clock System
    static constexpr SLEEP_t< 0x0048 > SLEEP = {}        //  Sleep Controller
    static constexpr OSC_t< 0x0050 > OSC = {}        //  Oscillator
    static constexpr DFLL_t< 0x0060 > DFLLRC32M = {}        //  DFLL RC32M
    static constexpr DFLL_t< 0x0068 > DFLLRC2M = {}        //  DFLL RC2M
    static constexpr PR_t< 0x0070 > PR = {}        //  Power Reduction
    static constexpr RST_t< 0x0078 > RST = {}        //  Reset
    static constexpr WDT_t< 0x0080 > WDT = {}        //  Watch-Dog Timer
    static constexpr MCU_t< 0x0090 > MCU = {}        //  MCU Control
    static constexpr PMIC_t< 0x00A0 > PMIC = {}        //  Programmable Multi-level Interrupt Controller
    static constexpr PORTCFG_t< 0x00B0 > PORTCFG = {}        //  I/O port Configuration
    static constexpr AES_t< 0x00C0 > AES = {}        //  AES Module
    static constexpr CRC_t< 0x00D0 > CRC = {}        //  Cyclic Redundancy Checker
    static constexpr DMA_t< 0x0100 > DMA = {}        //  DMA Controller
    static constexpr EVSYS_t< 0x0180 > EVSYS = {}        //  Event System
    static constexpr NVM_t< 0x01C0 > NVM = {}        //  Non-volatile Memory Controller
    static constexpr ADC_t< 0x0200 > ADCA = {}        //  Analog-to-Digital Converter A
    static constexpr ADC_t< 0x0240 > ADCB = {}        //  Analog-to-Digital Converter B
    static constexpr DAC_t< 0x0300 > DACA = {}        //  Digital-to-Analog Converter A
    static constexpr DAC_t< 0x0320 > DACB = {}        //  Digital-to-Analog Converter B
    static constexpr AC_t< 0x0380 > ACA = {}        //  Analog Comparator A
    static constexpr AC_t< 0x0390 > ACB = {}        //  Analog Comparator B
    static constexpr RTC_t< 0x0400 > RTC = {}        //  Real-Time Counter
    static constexpr EBI_t< 0x0440 > EBI = {}        //  External Bus Interface
    static constexpr TWI_t< 0x0480 > TWIC = {}        //  Two-Wire Interface C
    static constexpr TWI_t< 0x0490 > TWID = {}        //  Two-Wire Interface D
    static constexpr TWI_t< 0x04A0 > TWIE = {}        //  Two-Wire Interface E
    static constexpr TWI_t< 0x04B0 > TWIF = {}        //  Two-Wire Interface F
    static constexpr USB_t< 0x04C0 > USB = {}        //  Universal Serial Bus
    static constexpr PORT_t< 0x0600 > PORTA = {}        //  I/O Ports A
    static constexpr PORT_t< 0x0620 > PORTB = {}        //  I/O Ports B
    static constexpr PORT_t< 0x0640 > PORTC = {}        //  I/O Ports C
    static constexpr PORT_t< 0x0660 > PORTD = {}        //  I/O Ports D
    static constexpr PORT_t< 0x0680 > PORTE = {}        //  I/O Ports E
    static constexpr PORT_t< 0x06A0 > PORTF = {}        //  I/O Ports F
    static constexpr PORT_t< 0x06E0 > PORTH = {}        //  I/O Ports H
    static constexpr PORT_t< 0x0700 > PORTJ = {}        //  I/O Ports J
    static constexpr PORT_t< 0x0720 > PORTK = {}        //  I/O Ports K
    static constexpr PORT_t< 0x07C0 > PORTQ = {}        //  I/O Ports Q
    static constexpr PORT_t< 0x07E0 > PORTR = {}        //  I/O Ports R
    static constexpr TC0_t< 0x0800 > TCC0 = {}        //  16-bit Timer/Counter 0 C0
    static constexpr TC2_t< 0x0800 > TCC2 = {}        //  16-bit Timer/Counter type 2 C2
    static constexpr TC1_t< 0x0840 > TCC1 = {}        //  16-bit Timer/Counter 1 C1
    static constexpr AWEX_t< 0x0880 > AWEXC = {}        //  Advanced Waveform Extension C
    static constexpr HIRES_t< 0x0890 > HIRESC = {}        //  High-Resolution Extension C
    static constexpr USART_t< 0x08A0 > USARTC0 = {}        //  Universal Synchronous/Asynchronous Receiver/Transmitter C0
    static constexpr USART_t< 0x08B0 > USARTC1 = {}        //  Universal Synchronous/Asynchronous Receiver/Transmitter C1
    static constexpr SPI_t< 0x08C0 > SPIC = {}        //  Serial Peripheral Interface C
    static constexpr IRCOM_t< 0x08F8 > IRCOM = {}        //  IR Communication Module
    static constexpr TC0_t< 0x0900 > TCD0 = {}        //  16-bit Timer/Counter 0 D0
    static constexpr TC2_t< 0x0900 > TCD2 = {}        //  16-bit Timer/Counter type 2 D2
    static constexpr TC1_t< 0x0940 > TCD1 = {}        //  16-bit Timer/Counter 1 D1
    static constexpr HIRES_t< 0x0990 > HIRESD = {}        //  High-Resolution Extension D
    static constexpr USART_t< 0x09A0 > USARTD0 = {}        //  Universal Synchronous/Asynchronous Receiver/Transmitter D0
    static constexpr USART_t< 0x09B0 > USARTD1 = {}        //  Universal Synchronous/Asynchronous Receiver/Transmitter D1
    static constexpr SPI_t< 0x09C0 > SPID = {}        //  Serial Peripheral Interface D
    static constexpr TC0_t< 0x0A00 > TCE0 = {}        //  16-bit Timer/Counter 0 E0
    static constexpr TC2_t< 0x0A00 > TCE2 = {}        //  16-bit Timer/Counter type 2 E2
    static constexpr TC1_t< 0x0A40 > TCE1 = {}        //  16-bit Timer/Counter 1 E1
    static constexpr AWEX_t< 0x0A80 > AWEXE = {}        //  Advanced Waveform Extension E
    static constexpr HIRES_t< 0x0A90 > HIRESE = {}        //  High-Resolution Extension E
    static constexpr USART_t< 0x0AA0 > USARTE0 = {}        //  Universal Synchronous/Asynchronous Receiver/Transmitter E0
    static constexpr USART_t< 0x0AB0 > USARTE1 = {}        //  Universal Synchronous/Asynchronous Receiver/Transmitter E1
    static constexpr SPI_t< 0x0AC0 > SPIE = {}        //  Serial Peripheral Interface E
    static constexpr TC0_t< 0x0B00 > TCF0 = {}        //  16-bit Timer/Counter 0 F0
    static constexpr TC2_t< 0x0B00 > TCF2 = {}        //  16-bit Timer/Counter type 2 F2
    static constexpr TC1_t< 0x0B40 > TCF1 = {}        //  16-bit Timer/Counter 1 F1
    static constexpr HIRES_t< 0x0B90 > HIRESF = {}        //  High-Resolution Extension F
    static constexpr USART_t< 0x0BA0 > USARTF0 = {}        //  Universal Synchronous/Asynchronous Receiver/Transmitter F0
    static constexpr USART_t< 0x0BB0 > USARTF1 = {}        //  Universal Synchronous/Asynchronous Receiver/Transmitter F1
    static constexpr SPI_t< 0x0BC0 > SPIF = {}        //  Serial Peripheral Interface F

    /********** GPIO PINS **********/
    static constexpr gpio_pin< PORTA::tag_type, 0 > PA0 = {};
    static constexpr gpio_pin< PORTA::tag_type, 1 > PA1 = {};
    static constexpr gpio_pin< PORTA::tag_type, 2 > PA2 = {};
    static constexpr gpio_pin< PORTA::tag_type, 3 > PA3 = {};
    static constexpr gpio_pin< PORTA::tag_type, 4 > PA4 = {};
    static constexpr gpio_pin< PORTA::tag_type, 5 > PA5 = {};
    static constexpr gpio_pin< PORTA::tag_type, 6 > PA6 = {};
    static constexpr gpio_pin< PORTA::tag_type, 7 > PA7 = {};

    static constexpr gpio_pin< PORTB::tag_type, 0 > PB0 = {};
    static constexpr gpio_pin< PORTB::tag_type, 1 > PB1 = {};
    static constexpr gpio_pin< PORTB::tag_type, 2 > PB2 = {};
    static constexpr gpio_pin< PORTB::tag_type, 3 > PB3 = {};
    static constexpr gpio_pin< PORTB::tag_type, 4 > PB4 = {};
    static constexpr gpio_pin< PORTB::tag_type, 5 > PB5 = {};
    static constexpr gpio_pin< PORTB::tag_type, 6 > PB6 = {};
    static constexpr gpio_pin< PORTB::tag_type, 7 > PB7 = {};

    static constexpr gpio_pin< PORTC::tag_type, 0 > PC0 = {};
    static constexpr gpio_pin< PORTC::tag_type, 1 > PC1 = {};
    static constexpr gpio_pin< PORTC::tag_type, 2 > PC2 = {};
    static constexpr gpio_pin< PORTC::tag_type, 3 > PC3 = {};
    static constexpr gpio_pin< PORTC::tag_type, 4 > PC4 = {};
    static constexpr gpio_pin< PORTC::tag_type, 5 > PC5 = {};
    static constexpr gpio_pin< PORTC::tag_type, 6 > PC6 = {};
    static constexpr gpio_pin< PORTC::tag_type, 7 > PC7 = {};

    static constexpr gpio_pin< PORTD::tag_type, 0 > PD0 = {};
    static constexpr gpio_pin< PORTD::tag_type, 1 > PD1 = {};
    static constexpr gpio_pin< PORTD::tag_type, 2 > PD2 = {};
    static constexpr gpio_pin< PORTD::tag_type, 3 > PD3 = {};
    static constexpr gpio_pin< PORTD::tag_type, 4 > PD4 = {};
    static constexpr gpio_pin< PORTD::tag_type, 5 > PD5 = {};
    static constexpr gpio_pin< PORTD::tag_type, 6 > PD6 = {};
    static constexpr gpio_pin< PORTD::tag_type, 7 > PD7 = {};

    static constexpr gpio_pin< PORTE::tag_type, 0 > PE0 = {};
    static constexpr gpio_pin< PORTE::tag_type, 1 > PE1 = {};
    static constexpr gpio_pin< PORTE::tag_type, 2 > PE2 = {};
    static constexpr gpio_pin< PORTE::tag_type, 3 > PE3 = {};
    static constexpr gpio_pin< PORTE::tag_type, 4 > PE4 = {};
    static constexpr gpio_pin< PORTE::tag_type, 5 > PE5 = {};
    static constexpr gpio_pin< PORTE::tag_type, 6 > PE6 = {};
    static constexpr gpio_pin< PORTE::tag_type, 7 > PE7 = {};

    static constexpr gpio_pin< PORTF::tag_type, 0 > PF0 = {};
    static constexpr gpio_pin< PORTF::tag_type, 1 > PF1 = {};
    static constexpr gpio_pin< PORTF::tag_type, 2 > PF2 = {};
    static constexpr gpio_pin< PORTF::tag_type, 3 > PF3 = {};
    static constexpr gpio_pin< PORTF::tag_type, 4 > PF4 = {};
    static constexpr gpio_pin< PORTF::tag_type, 5 > PF5 = {};
    static constexpr gpio_pin< PORTF::tag_type, 6 > PF6 = {};
    static constexpr gpio_pin< PORTF::tag_type, 7 > PF7 = {};

    static constexpr gpio_pin< PORTH::tag_type, 0 > PH0 = {};
    static constexpr gpio_pin< PORTH::tag_type, 1 > PH1 = {};
    static constexpr gpio_pin< PORTH::tag_type, 2 > PH2 = {};
    static constexpr gpio_pin< PORTH::tag_type, 3 > PH3 = {};
    static constexpr gpio_pin< PORTH::tag_type, 4 > PH4 = {};
    static constexpr gpio_pin< PORTH::tag_type, 5 > PH5 = {};
    static constexpr gpio_pin< PORTH::tag_type, 6 > PH6 = {};
    static constexpr gpio_pin< PORTH::tag_type, 7 > PH7 = {};

    static constexpr gpio_pin< PORTJ::tag_type, 0 > PJ0 = {};
    static constexpr gpio_pin< PORTJ::tag_type, 1 > PJ1 = {};
    static constexpr gpio_pin< PORTJ::tag_type, 2 > PJ2 = {};
    static constexpr gpio_pin< PORTJ::tag_type, 3 > PJ3 = {};
    static constexpr gpio_pin< PORTJ::tag_type, 4 > PJ4 = {};
    static constexpr gpio_pin< PORTJ::tag_type, 5 > PJ5 = {};
    static constexpr gpio_pin< PORTJ::tag_type, 6 > PJ6 = {};
    static constexpr gpio_pin< PORTJ::tag_type, 7 > PJ7 = {};

    static constexpr gpio_pin< PORTK::tag_type, 0 > PK0 = {};
    static constexpr gpio_pin< PORTK::tag_type, 1 > PK1 = {};
    static constexpr gpio_pin< PORTK::tag_type, 2 > PK2 = {};
    static constexpr gpio_pin< PORTK::tag_type, 3 > PK3 = {};
    static constexpr gpio_pin< PORTK::tag_type, 4 > PK4 = {};
    static constexpr gpio_pin< PORTK::tag_type, 5 > PK5 = {};
    static constexpr gpio_pin< PORTK::tag_type, 6 > PK6 = {};
    static constexpr gpio_pin< PORTK::tag_type, 7 > PK7 = {};

    static constexpr gpio_pin< PORTQ::tag_type, 0 > PQ0 = {};
    static constexpr gpio_pin< PORTQ::tag_type, 1 > PQ1 = {};
    static constexpr gpio_pin< PORTQ::tag_type, 2 > PQ2 = {};
    static constexpr gpio_pin< PORTQ::tag_type, 3 > PQ3 = {};

    static constexpr gpio_pin< PORTR::tag_type, 0 > PR0 = {};
    static constexpr gpio_pin< PORTR::tag_type, 1 > PR1 = {};
}   // namespace device
