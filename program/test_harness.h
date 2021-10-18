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
        current_cycle_count = 0;
        cycle_collection.clear();
    }

    static bool update() {
        current_cycle_count++;
        auto s = difftime( time( 0 ), start_time );
        if ( time_since_start != s ) {
            cycle_collection.push_back( current_cycle_count );
            current_cycle_count = 0;
            time_since_start = s;
        }

        return time_since_start >= TIME_LIMIT;
    }

    static float get_average() {
        float total_cycles = 0;
        for ( int x : cycle_collection ) {
            total_cycles += x;
        }

        return total_cycles / time_since_start;
    }

private:
    static inline time_t start_time;
    static inline int current_cycle_count;
    static inline int time_since_start;
    static inline std::vector<int> cycle_collection;
};

#endif
