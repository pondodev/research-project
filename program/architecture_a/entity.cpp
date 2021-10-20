#include "entity.h"

namespace arch_a {
    Entity::Entity( unsigned int _id, glm::vec2 _position, glm::vec2 _velocity, glm::vec3 _color ) {
        id = _id;
        position = _position;
        velocity = _velocity;
        color = _color;
    }

    void Entity::update() {
        position += velocity;

        // loop around edges of screen
        // NOTE: we use ndc because i'm lazy lol
        if ( position.x > 1.0f ) position.x -= 2.0f;
        if ( position.y > 1.0f ) position.y -= 2.0f;
        if ( position.x < -1.0f ) position.x += 2.0f;
        if ( position.y < -1.0f ) position.y += 2.0f;
    }

    unsigned int Entity::get_id() {
        return id;
    }

    glm::vec2 Entity::get_position() {
        return position;
    }

    glm::vec3 Entity::get_color() {
        return color;
    }
}
