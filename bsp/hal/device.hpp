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

namespace device {
    /********** Peripheral Instances. Mapped to memory. **********/
    inline constexpr sfr::GPIO_t< 0x0000 > GPIO = {};       //  General Purpose IO Registers
    inline constexpr sfr::VPORT_t< 0x0010 > VPORT0 = {};    //  Virtual Port 0
    inline constexpr sfr::VPORT_t< 0x0014 > VPORT1 = {};    //  Virtual Port 1
    inline constexpr sfr::VPORT_t< 0x0018 > VPORT2 = {};    //  Virtual Port 2
    inline constexpr sfr::VPORT_t< 0x001C > VPORT3 = {};    //  Virtual Port 3
    inline constexpr sfr::OCD_t< 0x002E > OCD = {};         //  On-Chip Debug System
    inline constexpr sfr::CPU_t< 0x0030 > CPU = {};         //  CPU registers
    inline constexpr sfr::CLK_t< 0x0040 > CLK = {};         //  Clock System
    inline constexpr sfr::SLEEP_t< 0x0048 > SLEEP = {};     //  Sleep Controller
    inline constexpr sfr::OSC_t< 0x0050 > OSC = {};         //  Oscillator
    inline constexpr sfr::DFLL_t< 0x0060 > DFLLRC32M = {};  //  DFLL RC32M
    inline constexpr sfr::DFLL_t< 0x0068 > DFLLRC2M = {};   //  DFLL RC2M
    inline constexpr sfr::PR_t< 0x0070 > PR = {};           //  Power Reduction
    inline constexpr sfr::RST_t< 0x0078 > RST = {};         //  Reset
    inline constexpr sfr::WDT_t< 0x0080 > WDT = {};         //  Watch-Dog Timer
    inline constexpr sfr::MCU_t< 0x0090 > MCU = {};         //  MCU Control
    inline constexpr sfr::PMIC_t< 0x00A0 > PMIC = {};       //  Programmable Multi-level Interrupt Controller
    inline constexpr sfr::PORTCFG_t< 0x00B0 > PORTCFG = {}; //  I/O port Configuration
    inline constexpr sfr::AES_t< 0x00C0 > AES = {};         //  AES Module
    inline constexpr sfr::CRC_t< 0x00D0 > CRC = {};         //  Cyclic Redundancy Checker
    inline constexpr sfr::DMA_t< 0x0100 > DMA = {};         //  DMA Controller
    inline constexpr sfr::EVSYS_t< 0x0180 > EVSYS = {};     //  Event System
    inline constexpr sfr::NVM_t< 0x01C0 > NVM = {};         //  Non-volatile Memory Controller
    inline constexpr sfr::ADC_t< 0x0200 > ADCA = {};        //  Analog-to-Digital Converter A
    inline constexpr sfr::ADC_t< 0x0240 > ADCB = {};        //  Analog-to-Digital Converter B
    inline constexpr sfr::DAC_t< 0x0300 > DACA = {};        //  Digital-to-Analog Converter A
    inline constexpr sfr::DAC_t< 0x0320 > DACB = {};        //  Digital-to-Analog Converter B
    inline constexpr sfr::AC_t< 0x0380 > ACA = {};          //  Analog Comparator A
    inline constexpr sfr::AC_t< 0x0390 > ACB = {};          //  Analog Comparator B
    inline constexpr sfr::RTC_t< 0x0400 > RTC = {};         //  Real-Time Counter
    inline constexpr sfr::EBI_t< 0x0440 > EBI = {};         //  External Bus Interface
    inline constexpr sfr::TWI_t< 0x0480 > TWIC = {};        //  Two-Wire Interface C
    inline constexpr sfr::TWI_t< 0x0490 > TWID = {};        //  Two-Wire Interface D
    inline constexpr sfr::TWI_t< 0x04A0 > TWIE = {};        //  Two-Wire Interface E
    inline constexpr sfr::TWI_t< 0x04B0 > TWIF = {};        //  Two-Wire Interface F
    inline constexpr sfr::USB_t< 0x04C0 > USB = {};         //  Universal Serial Bus
    inline constexpr sfr::PORT_t< 0x0600 > PORTA = {};      //  I/O Ports A
    inline constexpr sfr::PORT_t< 0x0620 > PORTB = {};      //  I/O Ports B
    inline constexpr sfr::PORT_t< 0x0640 > PORTC = {};      //  I/O Ports C
    inline constexpr sfr::PORT_t< 0x0660 > PORTD = {};      //  I/O Ports D
    inline constexpr sfr::PORT_t< 0x0680 > PORTE = {};      //  I/O Ports E
    inline constexpr sfr::PORT_t< 0x06A0 > PORTF = {};      //  I/O Ports F
    inline constexpr sfr::PORT_t< 0x06E0 > PORTH = {};      //  I/O Ports H
    inline constexpr sfr::PORT_t< 0x0700 > PORTJ = {};      //  I/O Ports J
    inline constexpr sfr::PORT_t< 0x0720 > PORTK = {};      //  I/O Ports K
    inline constexpr sfr::PORT_t< 0x07C0 > PORTQ = {};      //  I/O Ports Q
    inline constexpr sfr::PORT_t< 0x07E0 > PORTR = {};      //  I/O Ports R
    inline constexpr sfr::TC0_t< 0x0800 > TCC0 = {};        //  16-bit Timer/Counter 0 C0
    inline constexpr sfr::TC2_t< 0x0800 > TCC2 = {};        //  16-bit Timer/Counter type 2 C2
    inline constexpr sfr::TC1_t< 0x0840 > TCC1 = {};        //  16-bit Timer/Counter 1 C1
    inline constexpr sfr::AWEX_t< 0x0880 > AWEXC = {};      //  Advanced Waveform Extension C
    inline constexpr sfr::HIRES_t< 0x0890 > HIRESC = {};    //  High-Resolution Extension C
    inline constexpr sfr::USART_t< 0x08A0 > USARTC0 = {};   //  Universal Synchronous/Asynchronous Receiver/Transmitter C0
    inline constexpr sfr::USART_t< 0x08B0 > USARTC1 = {};   //  Universal Synchronous/Asynchronous Receiver/Transmitter C1
    inline constexpr sfr::SPI_t< 0x08C0 > SPIC = {};        //  Serial Peripheral Interface C
    inline constexpr sfr::IRCOM_t< 0x08F8 > IRCOM = {};     //  IR Communication Module
    inline constexpr sfr::TC0_t< 0x0900 > TCD0 = {};        //  16-bit Timer/Counter 0 D0
    inline constexpr sfr::TC2_t< 0x0900 > TCD2 = {};        //  16-bit Timer/Counter type 2 D2
    inline constexpr sfr::TC1_t< 0x0940 > TCD1 = {};        //  16-bit Timer/Counter 1 D1
    inline constexpr sfr::HIRES_t< 0x0990 > HIRESD = {};    //  High-Resolution Extension D
    inline constexpr sfr::USART_t< 0x09A0 > USARTD0 = {};   //  Universal Synchronous/Asynchronous Receiver/Transmitter D0
    inline constexpr sfr::USART_t< 0x09B0 > USARTD1 = {};   //  Universal Synchronous/Asynchronous Receiver/Transmitter D1
    inline constexpr sfr::SPI_t< 0x09C0 > SPID = {};        //  Serial Peripheral Interface D
    inline constexpr sfr::TC0_t< 0x0A00 > TCE0 = {};        //  16-bit Timer/Counter 0 E0
    inline constexpr sfr::TC2_t< 0x0A00 > TCE2 = {};        //  16-bit Timer/Counter type 2 E2
    inline constexpr sfr::TC1_t< 0x0A40 > TCE1 = {};        //  16-bit Timer/Counter 1 E1
    inline constexpr sfr::AWEX_t< 0x0A80 > AWEXE = {};      //  Advanced Waveform Extension E
    inline constexpr sfr::HIRES_t< 0x0A90 > HIRESE = {};    //  High-Resolution Extension E
    inline constexpr sfr::USART_t< 0x0AA0 > USARTE0 = {};   //  Universal Synchronous/Asynchronous Receiver/Transmitter E0
    inline constexpr sfr::USART_t< 0x0AB0 > USARTE1 = {};   //  Universal Synchronous/Asynchronous Receiver/Transmitter E1
    inline constexpr sfr::SPI_t< 0x0AC0 > SPIE = {};        //  Serial Peripheral Interface E
    inline constexpr sfr::TC0_t< 0x0B00 > TCF0 = {};        //  16-bit Timer/Counter 0 F0
    inline constexpr sfr::TC2_t< 0x0B00 > TCF2 = {};        //  16-bit Timer/Counter type 2 F2
    inline constexpr sfr::TC1_t< 0x0B40 > TCF1 = {};        //  16-bit Timer/Counter 1 F1
    inline constexpr sfr::HIRES_t< 0x0B90 > HIRESF = {};    //  High-Resolution Extension F
    inline constexpr sfr::USART_t< 0x0BA0 > USARTF0 = {};   //  Universal Synchronous/Asynchronous Receiver/Transmitter F0
    inline constexpr sfr::USART_t< 0x0BB0 > USARTF1 = {};   //  Universal Synchronous/Asynchronous Receiver/Transmitter F1
    inline constexpr sfr::SPI_t< 0x0BC0 > SPIF = {};        //  Serial Peripheral Interface F

    /********** GPIO PINS **********/
    inline constexpr gpio_pin< decltype(PORTA), 0 > PA0 = {};
    inline constexpr gpio_pin< decltype(PORTA), 1 > PA1 = {};
    inline constexpr gpio_pin< decltype(PORTA), 2 > PA2 = {};
    inline constexpr gpio_pin< decltype(PORTA), 3 > PA3 = {};
    inline constexpr gpio_pin< decltype(PORTA), 4 > PA4 = {};
    inline constexpr gpio_pin< decltype(PORTA), 5 > PA5 = {};
    inline constexpr gpio_pin< decltype(PORTA), 6 > PA6 = {};
    inline constexpr gpio_pin< decltype(PORTA), 7 > PA7 = {};

    inline constexpr gpio_pin< decltype(PORTB), 0 > PB0 = {};
    inline constexpr gpio_pin< decltype(PORTB), 1 > PB1 = {};
    inline constexpr gpio_pin< decltype(PORTB), 2 > PB2 = {};
    inline constexpr gpio_pin< decltype(PORTB), 3 > PB3 = {};
    inline constexpr gpio_pin< decltype(PORTB), 4 > PB4 = {};
    inline constexpr gpio_pin< decltype(PORTB), 5 > PB5 = {};
    inline constexpr gpio_pin< decltype(PORTB), 6 > PB6 = {};
    inline constexpr gpio_pin< decltype(PORTB), 7 > PB7 = {};

    inline constexpr gpio_pin< decltype(PORTC), 0 > PC0 = {};
    inline constexpr gpio_pin< decltype(PORTC), 1 > PC1 = {};
    inline constexpr gpio_pin< decltype(PORTC), 2 > PC2 = {};
    inline constexpr gpio_pin< decltype(PORTC), 3 > PC3 = {};
    inline constexpr gpio_pin< decltype(PORTC), 4 > PC4 = {};
    inline constexpr gpio_pin< decltype(PORTC), 5 > PC5 = {};
    inline constexpr gpio_pin< decltype(PORTC), 6 > PC6 = {};
    inline constexpr gpio_pin< decltype(PORTC), 7 > PC7 = {};

    inline constexpr gpio_pin< decltype(PORTD), 0 > PD0 = {};
    inline constexpr gpio_pin< decltype(PORTD), 1 > PD1 = {};
    inline constexpr gpio_pin< decltype(PORTD), 2 > PD2 = {};
    inline constexpr gpio_pin< decltype(PORTD), 3 > PD3 = {};
    inline constexpr gpio_pin< decltype(PORTD), 4 > PD4 = {};
    inline constexpr gpio_pin< decltype(PORTD), 5 > PD5 = {};
    inline constexpr gpio_pin< decltype(PORTD), 6 > PD6 = {};
    inline constexpr gpio_pin< decltype(PORTD), 7 > PD7 = {};

    inline constexpr gpio_pin< decltype(PORTE), 0 > PE0 = {};
    inline constexpr gpio_pin< decltype(PORTE), 1 > PE1 = {};
    inline constexpr gpio_pin< decltype(PORTE), 2 > PE2 = {};
    inline constexpr gpio_pin< decltype(PORTE), 3 > PE3 = {};
    inline constexpr gpio_pin< decltype(PORTE), 4 > PE4 = {};
    inline constexpr gpio_pin< decltype(PORTE), 5 > PE5 = {};
    inline constexpr gpio_pin< decltype(PORTE), 6 > PE6 = {};
    inline constexpr gpio_pin< decltype(PORTE), 7 > PE7 = {};

    inline constexpr gpio_pin< decltype(PORTF), 0 > PF0 = {};
    inline constexpr gpio_pin< decltype(PORTF), 1 > PF1 = {};
    inline constexpr gpio_pin< decltype(PORTF), 2 > PF2 = {};
    inline constexpr gpio_pin< decltype(PORTF), 3 > PF3 = {};
    inline constexpr gpio_pin< decltype(PORTF), 4 > PF4 = {};
    inline constexpr gpio_pin< decltype(PORTF), 5 > PF5 = {};
    inline constexpr gpio_pin< decltype(PORTF), 6 > PF6 = {};
    inline constexpr gpio_pin< decltype(PORTF), 7 > PF7 = {};

    inline constexpr gpio_pin< decltype(PORTH), 0 > PH0 = {};
    inline constexpr gpio_pin< decltype(PORTH), 1 > PH1 = {};
    inline constexpr gpio_pin< decltype(PORTH), 2 > PH2 = {};
    inline constexpr gpio_pin< decltype(PORTH), 3 > PH3 = {};
    inline constexpr gpio_pin< decltype(PORTH), 4 > PH4 = {};
    inline constexpr gpio_pin< decltype(PORTH), 5 > PH5 = {};
    inline constexpr gpio_pin< decltype(PORTH), 6 > PH6 = {};
    inline constexpr gpio_pin< decltype(PORTH), 7 > PH7 = {};

    inline constexpr gpio_pin< decltype(PORTJ), 0 > PJ0 = {};
    inline constexpr gpio_pin< decltype(PORTJ), 1 > PJ1 = {};
    inline constexpr gpio_pin< decltype(PORTJ), 2 > PJ2 = {};
    inline constexpr gpio_pin< decltype(PORTJ), 3 > PJ3 = {};
    inline constexpr gpio_pin< decltype(PORTJ), 4 > PJ4 = {};
    inline constexpr gpio_pin< decltype(PORTJ), 5 > PJ5 = {};
    inline constexpr gpio_pin< decltype(PORTJ), 6 > PJ6 = {};
    inline constexpr gpio_pin< decltype(PORTJ), 7 > PJ7 = {};

    inline constexpr gpio_pin< decltype(PORTK), 0 > PK0 = {};
    inline constexpr gpio_pin< decltype(PORTK), 1 > PK1 = {};
    inline constexpr gpio_pin< decltype(PORTK), 2 > PK2 = {};
    inline constexpr gpio_pin< decltype(PORTK), 3 > PK3 = {};
    inline constexpr gpio_pin< decltype(PORTK), 4 > PK4 = {};
    inline constexpr gpio_pin< decltype(PORTK), 5 > PK5 = {};
    inline constexpr gpio_pin< decltype(PORTK), 6 > PK6 = {};
    inline constexpr gpio_pin< decltype(PORTK), 7 > PK7 = {};

    inline constexpr gpio_pin< decltype(PORTQ), 0 > PQ0 = {};
    inline constexpr gpio_pin< decltype(PORTQ), 1 > PQ1 = {};
    inline constexpr gpio_pin< decltype(PORTQ), 2 > PQ2 = {};
    inline constexpr gpio_pin< decltype(PORTQ), 3 > PQ3 = {};

    inline constexpr gpio_pin< decltype(PORTR), 0 > PR0 = {};
    inline constexpr gpio_pin< decltype(PORTR), 1 > PR1 = {};
}   // namespace device
