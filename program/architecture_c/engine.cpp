#include "engine.h"
#include <iostream>

namespace arch_c {
    Engine::Engine() {
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
        for ( auto const& e : movement_system_entities ) {
            auto mov = get_movable_component( e );
            mov->pos_x += mov->vel_x;
            mov->pos_y += mov->vel_y;

            // looping positions
            if ( mov->pos_x > 1.0f ) mov->pos_x -= 2.0f;
            if ( mov->pos_y > 1.0f ) mov->pos_y -= 2.0f;
            if ( mov->pos_x < -1.0f ) mov->pos_x += 2.0f;
            if ( mov->pos_y < -1.0f ) mov->pos_y += 2.0f;
        }
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
