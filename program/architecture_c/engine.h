#ifndef ARCH_C_ENGINE_H
#define ARCH_C_ENGINE_H

#define MAX_ENTITIES 500000

#include <queue>
#include <optional>
#include <cstring>

#include "types.h"
#include "component_container.h"
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

        void movement_system();
        void color_shift_system();

        MovableComponent* add_movable_component( Entity id );
        ColorComponent* add_color_component( Entity id );
        ColorVelocityComponent* add_color_velocity_component( Entity id );

        MovableComponent* get_movable_component( Entity id );
        ColorComponent* get_color_component( Entity id );
        ColorVelocityComponent* get_color_velocity_component( Entity id );

    private:
        std::queue<Entity> available_entities;
        std::vector<Entity> movement_system_entities;
        std::vector<Entity> color_shift_system_entities;

        ComponentFlag* entity_component_flags;
        ComponentContainer<MovableComponent, MAX_ENTITIES> movable_components;
        ComponentContainer<ColorComponent, MAX_ENTITIES> color_components;
        ComponentContainer<ColorVelocityComponent, MAX_ENTITIES> color_velocity_components;
    };
}

#endif
