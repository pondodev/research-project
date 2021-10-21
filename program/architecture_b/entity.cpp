#include "entity.h"

namespace arch_b {
    Entity::Entity() {
        id = next_id;
        next_id++;
    }

    Entity::~Entity() {
        for ( auto c : components ) {
            delete c;
        }
    }

    unsigned int Entity::get_id() {
        return id;
    }

    void Entity::add_component( Component* c ) {
        components.push_back( c );
    }

    void Entity::remove_component( unsigned int id ) {
        for ( size_t i = 0; i < components.size(); i++ ) {
            if ( components[ i ]->get_id() == id ) {
                delete components[ i ];
                components.erase( components.begin() + i );
                return;
            }
        }
    }
}
