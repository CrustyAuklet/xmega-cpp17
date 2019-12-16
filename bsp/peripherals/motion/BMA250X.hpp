#pragma once

namespace peripheral {
    namespace accel {

        template<class I2C_Instance>
        class BMA250X {
            I2C_Instance m_i2c;
        public:
            // constructor
            constexpr BMA250X(const I2C_Instance i2c) noexcept : m_i2c(i2c) {}

            /// calls init on I2C instance. In the end the I2C and peripheral should be ready and in low power state
            constexpr void init() const noexcept {
                m_i2c.init();
            }

            /// ensures the I2C interface is active and enabled
            constexpr bool begin() const noexcept  {
                m_i2c.start();
                return present();
            }

            /// ensures the I2C interface and device are off and in low power state
            constexpr bool stop() const noexcept  {
                present();
                m_i2c.stop();
                return true;
            }

            /// checks to see if the Accelerometer is responding and available
            constexpr bool present() const noexcept {
                const uint8_t id = m_i2c.ReadReg8(BMA250X_I2C_ADDRESS, CHIP_ID);
                return id == BMA250E_ID_VALUE || id == BMA250_ID_VALUE;
            }

            /**
            * @brief Put the Accelerometer into lowest power mode available
            * @return true if successful, false otherwise
            */
            bool deepSleep() noexcept {
                //const uint8_t sleepCommand = (is250e ? ACC_MODE_DEEP_250E : ACC_MODE_DEEP_250);
                return m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, PMU_LPW, ACC_MODE_DEEP_250E);
            }

            /**
            * @brief start the FIFO in low power sampling mode
            * Sample rate should be as close to 10Hz as the harware allows
            *
            * @return true if successful, false otherwise
            */
            int8_t startFIFO() noexcept {
                const uint8_t ACC_PERIOD = ACC_PERIOD_1000MS;
                // ensure the chip is in full power mode and hardware version is known
                bool success = m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, PMU_LPW, ACC_PERIOD);
                //Sleep(2);
                m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, INTERFACE_CONFIG, ACC_WDT_50MS);

                if (success) {
                    // disable temperature sensor as per errata #2:
                    // Write the secret command twice to open expanded registers, disable temperature, close the secret door.
                    success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, ACC_SECRET_REG, ACC_SECRET_OPEN);
                    success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, ACC_SECRET_REG, ACC_SECRET_OPEN);
                    success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, ACC_TEMP_CONTROL, ACC_SECRET_2);
                    success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, ACC_SECRET_REG, ACC_SECRET_CLOSE);

                    // eratta sheet specifies that we should only write to FIFO settings in standby mode
                    success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, PMU_LOW_POWER, (ACC_LP_MODE2 | ACC_LP_EQUAL_TIME));
                    success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, PMU_LPW, (ACC_MODE_SUSPEND | ACC_PERIOD));

                    // set up the FIFO to be in STREAM mode. With extra secret bits to prevent eratta 5
                    success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, FIFO_CONFIG_1, (ACC_FIFO_STREAM | ACC_SECRET_5 | ACC_FIFO_XYZ));
                    success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, FIFO_CONFIG_1, (ACC_FIFO_STREAM | ACC_SECRET_5 | ACC_FIFO_XYZ));

                    // FIFO settigns errata, return to normal mode. We must tdo this to then go into LP mode
                    //success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, PMU_LPW, ACC_PERIOD);
                    //Sleep(2);

                    // First set the low power mode to mode 2 and time based sampling
                    //success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, PMU_LOW_POWER, (ACC_LP_MODE2 | ACC_LP_EQUAL_TIME));

                    // THEN set to low power mode, with 10Hz sample rate
                    success &= m_i2c.WriteReg8(BMA250X_I2C_ADDRESS, PMU_LPW, (ACC_MODE_LP | ACC_PERIOD));
                    //Sleep(2);
                }
                return success;
            }

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

        private:
            // tracks the state of the accelerometer
            enum ACCEL_STATE {
                ACC_DEEP_SLEEP,
                ACC_FULL_POWER,
                ACC_FIFO_STARTED
            };

            bool is250e;                ///< defines this device as a BMA250E if true, a BMA250 either
            C_ThreeAxis   m_lastSample; ///< the last sample read from the FIFO
            ACCEL_STATE   m_state;      ///< state of the accelerometer

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

            enum BMA_250X_ID_t {
                BMA250E_ID_VALUE = 0xF9, // ID value of BMA250E in reg 0x00
                BMA250_ID_VALUE = 0x03  // ID value of BMA250 in reg 0x00
            };

            enum BMA_250X_ADDRESS_t {
                BMA250X_I2C_ADDRESS = 0x18<<1, // default address, SDO pulled to GND
                BMA250X_I2C_ADDRESS_ALT = 0x19  // alternate address, SDO pulled to VCC
            };

            /*** Register addresses for the MBA250e accelerometer ***/
            enum BMA250_REG_t {
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
                ACC_BANDWDTH = 0x10,
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
                ACC_FIFO_CONFIG = 0x30, // the current FIFO watermark level
                ACC_SELF_TEST = 0x32, // self test settings and parameters
                ACC_NVM_CTRL = 0x33, // control settings for the NVM
                INTERFACE_CONFIG = 0x34, //
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

            enum BMA250_SECRET_t {
                ACC_SECRET_2 = 0x00, // write to address 0x4F to disable temp sensor
                ACC_SECRET_OPEN = 0xCA, // write to address 0x00 to open the secret memory map
                ACC_SECRET_CLOSE = 0x0A, // write to address 0x00 to close the secret memory map
            };

            enum BMA250_RANGE_t {
                ACC_RANGE_2G = 0x03, //  3.91 mg/LSB
                ACC_RANGE_4G = 0x05, //  7.81 mg/LSB
                ACC_RANGE_8G = 0x08, // 15.62 mg/LSB
                ACC_RANGE_16G = 0x0C  // 31.25 mg/LSB
            };

            enum BMA250_MODE_t {
                ACC_MODE_NORM = 0x00, // Put the chip into NORMAL mode
                ACC_MODE_DEEP_250E = 0x20, // Put the chip into DEEP_SUSPEND mode (250E)
                ACC_MODE_DEEP_250 = 0x80, // Put the chip into DEEP_SUSPEND mode (250)
                ACC_MODE_LP = 0x40, // Put the chip into LOW_POWER mode
                ACC_MODE_SUSPEND = 0x80, // Put the chip into SUSPEND mode
                ACC_PERIOD_HALFMS = 0x0A, //  1/2  millisecond sleep period
                ACC_PERIOD_1MS = 0x12, //  1    millisecond sleep period
                ACC_PERIOD_2MS = 0x0E, //  2    millisecond sleep period
                ACC_PERIOD_4MS = 0x10, //  4    millisecond sleep period
                ACC_PERIOD_6MS = 0x12, //  6    millisecond sleep period
                ACC_PERIOD_10MS = 0x14, //  10   millisecond sleep period
                ACC_PERIOD_25MS = 0x16, //  25   millisecond sleep period
                ACC_PERIOD_50MS = 0x18, //  50   millisecond sleep period
                ACC_PERIOD_100MS = 0x1A, //  100  millisecond sleep period
                ACC_PERIOD_500MS = 0x1C, //  500  millisecond sleep period
                ACC_PERIOD_1000MS = 0x1E  //  1000 millisecond sleep period
            };

            enum BMA250_LP_t {
                ACC_LP_MODE1 = 0x00, // Put the chip into LP mode 1
                ACC_LP_MODE2 = 0x40, // Put the chip into LP mode 2
                ACC_LP_EVENTS = 0x00, // use event driven mode in Low Power
                ACC_LP_EQUAL_TIME = 0x20, // Use equidistant sampling time mode in Low Power
            };

            enum BMA250_FIFO_MODE_t {
                ACC_FIFO_BYPASS = 0x00, // disable FIFO
                ACC_FIFO_STOP = 0x40, // FIFO stops wen buffer is full with 32 frames
                ACC_FIFO_STREAM = 0x80, // When full FIFO will discard the oldest frame
                ACC_FIFO_XYZ = 0x00, // sample all axes
                ACC_FIFO_X = 0x01, // Sample only X into the FIFO
                ACC_FIFO_Y = 0x02, // Sample only Y into the FIFO
                ACC_FIFO_Z = 0x03, // Sample only Z into the FIFO
                ACC_SECRET_5 = 0x0C  // fixes FIFO errata number 5 by writing 1s to reserved bits
            };

            enum BMA250_WDT_t {
                ACC_WDT_OFF = 0x00, // disable the watchdog timer
                ACC_WDT_1MS = 0x04, // 1ms watchdog timer
                ACC_WDT_50MS = 0x06, // 50ms watchdog timer
            };
        };

    } // namespace acceleration
} // namespace peripheral
