#include "components.h"

namespace arch_b {
    PositionComponent::PositionComponent( glm::vec2 _value ) {
        value = _value;
    }

    void PositionComponent::apply_velocity( glm::vec2 vel ) {
        value += vel;

        // looping around edges of screen
        if ( value.x > 1.0f ) value.x -= 2.0f;
        if ( value.y > 1.0f ) value.y -= 2.0f;
        if ( value.x < -1.0f ) value.x += 2.0f;
        if ( value.y < -1.0f ) value.y += 2.0f;
    }

    VelocityComponent::VelocityComponent( glm::vec2 _value ) {
        value = _value;
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