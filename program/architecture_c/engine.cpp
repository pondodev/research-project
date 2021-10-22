#include "engine.h"
#include <iostream>

namespace arch_c {
    Engine::Engine() {
        for ( Entity i = 0; i < MAX_ENTITIES; ++i ) {
            available_entities.push( i );
        }

        entity_component_flags = new ComponentFlag[ MAX_ENTITIES ];
        memset( entity_component_flags, 0x0000, MAX_ENTITIES ); // zero out flags
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
        // remove components from the component containers
        position_components.remove( id );
        velocity_components.remove( id );
        color_components.remove( id );

        if ( entity_has_component( id, ComponentFlag::ColorVelocity ) )
            color_velocity_components.remove( id );

        // reset entity values
        entity_component_flags[ id ] = (ComponentFlag)0x0000;
        available_entities.push( id );
    }

    int Engine::entity_has_component( Entity id, ComponentFlag component ) {
        return (int)(entity_component_flags[ id ] & component);
    }

    void Engine::movement_system() {
        for ( auto const& e : movement_system_entities ) {
            auto pos = get_position_component( e );
            auto const vel = get_velocity_component( e );
            pos->x += vel->x;
            pos->y += vel->y;

            // looping positions
            if ( pos->x > 1.0f ) pos->x -= 2.0f;
            if ( pos->y > 1.0f ) pos->y -= 2.0f;
            if ( pos->x < -1.0f ) pos->x += 2.0f;
            if ( pos->y < -1.0f ) pos->y += 2.0f;
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

    PositionComponent* Engine::add_position_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::Position;
        return position_components.add( id );
    }

    VelocityComponent* Engine::add_velocity_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::Velocity;
        movement_system_entities.push_back( id );
        return velocity_components.add( id );
    }

    ColorComponent* Engine::add_color_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::Color;
        return color_components.add( id );
    }

    ColorVelocityComponent* Engine::add_color_velocity_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::ColorVelocity;
        color_shift_system_entities.push_back( id );
        return color_velocity_components.add( id );
    }

    PositionComponent* Engine::get_position_component( Entity id ) {
        return position_components.get( id );
    }

    VelocityComponent* Engine::get_velocity_component( Entity id ) {
        return velocity_components.get( id );
    }

    ColorComponent* Engine::get_color_component( Entity id ) {
        return color_components.get( id );
    }

    ColorVelocityComponent* Engine::get_color_velocity_component( Entity id ) {
        return color_velocity_components.get( id );
    }
}
