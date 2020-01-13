#pragma once

namespace peripheral {

    struct ThreeAxis {
        int16_t x;
        int16_t y;
        int16_t z;
    };

    namespace accel {

        enum class error { NO_ERROR, DATA_NOT_READY, FIFO_OVERFLOW, COMMUNICATION_ERROR };

        struct Acceleration : ThreeAxis {
            Acceleration() = default;
            explicit Acceleration(const int16_t x, const int16_t y, const int16_t z) : ThreeAxis{x,y,z} {}
        };

    }

    namespace rtc {
        enum class error { NO_ERROR, OSCILLATOR_ERROR, BAD_TIME_VALUE, COMMUNICATION_ERROR };
    }
}
