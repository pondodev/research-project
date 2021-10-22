#ifndef ARCH_C_ENGINE_H
#define ARCH_C_ENGINE_H

#define MAX_ENTITIES 500000

#include <queue>
#include <optional>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "types.h"
#include "components.h"
#include "../dan_math.h"

namespace arch_c {
    // source: https://stackoverflow.com/a/23152590
    template<class T> inline T operator~ (T a) { return (T)~(int)a; }
    template<class T> inline T operator| (T a, T b) { return (T)((int)a | (int)b); }
    template<class T> inline T operator& (T a, T b) { return (T)((int)a & (int)b); }
    template<class T> inline T operator^ (T a, T b) { return (T)((int)a ^ (int)b); }
    template<class T> inline T& operator|= (T& a, T b) { return (T&)((int&)a |= (int)b); }
    template<class T> inline T& operator&= (T& a, T b) { return (T&)((int&)a &= (int)b); }
    template<class T> inline T& operator^= (T& a, T b) { return (T&)((int&)a ^= (int)b); }

    class Engine {
    public:
        Engine();
        ~Engine();
        std::optional<Entity> add_entity();
        void remove_entity( Entity id );
        int entity_has_component( Entity id, ComponentFlag component );

        void dispatch_systems();
        bool are_thread_cycles_complete();

        MovableComponent* add_movable_component( Entity id );
        ColorComponent* add_color_component( Entity id );
        ColorVelocityComponent* add_color_velocity_component( Entity id );

        MovableComponent* get_movable_component( Entity id );
        ColorComponent* get_color_component( Entity id );
        ColorVelocityComponent* get_color_velocity_component( Entity id );

    private:
        bool running = true;
        bool movement_thread_cycle_complete = true;
        bool color_shift_thread_cycle_complete = true;
        std::thread movement_thread;
        std::thread color_shift_thread;
        std::mutex movement_thread_lock;
        std::mutex color_shift_thread_lock;
        std::unique_lock<std::mutex> system_thread_status_lock;
        std::condition_variable system_threads_complete;

        std::queue<Entity> available_entities;
        std::vector<Entity> movement_system_entities;
        std::vector<Entity> color_shift_system_entities;

        ComponentFlag* entity_component_flags;
        MovableComponent* movable_components;
        ColorComponent* color_components;
        ColorVelocityComponent* color_velocity_components;

        void movement_system();
        void color_shift_system();
    };
}

#endif
