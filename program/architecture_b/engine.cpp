#include "engine.h"

namespace arch_b {
    Engine::~Engine() {
        for ( auto e : entities ) {
            delete e;
        }
    }

    void Engine::add_entity( Entity* entity ) {
        entities.push_back( entity );
    }

    void Engine::remove_entity( unsigned int id ) {
        for ( size_t i = 0; i < entities.size(); i++ ) {
            if ( entities[ i ]->get_id() == id ) {
                entities.erase( entities.begin() + i );
                return;
            }
        }
    }

    void Engine::pop_entity() {
        delete entities.back();
        entities.pop_back();
    }

    std::optional<Entity*> Engine::get_entity( unsigned int id ) {
        std::optional<Entity*> to_return;

        for ( auto e : entities ) {
            if ( e->get_id() == id ) {
                to_return = e;
                break;
            }
        }

        return to_return;
    }

    std::vector<Entity*> Engine::get_all_entities() {
        return entities;
    }

    void Engine::update() {
        for ( auto e : entities ) {
            auto mov = e->get_component<MovementComponent>();
            auto col = e->get_component<ColorComponent>();
            auto col_vel = e->get_component<ColorVelocityComponent>();

            if ( mov.has_value() ) mov.value()->move();

            if ( col.has_value() && col_vel.has_value() ) {
                col.value()->apply_velocity( col_vel.value()->value );
            }
        }
    }
}
