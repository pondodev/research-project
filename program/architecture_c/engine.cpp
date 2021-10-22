#include "engine.h"
#include <iostream>

namespace arch_c {
    Engine::Engine() {
        for ( Entity i = 0; i < MAX_ENTITIES; i++ ) {
            available_entities.push( i );
        }

        entity_component_flags = new ComponentFlag[ MAX_ENTITIES ];
        memset( entity_component_flags, 0x0000, MAX_ENTITIES ); // zero out flags
        position_components = new PositionComponent[ MAX_ENTITIES ];
        velocity_components = new VelocityComponent[ MAX_ENTITIES ];
        color_components = new ColorComponent[ MAX_ENTITIES ];
        color_velocity_components = new ColorVelocityComponent[ MAX_ENTITIES ];
    }

    Engine::~Engine() {
        delete [] entity_component_flags;
        delete [] position_components;
        delete [] velocity_components;
        delete [] color_components;
        delete [] color_velocity_components;
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
        entity_component_flags[ id ] = (ComponentFlag)0x0000;
        available_entities.push( id );
    }

    bool Engine::entity_has_component( Entity id, ComponentFlag component ) {
        return entity_component_flags[ id ] & component > 0;
    }

    PositionComponent* Engine::add_position_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::Position;
        return &position_components[ id ];
    }

    VelocityComponent* Engine::add_velocity_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::Velocity;
        return &velocity_components[ id ];
    }

    ColorComponent* Engine::add_color_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::Color;
        return &color_components[ id ];
    }

    ColorVelocityComponent* Engine::add_color_velocity_component( Entity id ) {
        entity_component_flags[ id ] |= ComponentFlag::ColorVelocity;
        return &color_velocity_components[ id ];
    }

    PositionComponent* Engine::get_position_component( Entity id ) {
        return &position_components[ id ];
    }

    VelocityComponent* Engine::get_velocity_component( Entity id ) {
        return &velocity_components[ id ];
    }

    ColorComponent* Engine::get_color_component( Entity id ) {
        return &color_components[ id ];
    }

    ColorVelocityComponent* Engine::get_color_velocity_component( Entity id ) {
        return &color_velocity_components[ id ];
    }
}
