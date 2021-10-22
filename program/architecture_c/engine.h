#ifndef ARCH_C_ENGINE_H
#define ARCH_C_ENGINE_H

#define MAX_ENTITIES 500000

#include <queue>
#include <cstdint>
#include <optional>
#include <cstring>

#include "components.h"

namespace arch_c {
    typedef uint32_t Entity;
    typedef enum {
        Position      = 0x0001,
        Velocity      = 0x0010,
        Color         = 0x0100,
        ColorVelocity = 0x1000
    } ComponentFlag;

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
        bool entity_has_component( Entity id, ComponentFlag component );

        PositionComponent* add_position_component( Entity id );
        VelocityComponent* add_velocity_component( Entity id );
        ColorComponent* add_color_component( Entity id );
        ColorVelocityComponent* add_color_velocity_component( Entity id );

        PositionComponent* get_position_component( Entity id );
        VelocityComponent* get_velocity_component( Entity id );
        ColorComponent* get_color_component( Entity id );
        ColorVelocityComponent* get_color_velocity_component( Entity id );

    private:
        std::queue<Entity> available_entities;
        ComponentFlag* entity_component_flags;
        PositionComponent* position_components;
        VelocityComponent* velocity_components;
        ColorComponent* color_components;
        ColorVelocityComponent* color_velocity_components;
    };
}

#endif
