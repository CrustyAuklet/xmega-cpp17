#pragma once

#include "drivers/uart.hpp"
#include "drivers/twi.hpp"
#include "drivers/pin_types.hpp"
#include "drivers/adc.hpp"

namespace board {

	inline constexpr uint32_t CrystalFreq = 32'768;			//< crystal frequency in Hz
    inline constexpr uint32_t CPUFreq = 2'000'000;          //< CPU frequency
    inline constexpr bool simulation  = SIMULATION_BUILD;   //< true if this is a simulation build

    inline constexpr drivers::Uart_Basic SerialC0(device::USARTC0, device::PC2, device::PC3);
	inline constexpr drivers::Uart_Basic EDBG_VCOM(device::USARTE0, device::PE2, device::PE3);
    inline constexpr drivers::TWI_Master_Basic I2C_C(device::TWIC, device::PC0, device::PC1);
    inline constexpr drivers::LedInverted UserLED(device::PQ3);

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

}   // namespace board
