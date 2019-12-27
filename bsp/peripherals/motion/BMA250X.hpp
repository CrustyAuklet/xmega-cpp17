#pragma once

#include <cstdint>
#include <tuple>
#include <UTH/board.hpp>
#include "peripherals/peripheral_types.hpp"
#include "nonstd/expected.hpp"

#include "board.hpp"

#include <stdio.h>

namespace peripheral::accel {

    namespace BMA250X {
        enum class RANGE : uint8_t {
            R_2G  = 0x03u, //  3.91 mg/LSB
            R_4G  = 0x05u, //  7.81 mg/LSB
            R_8G  = 0x08u, // 15.62 mg/LSB
            R_16G = 0x0Cu  // 31.25 mg/LSB
        };

        enum class BANDWIDTH : uint8_t {
            BW_7p81   = 0x08u, //< 7.81 Hz
            BW_15p63  = 0x09u, //< 15.63 Hz
            BW_31p25  = 0x0Au, //< 31.25 Hz
            BW_62p5   = 0x0Bu, //< 62.5 Hz
            BW_125    = 0x0Cu, //< 125 Hz
            BW_250    = 0x0Du, //< 250 Hz
            BW_500    = 0x0Eu, //< 500 Hz
            BW_1000   = 0x0Fu  //< 1000 Hz
        };

        enum class MODE : uint8_t {
            NORMAL      = 0x00u, // Put the chip into NORMAL mode
            DEEP_250E   = 0x20u, // Put the chip into DEEP_SUSPEND mode (250E)
            DEEP_250    = 0x80u, // Put the chip into DEEP_SUSPEND mode (250)
            LOW_POWER   = 0x40u, // Put the chip into LOW_POWER mode
            SUSPEND     = 0x80u, // Put the chip into SUSPEND mode
        };

        enum class SLEEP_DURATION : uint8_t {
            D_p5_default = 0x00u, // 1/2 millisecond sleep period also, but the default state at reset
            D_p5    = 0x0Au,  //  1/2  millisecond sleep period
            D_1MS   = 0x12u,  //  1    millisecond sleep period
            D_2MS   = 0x0Eu,  //  2    millisecond sleep period
            D_4MS   = 0x10u,  //  4    millisecond sleep period
            D_6MS   = 0x12u,  //  6    millisecond sleep period
            D_10MS  = 0x14u,  //  10   millisecond sleep period
            D_25MS  = 0x16u,  //  25   millisecond sleep period
            D_50MS  = 0x18u,  //  50   millisecond sleep period
            D_100MS = 0x1Au,  //  100  millisecond sleep period
            D_500MS = 0x1Cu,  //  500  millisecond sleep period
            D_1000MS = 0x1Eu  //  1000 millisecond sleep period
        };

        enum class FIFO_MODE : uint8_t {
            BYPASS = 0x00u, // disable FIFO
            STOP   = 0x40u, // FIFO stops wen buffer is full with 32 frames
            STREAM = 0x80u, // When full FIFO will discard the oldest frame
        };

        enum FIFO_AXIS : uint8_t {
            XYZ = 0x00u, // sample all axes
            X   = 0x01u, // Sample only X into the FIFO
            Y   = 0x02u, // Sample only Y into the FIFO
            Z   = 0x03u, // Sample only Z into the FIFO
        };
    }

    template<class I2C_Instance>
    class BMA250X_simple {
        I2C_Instance m_i2c;
        //decltype(board::I2C_Isolated) m_i2c;
        bool m_is250e;
        [[gnu::progmem]] static constexpr char name_250[]  = "BMA250";
        [[gnu::progmem]] static constexpr char name_250e[] = "BMA250E";
    public:
        constexpr BMA250X_simple(const I2C_Instance i2c) noexcept : m_i2c(i2c) {}

        /// ensures the I2C interface is active and enabled
        bool start() noexcept  {
            if(!present()) {
                return false;
            }
            m_is250e = is_250e();
            return true;
        }

        /// ensures the I2C interface and device are off and in low power state
        bool stop() noexcept  {
            deepSleep();
            return true;
        }

        /// checks to see if the Accelerometer is responding and available
        constexpr bool present() const noexcept {
            const auto id = m_i2c.read_reg8(BMA250X_I2C_ADDRESS, REG::CHIP_ID );
            if(id) {
                return id.value() == BMA250E_ID_VALUE || id.value() == BMA250_ID_VALUE;
            }
            return false;
        }

        const char* name() const noexcept {
            return is_250e() ? name_250e : name_250;
        }

        /// returns true if the attached device is a 250E
        constexpr bool is_250e() const noexcept {
            const auto id = m_i2c.read_reg8(BMA250X_I2C_ADDRESS, REG::CHIP_ID );
            return static_cast<bool>(id) && id.value() == BMA250E_ID_VALUE;
        }

        /**
        * @brief Put the Accelerometer into lowest power mode available, for model BMA250E
        * @return true if successful, false otherwise
        */
        constexpr bool deepSleep() const noexcept {
            if(m_is250e) {
                return m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::PMU_LPW, BMA250X::MODE::DEEP_250E);
            }
            else {
                return m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::PMU_LPW, BMA250X::MODE::DEEP_250);
            }
        }

        /// Disabled the temperature sensor as per secret errata #2
        constexpr bool disable_temp() const noexcept {
            constexpr uint8_t ACC_SECRET_2     = 0x00u; // write to address 0x4F to disable temp sensor
            constexpr uint8_t ACC_SECRET_OPEN  = 0xCAu; // write to address 0x00 to open the secret memory map
            constexpr uint8_t ACC_SECRET_CLOSE = 0x0Au; // write to address 0x00 to close the secret memory map

            // Write the secret command twice to open expanded registers, disable temperature, close the secret door.
            bool success = m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::ACC_SECRET_REG, ACC_SECRET_OPEN);
            success &= m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::ACC_SECRET_REG, ACC_SECRET_OPEN).has_value();
            success &= m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::ACC_TEMP_CONTROL, ACC_SECRET_2).has_value();
            success &= m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::ACC_SECRET_REG, ACC_SECRET_CLOSE).has_value();
            return success;
        }

        constexpr std::pair<uint8_t, bool> FIFO_Status() const noexcept {
            const auto result = m_i2c.read_reg8(BMA250X_I2C_ADDRESS, REG::FIFO_STATUS);
            if(result) {
                return { result.value() & 0x7FU, result.value() & 0x80U };
            }
            return {0, false};
        }

        constexpr bool set_range(const BMA250X::RANGE r) const noexcept {
            return m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::G_RANGE, static_cast<uint8_t>(r)).has_value();
        }

        constexpr bool set_bandwidth(const BMA250X::BANDWIDTH b) const noexcept {
            return m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::BANDWDTH, static_cast<uint8_t>(b)).has_value();
        }

        constexpr bool set_mode(const BMA250X::MODE m, const BMA250X::SLEEP_DURATION d = BMA250X::SLEEP_DURATION::D_p5_default) const noexcept {
            return m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::PMU_LPW, (static_cast<uint8_t>(m) | static_cast<uint8_t>(d))).has_value();
        }

        /// selects filtered or unfiltered data for the acceleration data registers. Also sets shadowing mode so that reads are atomic.
        constexpr bool unfiltered_data(const bool unfiltered = true) const noexcept {
            constexpr uint8_t FilterShift = 7u;
            constexpr uint8_t shadowMode = 1U<<6U;
            return m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::DATA_CONFIG, (unfiltered << FilterShift) | shadowMode).has_value();
        }

        constexpr bool set_lowpower1() const noexcept {
            constexpr uint8_t reg_val = static_cast<uint8_t>(LP::MODE1) | static_cast<uint8_t>(LP::EQUAL_TIME);
            return m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::PMU_LOW_POWER, reg_val).has_value();
        }

        constexpr bool set_lowpower2() const noexcept {
            constexpr uint8_t reg_val = static_cast<uint8_t>(LP::MODE2) | static_cast<uint8_t>(LP::EQUAL_TIME);
            return m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::PMU_LOW_POWER, reg_val).has_value();
        }

        constexpr bool set_fifo_mode(const BMA250X::FIFO_MODE mode, const BMA250X::FIFO_AXIS axis) const noexcept {
            constexpr uint8_t ACC_SECRET_5 = 0x0C;  // fixes FIFO errata number 5 by writing 1s to reserved bits
            const uint8_t reg_val = static_cast<uint8_t>(mode) | static_cast<uint8_t>(axis) | ACC_SECRET_5;
            return m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::FIFO_CONFIG_1, reg_val).has_value();
        }

        /**
        * start the FIFO in low power sampling mode
        * @return true if successful, false otherwise
        */
        bool startFIFO(const BMA250X::SLEEP_DURATION interval) noexcept {
            // ensure the chip is in full power mode and hardware version is known
            bool success = set_mode(BMA250X::MODE::NORMAL, interval);
            //board::delay_ms(2);
            // enable I2C 50ms watchdog timer
            success &= m_i2c.write_reg8(BMA250X_I2C_ADDRESS, REG::INTERFACE_CONFIG, ACC_WDT_50MS).has_value();

            if (success) {
                // disable temperature sensor as per errata #2:
                success &= disable_temp();

                // eratta sheet specifies that we should only write to FIFO settings in standby mode
                success &= set_lowpower2();
                success &= set_mode(BMA250X::MODE::SUSPEND, interval);

                // set up the FIFO to be in STREAM mode. With extra secret bits to prevent eratta 5
                success &= set_fifo_mode(BMA250X::FIFO_MODE::STREAM, BMA250X::FIFO_AXIS::XYZ);
                //success &= start_fifo(BMA250X::FIFO_MODE::STREAM, BMA250X::FIFO_AXIS::XYZ);

                // FIFO settings errata, return to normal mode. We must do this to then go into LP mode
                success &= set_mode(BMA250X::MODE::NORMAL, interval);
                //board::delay_ms(2);

                // First set the low power mode to mode 2 and time based sampling
                success &= set_lowpower2();

                // THEN set to low power mode with specified interval
                success &= set_mode(BMA250X::MODE::LOW_POWER, interval);
                //board::delay_ms(2);
            }
            return success;
        }

        [[nodiscard]] nonstd::expected<Acceleration, accel::error>
        read() const noexcept {
            constexpr uint16_t NewDataFlag = 0x0001u;
            constexpr uint16_t DataShift = 6u;

            // write the register we want to read with no stop condition
            auto r = m_i2c.write(BMA250X_I2C_ADDRESS, {REG::XAXIS_LSB}, false);
            if(!r) { return nonstd::make_unexpected( error::COMMUNICATION_ERROR ); }
            // read all three acceleration registers in a row
            std::array<int16_t, 3> buf;
            r = m_i2c.read(BMA250X_I2C_ADDRESS, nonstd::span<uint8_t>{reinterpret_cast<uint8_t*>(buf.begin()), 6} );
            if(!r) { return nonstd::make_unexpected( error::COMMUNICATION_ERROR ); }
            if( (buf[0]&NewDataFlag) && (buf[1]&NewDataFlag) && (buf[2]&NewDataFlag) ) {
                return Acceleration{ static_cast<int16_t>(buf[0]>>DataShift), static_cast<int16_t>(buf[1]>>DataShift), static_cast<int16_t>(buf[2]>>DataShift) };
            }
            return nonstd::make_unexpected( error::DATA_NOT_READY );
        }

#if 0   // not implemented - ported
        /**
        * @brief get a single acceleration sample
        *
        * @param a pointer to a single Accelerometer sample
        * @return true if successful, false otherwise
        */
        int8_t read(C_ThreeAxis& a) noexcept {
            bool success = false;
            if (ACC_FIFO_STARTED == m_state) {
                a = m_lastSample;
                success = true;
            }
            else {

                success = m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, PMU_LPW, 0x00);

                if (success) {
                    Sleep(2);
                    success = m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, INTERFACE_CONFIG, ACC_WDT_50MS);
                }

                if (success) {
                    //            uint8_t haveReadSincePowerOn = 0;   // tracks if we have tried to read yet
                    for (uint16_t count = 10; count; --count) {
                        if (!i2cShim::readContinous(BMA250X_I2C_ADDRESS, XAXIS_LSB, (uint8_t*)& a, sizeof(C_ThreeAxis))) {
                            break;
                        }

                        // Check each channel for valid data.  Done when all three have data
                        if (newData(a)) {
                            // if( !haveReadSincePowerOn ) {
                            //     haveReadSincePowerOn = 1;
                            //     if(!is250e) { delay_us(500); }  // update period of .5ms at default bandwidth on BMA250, no need to waste time polling
                            //     continue;
                            // }

                            // transform the data to the minipat reference frame
                            transform(a);
                            break;
                        }
                    }
                    deepSleep();    // turn chip fully off
                }
            }
            return success;
        }

#define	bit_test( val, bitno )		(((val) & ((uint32_t)1 << (bitno))) ? 1 : 0)
#define bit_set( val, bitno )		((val) |= ((uint32_t)1<<(bitno)) )
#define bit_clear( val, bitno )		((val) &= ~((uint32_t)1<<(bitno)) )
#define max(a,b)					(((a) > (b)) ? (a) : (b))
#define min(a,b)					(((a) < (b)) ? (a) : (b))
#define ACCEL_BIT_WIDTH         (10)
#define ACCEL_RAW_MIDPOINT      (1<<(ACCEL_BIT_WIDTH-1))

        // Scale the two's-complement (10 bit) result to a positive 10 bit value
        // scaled from 0 -> 1023 Resulting gain is 2/512, offset 2
        uint16_t scale(uint16_t value) noexcept {
            if (bit_test(value, 9)) {
                value = ACCEL_RAW_MIDPOINT - ((~value + 1) & 0x1FF);
            }
            else {
                bit_set(value, 9);
            }

            return value;
        }

        void BMA250X::transform(C_ThreeAxis& a) noexcept {
            int16_t rawZ = (a.x >> BMA250_VALUE_SHIFT);

            a.x = scale(a.z >> BMA250_VALUE_SHIFT);
            a.y = scale(a.y >> BMA250_VALUE_SHIFT);

            if (bit_test(rawZ, 9)) { rawZ |= 0xFC00; }
            a.z = scale(-rawZ);
        }

        bool BMA250X::newData(C_ThreeAxis& a) noexcept {
            return (a.x & BMA250_NEWDATA) && (a.y & BMA250_NEWDATA) && (a.z & BMA250_NEWDATA);
        }

        /**
        * @brief Reads data from the FIFO, up to the size of the buffer passed in.
        * There may be more data available so this function can be called until it
        * returns 0, indicating there are no samples available.
        * @note calling this function without first calling startfifo() will produce
        * undefined behaviour (most likely all 0x00 values).
        *
        * @param[OUT] accBuf buffer to hold new acceleration samples
        * @param[IN] LEN length of accBuf
        * @return int8_t the number of samples read into accBuf, otherwise an error code
        */
        int8_t readFIFO(C_ThreeAxis accBuf[], const uint8_t LEN) noexcept {
            uint8_t i;                                // the return value and loop control variable

            //ASSERT(hasFIFO());
            uint8_t count = i2cShim::readReg8(BMA250X_I2C_ADDRESS, FIFO_STATUS);
            BMA250X_DEBUG("readFIFO(): FIFO_STATUS   = %02X\n", count);
            count = min((count & 0x7F), LEN);

            // read out the fifo into the provided buffer
            i2cShim::readContinous(BMA250X_I2C_ADDRESS, FIFO_DATA, (uint8_t*)accBuf, sizeof(C_ThreeAxis) * count);

            // proccess each frame read out in place
            for (i = 0; i < count; ++i) {
                // bail if the next sample is not new data.
                if (!newData(accBuf[i])) {
                    count = 0;
                    break;
                }

                // transform the data to the minipat reference frame
                transform(accBuf[i]);
            }

            m_lastSample = accBuf[count - 1];
            return i;
        }
#endif // not implemented - ported
    protected:
        /***************** REGISTER ENUM DEFINITIONS ************************************/

        /* the format of a single axis reading from the Accelerometer. */
        typedef union {
            struct {
                uint16_t newDataFlag : 1;   // bit to indicate this reading is new data
                uint16_t padBits : 5;   // unused/reserved padding
                uint16_t value : 10;  // signed value in 2's complement
            };
            uint16_t all;
        } accelAxis;

        /* the format of a single frame from the Accelerometer FIFO. */
        struct accelFrame {
            accelAxis x;    // The x-axis on the chip
            accelAxis y;    // The y-axis on the chip
            accelAxis z;    // The z-axis on the chip
        };

        static constexpr uint8_t BMA250X_I2C_ADDRESS     = 0x18u<<1u;   // default address, SDO pulled to GND
        static constexpr uint8_t BMA250X_I2C_ADDRESS_ALT = 0x19u<<1u;  // alternate address, SDO pulled to VCC

        static constexpr uint8_t BMA250E_ID_VALUE = 0xF9u;  // ID value of BMA250E in reg 0x00
        static constexpr uint8_t BMA250_ID_VALUE  = 0x03u;  // ID value of BMA250 in reg 0x00

        /*** Register addresses for the MBA250e accelerometer ***/
        enum REG : uint8_t {
            CHIP_ID = 0x00,
            XAXIS_LSB = 0x02,
            YAXIS_LSB = 0x04,
            ZAXIS_LSB = 0x06,
            ACC_TEMP = 0x08,
            INT_STATUS_0 = 0x09,
            INT_STATUS_1 = 0x0A,
            INT_STATUS_2 = 0x0B,
            INT_STATUS_3 = 0x0C,
            FIFO_STATUS = 0x0E,
            G_RANGE = 0x0F,
            BANDWDTH = 0x10,
            PMU_LPW = 0x11,
            PMU_LOW_POWER = 0x12,
            DATA_CONFIG = 0x13,
            SOFT_RESET = 0x14,
            INT_SETTING0 = 0x16,
            INT_SETTING1 = 0x17,
            INT_SETTING2 = 0x18,
            INT_MAP0 = 0x19,
            INT_MAP1 = 0x1A,
            INT_MAP2 = 0x1B,
            INT_DATASOURCE = 0x1E,
            INT_ELEC = 0x20,
            INT_MODE = 0x21,
            ACC_INT_0 = 0x22, // Time definition for the low-g interrupt
            ACC_INT_1 = 0x23, // Threshold definition for the low-g interrupt
            ACC_INT_2 = 0x24,
            ACC_INT_3 = 0x25, // Time definition for the high-g interrupt
            ACC_INT_4 = 0x26, // Threshold definition for the high-g interrupt
            SLOPE_SAMPLES = 0x27, // number of samples to evaluate for a slope interrupt
            SLOPE_THRESHOLD = 0x28, // threshold definition for any-motion interrupt
            ACC_INT_7 = 0x29, // threshold definition for slow/no-motion interrupt
            ACC_INT_8 = 0x2A, // Timing value for single and double tap interrupts
            ACC_INT_9 = 0x2B, // number of samples processed after tap interrupt and tap threshold
            ACC_INT_A = 0x2C, //
            ACC_INT_B = 0x2D, //
            ACC_INT_C = 0x2D, // threshold interrupt for flat angle
            ACC_INT_D = 0x2F, // flat interrupt hold time and hysteresis
            FIFO_CONFIG_0 = 0x30, // the FIFO watermark level setting
            ACC_SELF_TEST = 0x32, // self test settings and parameters
            ACC_NVM_CTRL = 0x33, // control settings for the NVM
            INTERFACE_CONFIG = 0x34, // configure the interface type (I2C vs SPI) and watchdog timer
            ACC_SECRET_REG = 0x35,  // secret register to extend memory map
            ACC_OFC_CTRL = 0x36,
            ACC_OFC_SETTING = 0x37,
            ACC_OFC_OFFSET_X = 0x38,
            ACC_OFC_OFFSET_Y = 0x39,
            ACC_OFC_OFFSET_Z = 0x3A,
            ACC_NVM_0 = 0x3B, // general purpose NVM memory #1
            ACC_NVM_1 = 0x3C, // general purpose NVM memory #1
            FIFO_CONFIG_1 = 0x3E, // FIFO mode and data selection
            FIFO_DATA = 0x3F, // FIFO data output register
            ACC_TEMP_CONTROL = 0x4F  // secret register to control the temperature sensor
        };

        enum BMA250_DATA_t {
            BMA250_NEWDATA = 0x0001,
            BMA250_VALUE_MASK = 0xFFC0,
            BMA250_VALUE_SHIFT = 6
        };

        enum class LP : uint8_t {
            MODE1 = 0x00, // Put the chip into LP mode 1
            MODE2 = 0x40, // Put the chip into LP mode 2
            EVENTS = 0x00, // use event driven mode in Low Power
            EQUAL_TIME = 0x20, // Use equidistant sampling time mode in Low Power
        };

        enum BMA250_WDT_t {
            ACC_WDT_OFF = 0x00, // disable the watchdog timer
            ACC_WDT_1MS = 0x04, // 1ms watchdog timer
            ACC_WDT_50MS = 0x06, // 50ms watchdog timer
        };
    };

} // namespace peripheral
