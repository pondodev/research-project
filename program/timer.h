#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
private:
    inline static unsigned int start_time;
    inline static unsigned int end_time;

    static unsigned int get_time_now() {
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        );

        return time.count();
    }

public:
    static void start() {
        start_time = get_time_now();
    }

    static void end() {
        end_time = get_time_now();
    }

    static float get_time_seconds() {
        return (end_time - start_time) / 1000.0f / 1000.0f;
    }

    static float get_time_milliseconds() {
        return (end_time - start_time) / 1000.0f;
    }

    static float get_time_microseconds() {
        return (float)(end_time - start_time);
    }
};

#endif