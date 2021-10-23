#include "engine.h"
#include <iostream>

namespace arch_d {
    Engine::Engine()
    : movement_compute( "architecture_d/movement.comp", glm::vec2( MAX_COMPUTE_BATCH / 2, MAX_COMPUTE_BATCH / 2 ) ),
      color_shift_compute( "architecture_d/color_shift.comp", glm::vec2( MAX_COMPUTE_BATCH / 2, MAX_COMPUTE_BATCH / 2 ) ) {
        for ( Entity i = 0; i < MAX_ENTITIES; ++i ) {
            available_entities.push( i );
        }

        entity_component_flags = new ComponentFlag[ MAX_ENTITIES ];
        memset( entity_component_flags, 0x0000, MAX_ENTITIES ); // zero out flags
        movable_components = new MovableComponent[ MAX_ENTITIES ];
        color_components = new ColorComponent[ MAX_ENTITIES ];
        color_velocity_components = new ColorVelocityComponent[ MAX_ENTITIES ];
    }

    Engine::~Engine() {
        delete [] entity_component_flags;
    }

    std::optional<Entity> Engine::add_entity() {
        std::optional<Entity> to_return;

        if ( available_entities.size() > 0 ) {
            to_return = available_entities.front();
            available_entities.pop();
        }

        return to_return;
    }

    void Engine::remove_entity( Entity id ) {
        // reset entity values
        entity_component_flags[ id ] = (ComponentFlag)0x0000;
        available_entities.push( id );
    }

    int Engine::entity_has_component( Entity id, ComponentFlag component ) {
        return (int)(entity_component_flags[ id ] & component);
    }

    void Engine::movement_system() {
        // TODO: very not working
        std::vector<float> positions;
        std::vector<float> velocities;
        for ( auto const& e : movement_system_entities ) {
            auto mov = get_movable_component( e );
            positions.push_back( mov->pos_x );
            positions.push_back( mov->pos_y );
            // padding so it all fits in the rgba space of the texture
            positions.push_back( 0.0f );
            positions.push_back( 0.0f );

            velocities.push_back( mov->vel_x );
            velocities.push_back( mov->vel_y );
            // padding so it all fits in the rgba space of the texture
            velocities.push_back( 0.0f );
            velocities.push_back( 0.0f );
        }

        movement_compute.set_values( 1, positions.data() );
        movement_compute.set_values( 2, velocities.data() );
        movement_compute.wait();

        auto result = movement_compute.get_values();
    }

    void Engine::color_shift_system() {
        for ( auto const& e : color_shift_system_entities ) {
            auto col = get_color_component( e );
            auto const col_vel = get_color_velocity_component( e );
            col->r += col_vel->r;
            col->g += col_vel->g;
            col->b += col_vel->b;

            // looping colours
            col->r = frac( col->r );
            col->g = frac( col->g );
            col->b = frac( col->b );
        }
    }

    MovableComponent* Engine::add_movable_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::Movable;
        movement_system_entities.push_back( id );
        return &movable_components[ id ];
    }

    ColorComponent* Engine::add_color_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::Color;
        return &color_components[ id ];
    }

    ColorVelocityComponent* Engine::add_color_velocity_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::ColorVelocity;
        color_shift_system_entities.push_back( id );
        return &color_velocity_components[ id ];
    }

    MovableComponent* Engine::get_movable_component( Entity id ) {
        return &movable_components[ id ];
    }

    ColorComponent* Engine::get_color_component( Entity id ) {
        return &color_components[ id ];
    }

    ColorVelocityComponent* Engine::get_color_velocity_component( Entity id ) {
        return &color_velocity_components[ id ];
    }
}
