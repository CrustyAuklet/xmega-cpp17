#pragma once

#include "drivers/uart.hpp"
#include "drivers/twi.hpp"
#include "drivers/spi.hpp"
#include "drivers/adc.hpp"

#include "pin_types.hpp"

//#include "../peripherals/motion/BMA250X.hpp"

#include <tuple>

namespace board {

	inline constexpr uint32_t CrystalFreq = 32'768;			//< crystal frequency in Hz
    inline constexpr uint32_t CPUFreq = 2'000'000;          //< CPU frequency
    inline constexpr bool simulation  = SIMULATION_BUILD;   //< true if this is a simulation build

    namespace UTH_Version0 {
        inline constexpr auto MonBattery    = device::PA0;
        inline constexpr auto TxPower       = device::PA1;
        inline constexpr auto INTSensor     = device::PA2;
        inline constexpr auto PLL_enable    = device::PA3;
        inline constexpr auto TX_Lock       = device::PA4;
        inline constexpr auto VPA           = device::PA5;
        inline constexpr auto WDin          = device::PA6;
        inline constexpr auto Reflect       = device::PA7;

        inline constexpr auto Ix            = device::PB0;
        inline constexpr auto VpllBB        = device::PB1;
        inline constexpr auto RTCINT        = device::PB2;
        inline constexpr auto Battery       = device::PB3;
        inline constexpr auto TxVco         = device::PB4;
        inline constexpr auto DegC          = device::PB5;
        inline constexpr auto Light         = device::PB6;
        inline constexpr auto Light_pwr     = device::PB7;

        inline constexpr auto SDA_external  = device::PC0;
        inline constexpr auto SCL_external  = device::PC1;
        inline constexpr GPIO::USART_RX     RXD(device::PC2);
        inline constexpr GPIO::USART_TX     TXD(device::PC3);
        inline constexpr auto MonVpllBB     = device::PC4;
        inline constexpr auto Personality   = device::PC5;
        inline constexpr auto PLLBBPs       = device::PC6;
        inline constexpr auto PLLBB_enable  = device::PC7;

        inline constexpr auto WD_pwr        = device::PD0;
        inline constexpr auto WD_pwr_resistor = device::PD1;
        inline constexpr auto BMA_int1      = device::PD2;
        inline constexpr auto FRAM_enable   = device::PD3;
        inline constexpr auto FRAM_cs       = device::PD4;
        inline constexpr auto FRAM_si       = device::PD5;
        inline constexpr auto FRAM_so       = device::PD6;
        inline constexpr auto FRAM_sck      = device::PD7;

        inline constexpr GPIO::SDA          SDA_isolated(device::PE0);
        inline constexpr GPIO::SCL          SCL_isolated(device::PE1);
        inline constexpr auto reset_switch  = device::PE2;
        inline constexpr auto reset_enable  = device::PE3;
        inline constexpr GPIO::Unused       NC_PE4(device::PE4);
        inline constexpr GPIO::Unused       NC_PE5(device::PE5);
        inline constexpr GPIO::Unused       NC_PE6(device::PE6);
        inline constexpr auto RTC_clk       = device::PE7;

        inline constexpr auto TEMP_read     = device::PF0;
        inline constexpr auto MonTxVco      = device::PF1;
        inline constexpr auto INT_ext       = device::PF2;
        inline constexpr GPIO::Unused       NC_PF3(device::PF3);
        inline constexpr auto REV_ID0       = device::PF4;
        inline constexpr auto REV_ID1       = device::PF5;
        inline constexpr auto REV_ID2       = device::PF6;
        inline constexpr auto REV_ID3       = device::PF7;

        inline constexpr GPIO::Unused       NC_PR0(device::PR0);
        inline constexpr GPIO::Led          LED(device::PR1);

        inline constexpr std::tuple all_pins {
            MonBattery, TxPower, INTSensor, PLL_enable, TX_Lock, VPA, WDin, Reflect,
            Ix, VpllBB, RTCINT, Battery, TxVco, DegC, Light, Light_pwr,
            SDA_external, SCL_external, RXD, TXD, MonVpllBB, Personality, PLLBBPs, PLLBB_enable,
            WD_pwr, WD_pwr_resistor, BMA_int1, FRAM_enable, FRAM_cs, FRAM_si, FRAM_so, FRAM_sck,
            SDA_isolated, SCL_isolated, reset_switch, reset_enable, NC_PE4, NC_PE5, NC_PE6, RTC_clk,
            TEMP_read, MonTxVco, INT_ext, NC_PF3, REV_ID0, REV_ID1, REV_ID2, REV_ID3,
            NC_PR0, LED
        };
    }

    // select the right version of the board
    namespace pins = UTH_Version0;

    // fundamental wiring of the board
    using pins::LED;
    inline constexpr drivers::Uart_Basic SerialPort(device::USARTC0, pins::RXD, pins::TXD);
	inline constexpr drivers::TWI_Master_Basic I2C_External(device::TWIC, pins::SDA_external, pins::SCL_external);
    inline constexpr drivers::TWI_Master_Basic I2C_Isolated(device::TWIE, pins::SDA_isolated, pins::SCL_isolated);
    inline constexpr drivers::SPI_Master_Basic FRAM(device::SPID, pins::FRAM_si, pins::FRAM_so, pins::FRAM_sck, pins::FRAM_cs);
    using pins::FRAM_enable;
    inline constexpr drivers::ADC_SingleEnded_Basic ADC(device::ADCA);

    /**
     * Initialize the board.
     * When this function returns the system clocks should be initialized,
     * and peripherals should have gone through initialization and left in a low power state.
     * @return True if the initialization succeeds, False if there is a failure.
     */
    bool init() noexcept;

    /// delay AT MOST us microseconds
    void delay_us(uint16_t us) noexcept;
    /// delay AT MOST ms milliseconds
    void delay_ms(uint16_t ms) noexcept;

    // inline variable constructor will run right before main
    class impl {
    public:
        impl() noexcept { init(); }
    };
    inline impl ImplInst;

}   // namespace board
