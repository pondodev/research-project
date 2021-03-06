#ifndef ARCH_D_ENGINE_H
#define ARCH_D_ENGINE_H

#define MAX_ENTITIES 500000
#define MAX_COMPUTE_BATCH 60000

#include <queue>
#include <optional>
#include <cstring>
#include <glm/glm.hpp>

#include "types.h"
#include "components.h"
#include "../dan_math.h"
#include "compute.h"

namespace arch_d {
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
        Compute movement_compute;
        Compute color_shift_compute;

        std::queue<Entity> available_entities;
        std::vector<Entity> movement_system_entities;
        std::vector<Entity> color_shift_system_entities;

        ComponentFlag* entity_component_flags;
        MovableComponent* movable_components;
        ColorComponent* color_components;
        ColorVelocityComponent* color_velocity_components;
    };
}

#endif
