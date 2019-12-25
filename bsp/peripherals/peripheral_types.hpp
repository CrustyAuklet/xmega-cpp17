#pragma once

namespace peripheral {

    struct ThreeAxis {
        int16_t x;
        int16_t y;
        int16_t z;
    };

    namespace accel {

        enum class error { DATA_NOT_READY, FIFO_OVERFLOW, COMMUNICATION_ERROR };

        struct Acceleration : ThreeAxis {
        };

    }
}