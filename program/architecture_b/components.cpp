#include "components.h"

namespace arch_b {
    MovementComponent::MovementComponent( glm::vec2 _pos, glm::vec2 _vel ) {
        pos = _pos;
        vel = _vel;
    }

    void MovementComponent::move() {
        pos += vel;

        // looping around edges of screen
        if ( pos.x > 1.0f ) pos.x -= 2.0f;
        if ( pos.y > 1.0f ) pos.y -= 2.0f;
        if ( pos.x < -1.0f ) pos.x += 2.0f;
        if ( pos.y < -1.0f ) pos.y += 2.0f;
    }

    ColorComponent::ColorComponent( glm::vec3 _value ) {
        value = _value;
    }

    void ColorComponent::apply_velocity( glm::vec3 vel ) {
        value += vel;

        // looping colours
        value.r = frac( value.r );
        value.g = frac( value.r );
        value.b = frac( value.r );
    }

    ColorVelocityComponent::ColorVelocityComponent( glm::vec3 _value ) {
        value = _value;
    }
}