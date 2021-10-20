#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#define TIME_LIMIT 60

#include <vector>
#include <ctime>

class TestHarness {
public:
    static void init() {
        start_time = time( 0 );
        time_since_start = 0;
    }

    static void clear() {
        init();
        cycle_count = 0;
    }

    static bool update() {
        cycle_count++;
        time_since_start = difftime( time( 0 ), start_time );

        return time_since_start >= TIME_LIMIT;
    }

    static float get_average() {
        return cycle_count / time_since_start;
    }

private:
    static inline time_t start_time;
    static inline int cycle_count;
    static inline int time_since_start;
};

#endif
