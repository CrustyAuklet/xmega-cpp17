
//#include <chrono>
#include <cstdint>

#include "board.hpp"

namespace peripheral::rtc {
    namespace PCF85063A {

        enum class HOUR_MODE : uint8_t { HOUR_24 = 0x00, HOUR_12 = 0x02 };
        enum class CAPACITOR_SELECT : uint8_t { pF_7 = 0x00, pF_12p5 = 0x01 };

        enum class OUTPUT_CLK : uint8_t {
            f_32768 = 0x00,
            f_16384 = 0x01,
            f_8192  = 0x02,
            f_4096  = 0x03,
            f_2048  = 0x04,
            f_1024  = 0x05,
            f_1     = 0x06,
            f_OFF   = 0x07
        };

        struct rtc_time_t {
            uint8_t second;
            uint8_t minute;
            uint8_t hour;
            uint8_t day;
            uint8_t weekday;
            uint8_t month;
            uint8_t year;
        };

        static constexpr bool validate_time_t(const rtc_time_t t) {
            return t.second < 60 && t.minute < 60 && t.hour < 24 && t.day < 31 && t.weekday < 7 &&
                   t.month < 13 && t.month > 0 && t.year < 100;
        }

    }   // namespace PCF85063A

    template<class I2C_Instance>
    class PCF85063A_simple {
        I2C_Instance m_i2c;
        //decltype(board::I2C_Isolated) m_i2c;
        [[gnu::progmem]] static constexpr char mName[] = "PCF85063A";
    public:
        explicit constexpr PCF85063A_simple(const I2C_Instance i2c) noexcept : m_i2c(i2c) {}

        /// ensures the I2C interface is active and enabled
        bool start() const noexcept {
            const auto control_reg = m_i2c.read_reg8(I2C_ADDRESS, REG::CONTROL_1);
            if(control_reg.has_value()) {
                m_i2c.write_reg8(I2C_ADDRESS, REG::CONTROL_1, control_reg.value() & ~CONTROL_1_MASK::STOP);
                return true;
            }
            return false;
        }

        /// ensures the I2C interface and device are off and in low power state
        bool stop() const noexcept {
            const auto control_reg = m_i2c.read_reg8(I2C_ADDRESS, REG::CONTROL_1);
            if(control_reg.has_value()) {
                control_reg.value() |= CONTROL_1_MASK::STOP;
                return m_i2c.write_reg8(I2C_ADDRESS, REG::CONTROL_1, control_reg.value()).value_or(false);
            }
            return false;
        }

        /// checks to see if the Accelerometer is responding and available
        constexpr bool present() const noexcept {
            return true;
        }

        const char* name() const noexcept {
            return mName;
        }

        bool set_output_clk(const PCF85063A::OUTPUT_CLK freq) const noexcept {
            const auto control_reg = m_i2c.read_reg8(I2C_ADDRESS, REG::CONTROL_2);
            if(control_reg.has_value()) {
                uint8_t send_val = control_reg.value() & ~CONTROL_2_MASK::COF_DISABLED;
                send_val |= static_cast<uint8_t>(freq);
                return m_i2c.write_reg8(I2C_ADDRESS, REG::CONTROL_1, send_val).value_or(false);
            }
            return false;
        }

        [[nodiscard]] nonstd::expected<PCF85063A::rtc_time_t, rtc::error>
        read_time() const noexcept {
            std::array<uint8_t, 7> buf{};
            // write the register we want to read with no stop condition
            auto r = m_i2c.write(I2C_ADDRESS, { REG::SECONDS }, false);
            if(!r) { return nonstd::make_unexpected( error::COMMUNICATION_ERROR ); }
            // read into the provided buffer
            r = m_i2c.read( I2C_ADDRESS, buf );
            if(!r) { return nonstd::make_unexpected( error::COMMUNICATION_ERROR ); }

            return PCF85063A::rtc_time_t{
                bcd2bin(buf[0]),
                bcd2bin(buf[1]),
                bcd2bin(buf[2]),
                bcd2bin(buf[3]),
                bcd2bin(buf[4]),
                bcd2bin(buf[5]),
                bcd2bin(buf[6]),
            };
        }

        rtc::error set_time(const PCF85063A::rtc_time_t time) const noexcept {
            if(!PCF85063A::validate_time_t(time)) {
                return rtc::error::BAD_TIME_VALUE;
            }

            std::array<uint8_t, 7> buf{
                bcd2bin(time.second),
                bcd2bin(time.minute),
                bcd2bin(time.hour),
                bcd2bin(time.day),
                bcd2bin(time.weekday),
                bcd2bin(time.month),
                bcd2bin(time.year)
            };

            return m_i2c.write(I2C_ADDRESS, buf).value_or(0) == buf.size() ? rtc::error::NO_ERROR : rtc::error::COMMUNICATION_ERROR;
        }

    private:
        static constexpr uint8_t bcd2bin(const uint8_t v) noexcept {
            return ( v >> 4U ) * 10 + (v & 0x0FU);
        }

        static constexpr uint8_t bin2bcd(const uint8_t v) noexcept {
            return ((v / 10) << 4U) | (v % 10);
        }

        /***************** REGISTER ENUM DEFINITIONS ************************************/
        static constexpr uint8_t I2C_ADDRESS     = 0x51u<<1u;   // I2C address

        enum REG : uint8_t {
            CONTROL_1       = 0x00, // Control/Status 1 register
            CONTROL_2       = 0x01, // Control/Status 2 register
            OFFSET          = 0x02,
            RAM_BYTE        = 0x03,
            SECONDS         = 0x04, // Seconds register
            MINUTES         = 0x05, // Minutes register
            HOURS           = 0x06, // Hours register
            DAYS            = 0x07, // Days register
            WEEKDAYS        = 0x08, // WeekDays register
            MONTHS          = 0x09, // Months regiser
            YEARS           = 0x0A, // Years register
            SECOND_alarm    = 0x0B, // Second alarm register
            MINUTE_alarm    = 0x0C, // Minute alarm register
            HOUR_alarm      = 0x0D, // Hour alarm register
            DAY_alarm       = 0x0E, // Day alarm register
            WEEKDAY_alarm   = 0x0F, // weekday alarm register
            TIMER_value     = 0x10, // Timer countdown value register
            TIMER_mode      = 0x11  // Countdown timer control register
        };

        enum CONTROL_1_MASK : uint8_t {
            EXT_TEST        = 0x80,
            STOP        = 0x20,
            SR          = 0x10,
            CIE         = 0x04,
            v12_24      = 0x02,
            CAP_SEL     = 0x01
        };

        enum CONTROL_2_MASK : uint8_t {
            AIE     = 0x80,
            AF      = 0x40,
            MI      = 0x20,
            HMI     = 0x10,
            TF      = 0x08,
            COF     = 0x07
        };

        enum SECONDS_MASK : uint8_t { OS_bm=0x80 };
        enum TIMER_MODE_MASK : uint8_t { TE_bm=0x04, TIE_bm=0x2, TI_TP_bm=0x01, TCF_bm=0x18, TCF4096_bm=0, TCF64_bm=0x08, TCF1_bm=0x10, TCF60_bm=0x18 };
        enum ALARM_MASK : uint8_t { AEN_S_bm=0x80, AEN_M_bm=0x80, AEN_H_bm=0x80, AEN_D_bm=0x80, AEN_W_bm=0x80 };
        enum OFFSET_MASK : uint8_t { MODE_bm=0x80, OFFSET_bm=0x7F };

    };

}   // namespace peripheral::rtc
