#ifndef SEAL_HAL_DEVICE_FILE_XMEGA128A1U
#define SEAL_HAL_DEVICE_FILE_XMEGA128A1U

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
using GPIO      = device::GPIO_t< 0x0000 >;     // General Purpose IO Registers
using VPORT0    = device::VPORT_t< 0x0010 >;    // Virtual Port 0
using VPORT1    = device::VPORT_t< 0x0014 >;    // Virtual Port 1
using VPORT2    = device::VPORT_t< 0x0018 >;    // Virtual Port 2
using VPORT3    = device::VPORT_t< 0x001C >;    // Virtual Port 3
using OCD       = device::OCD_t< 0x002E >;      // On-Chip Debug System
using CPU       = device::CPU_t< 0x0030 >;      // CPU registers
using CLK       = device::CLK_t< 0x0040 >;      // Clock System
using SLEEP     = device::SLEEP_t< 0x0048 >;    // Sleep Controller
using OSC       = device::OSC_t< 0x0050 >;      // Oscillator
using DFLLRC32M = device::DFLL_t< 0x0060 >;     // DFLL RC32M
using DFLLRC2M  = device::DFLL_t< 0x0068 >;     // DFLL RC2M
using PR        = device::PR_t< 0x0070 >;       // Power Reduction
using RST       = device::RST_t< 0x0078 >;      // Reset
using WDT       = device::WDT_t< 0x0080 >;      // Watch-Dog Timer
using MCU       = device::MCU_t< 0x0090 >;      // MCU Control
using PMIC      = device::PMIC_t< 0x00A0 >;     // Programmable Multi-level Interrupt Controller
using PORTCFG   = device::PORTCFG_t< 0x00B0 >;  // I/O port Configuration
using AES       = device::AES_t< 0x00C0 >;      // AES Module
using CRC       = device::CRC_t< 0x00D0 >;      // Cyclic Redundancy Checker
using DMA       = device::DMA_t< 0x0100 >;      // DMA Controller
using EVSYS     = device::EVSYS_t< 0x0180 >;    // Event System
using NVM       = device::NVM_t< 0x01C0 >;      // Non-volatile Memory Controller
using ADCA      = device::ADC_t< 0x0200 >;      // Analog-to-Digital Converter A
using ADCB      = device::ADC_t< 0x0240 >;      // Analog-to-Digital Converter B
using DACA      = device::DAC_t< 0x0300 >;      // Digital-to-Analog Converter A
using DACB      = device::DAC_t< 0x0320 >;      // Digital-to-Analog Converter B
using ACA       = device::AC_t< 0x0380 >;       // Analog Comparator A
using ACB       = device::AC_t< 0x0390 >;       // Analog Comparator B
using RTC       = device::RTC_t< 0x0400 >;      // Real-Time Counter
using EBI       = device::EBI_t< 0x0440 >;      // External Bus Interface
using TWIC      = device::TWI_t< 0x0480 >;      // Two-Wire Interface C
using TWID      = device::TWI_t< 0x0490 >;      // Two-Wire Interface D
using TWIE      = device::TWI_t< 0x04A0 >;      // Two-Wire Interface E
using TWIF      = device::TWI_t< 0x04B0 >;      // Two-Wire Interface F
using USB       = device::USB_t< 0x04C0 >;      // Universal Serial Bus
using PORTA     = device::PORT_t< 0x0600 >;     // I/O Ports A
using PORTB     = device::PORT_t< 0x0620 >;     // I/O Ports B
using PORTC     = device::PORT_t< 0x0640 >;     // I/O Ports C
using PORTD     = device::PORT_t< 0x0660 >;     // I/O Ports D
using PORTE     = device::PORT_t< 0x0680 >;     // I/O Ports E
using PORTF     = device::PORT_t< 0x06A0 >;     // I/O Ports F
using PORTH     = device::PORT_t< 0x06E0 >;     // I/O Ports H
using PORTJ     = device::PORT_t< 0x0700 >;     // I/O Ports J
using PORTK     = device::PORT_t< 0x0720 >;     // I/O Ports K
using PORTQ     = device::PORT_t< 0x07C0 >;     // I/O Ports Q
using PORTR     = device::PORT_t< 0x07E0 >;     // I/O Ports R
using TCC0      = device::TC0_t< 0x0800 >;      // 16-bit Timer/Counter 0 C0
using TCC2      = device::TC2_t< 0x0800 >;      // 16-bit Timer/Counter type 2 C2
using TCC1      = device::TC1_t< 0x0840 >;      // 16-bit Timer/Counter 1 C1
using AWEXC     = device::AWEX_t< 0x0880 >;     // Advanced Waveform Extension C
using HIRESC    = device::HIRES_t< 0x0890 >;    // High-Resolution Extension C
using USARTC0   = device::USART_t< 0x08A0 >;    // Universal Synchronous/Asynchronous Receiver/Transmitter C0
using USARTC1   = device::USART_t< 0x08B0 >;    // Universal Synchronous/Asynchronous Receiver/Transmitter C1
using SPIC      = device::SPI_t< 0x08C0 >;      // Serial Peripheral Interface C
using IRCOM     = device::IRCOM_t< 0x08F8 >;    // IR Communication Module
using TCD0      = device::TC0_t< 0x0900 >;      // 16-bit Timer/Counter 0 D0
using TCD2      = device::TC2_t< 0x0900 >;      // 16-bit Timer/Counter type 2 D2
using TCD1      = device::TC1_t< 0x0940 >;      // 16-bit Timer/Counter 1 D1
using HIRESD    = device::HIRES_t< 0x0990 >;    // High-Resolution Extension D
using USARTD0   = device::USART_t< 0x09A0 >;    // Universal Synchronous/Asynchronous Receiver/Transmitter D0
using USARTD1   = device::USART_t< 0x09B0 >;    // Universal Synchronous/Asynchronous Receiver/Transmitter D1
using SPID      = device::SPI_t< 0x09C0 >;      // Serial Peripheral Interface D
using TCE0      = device::TC0_t< 0x0A00 >;      // 16-bit Timer/Counter 0 E0
using TCE2      = device::TC2_t< 0x0A00 >;      // 16-bit Timer/Counter type 2 E2
using TCE1      = device::TC1_t< 0x0A40 >;      // 16-bit Timer/Counter 1 E1
using AWEXE     = device::AWEX_t< 0x0A80 >;     // Advanced Waveform Extension E
using HIRESE    = device::HIRES_t< 0x0A90 >;    // High-Resolution Extension E
using USARTE0   = device::USART_t< 0x0AA0 >;    // Universal Synchronous/Asynchronous Receiver/Transmitter E0
using USARTE1   = device::USART_t< 0x0AB0 >;    // Universal Synchronous/Asynchronous Receiver/Transmitter E1
using SPIE      = device::SPI_t< 0x0AC0 >;      // Serial Peripheral Interface E
using TCF0      = device::TC0_t< 0x0B00 >;      // 16-bit Timer/Counter 0 F0
using TCF2      = device::TC2_t< 0x0B00 >;      // 16-bit Timer/Counter type 2 F2
using TCF1      = device::TC1_t< 0x0B40 >;      // 16-bit Timer/Counter 1 F1
using HIRESF    = device::HIRES_t< 0x0B90 >;    // High-Resolution Extension F
using USARTF0   = device::USART_t< 0x0BA0 >;    // Universal Synchronous/Asynchronous Receiver/Transmitter F0
using USARTF1   = device::USART_t< 0x0BB0 >;    // Universal Synchronous/Asynchronous Receiver/Transmitter F1
using SPIF      = device::SPI_t< 0x0BC0 >;      // Serial Peripheral Interface F

/********** GPIO PINS **********/
using PA0 = gpio_pin< PORTA, 0 >;
using PA1 = gpio_pin< PORTA, 1 >;
using PA2 = gpio_pin< PORTA, 2 >;
using PA3 = gpio_pin< PORTA, 3 >;
using PA4 = gpio_pin< PORTA, 4 >;
using PA5 = gpio_pin< PORTA, 5 >;
using PA6 = gpio_pin< PORTA, 6 >;
using PA7 = gpio_pin< PORTA, 7 >;

using PB0 = gpio_pin< PORTB, 0 >;
using PB1 = gpio_pin< PORTB, 1 >;
using PB2 = gpio_pin< PORTB, 2 >;
using PB3 = gpio_pin< PORTB, 3 >;
using PB4 = gpio_pin< PORTB, 4 >;
using PB5 = gpio_pin< PORTB, 5 >;
using PB6 = gpio_pin< PORTB, 6 >;
using PB7 = gpio_pin< PORTB, 7 >;

using PC0 = gpio_pin< PORTC, 0 >;
using PC1 = gpio_pin< PORTC, 1 >;
using PC2 = gpio_pin< PORTC, 2 >;
using PC3 = gpio_pin< PORTC, 3 >;
using PC4 = gpio_pin< PORTC, 4 >;
using PC5 = gpio_pin< PORTC, 5 >;
using PC6 = gpio_pin< PORTC, 6 >;
using PC7 = gpio_pin< PORTC, 7 >;

using PD0 = gpio_pin< PORTD, 0 >;
using PD1 = gpio_pin< PORTD, 1 >;
using PD2 = gpio_pin< PORTD, 2 >;
using PD3 = gpio_pin< PORTD, 3 >;
using PD4 = gpio_pin< PORTD, 4 >;
using PD5 = gpio_pin< PORTD, 5 >;
using PD6 = gpio_pin< PORTD, 6 >;
using PD7 = gpio_pin< PORTD, 7 >;

using PE0 = gpio_pin< PORTE, 0 >;
using PE1 = gpio_pin< PORTE, 1 >;
using PE2 = gpio_pin< PORTE, 2 >;
using PE3 = gpio_pin< PORTE, 3 >;
using PE4 = gpio_pin< PORTE, 4 >;
using PE5 = gpio_pin< PORTE, 5 >;
using PE6 = gpio_pin< PORTE, 6 >;
using PE7 = gpio_pin< PORTE, 7 >;

using PF0 = gpio_pin< PORTF, 0 >;
using PF1 = gpio_pin< PORTF, 1 >;
using PF2 = gpio_pin< PORTF, 2 >;
using PF3 = gpio_pin< PORTF, 3 >;
using PF4 = gpio_pin< PORTF, 4 >;
using PF5 = gpio_pin< PORTF, 5 >;
using PF6 = gpio_pin< PORTF, 6 >;
using PF7 = gpio_pin< PORTF, 7 >;

using PH0 = gpio_pin< PORTH, 0 >;
using PH1 = gpio_pin< PORTH, 1 >;
using PH2 = gpio_pin< PORTH, 2 >;
using PH3 = gpio_pin< PORTH, 3 >;
using PH4 = gpio_pin< PORTH, 4 >;
using PH5 = gpio_pin< PORTH, 5 >;
using PH6 = gpio_pin< PORTH, 6 >;
using PH7 = gpio_pin< PORTH, 7 >;

using PJ0 = gpio_pin< PORTJ, 0 >;
using PJ1 = gpio_pin< PORTJ, 1 >;
using PJ2 = gpio_pin< PORTJ, 2 >;
using PJ3 = gpio_pin< PORTJ, 3 >;
using PJ4 = gpio_pin< PORTJ, 4 >;
using PJ5 = gpio_pin< PORTJ, 5 >;
using PJ6 = gpio_pin< PORTJ, 6 >;
using PJ7 = gpio_pin< PORTJ, 7 >;

using PK0 = gpio_pin< PORTK, 0 >;
using PK1 = gpio_pin< PORTK, 1 >;
using PK2 = gpio_pin< PORTK, 2 >;
using PK3 = gpio_pin< PORTK, 3 >;
using PK4 = gpio_pin< PORTK, 4 >;
using PK5 = gpio_pin< PORTK, 5 >;
using PK6 = gpio_pin< PORTK, 6 >;
using PK7 = gpio_pin< PORTK, 7 >;

using PQ0 = gpio_pin< PORTQ, 0 >;
using PQ1 = gpio_pin< PORTQ, 1 >;
using PQ2 = gpio_pin< PORTQ, 2 >;
using PQ3 = gpio_pin< PORTQ, 3 >;

using PR0 = gpio_pin< PORTR, 0 >;
using PR1 = gpio_pin< PORTR, 1 >;

}   // namespace device

#endif  // SEAL_HAL_DEVICE_FILE_XMEGA128A1U
