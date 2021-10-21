#include "engine.h"

namespace arch_a {
    Engine::~Engine() {
        for ( auto e : entities ) {
            delete e;
        }
    }

    unsigned int Engine::add_entity( glm::vec2 _position, glm::vec2 _velocity, glm::vec3 _color ) {
        auto new_entity_id =  current_entity_id;
        entities.push_back( new Entity(new_entity_id, _position, _velocity, _color) );
        current_entity_id++;

        return new_entity_id;
    }

    unsigned int Engine::add_entity( glm::vec2 _position, glm::vec2 _velocity, glm::vec3 _color, glm::vec3 _color_velocity ) {
        auto new_entity_id =  current_entity_id;
        entities.push_back( new ColorShiftEntity(new_entity_id, _position, _velocity, _color, _color_velocity) );
        current_entity_id++;

        return new_entity_id;
    }

    void Engine::remove_entity( unsigned int id ) {
        for ( int i = 0; i < entities.size(); i++ ) {
            if ( entities[ i ]->get_id() == id ) {
                delete entities[ i ];
                entities.erase( entities.begin() + i );
                return;
            }
        }
    }

    void Engine::pop_entity() {
        delete entities.back();
        entities.pop_back();
    }

    std::vector<Entity*> Engine::get_entities() {
        return entities;
    }

    void Engine::update() {
        for ( auto e : entities ) {
            e->update();
        }
    }
}
