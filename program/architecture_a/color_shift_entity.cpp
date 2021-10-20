#include "color_shift_entity.h"

namespace arch_a {
    ColorShiftEntity::ColorShiftEntity( unsigned int _id, glm::vec2 _position, glm::vec2 _velocity, glm::vec3 _color, glm::vec3 _color_velocity )
    : Entity( _id, _position, _velocity, _color ) {
        color_velocity = _color_velocity;
    }

    void ColorShiftEntity::update() {
        Entity::update();
        color += color_velocity;

        // loop color values
        if ( color.r > 1.0f ) color.r -= 1.0f;
        if ( color.g > 1.0f ) color.g -= 1.0f;
        if ( color.b > 1.0f ) color.b -= 1.0f;
        if ( color.r < 1.0f ) color.r += 1.0f;
        if ( color.g < 1.0f ) color.g += 1.0f;
        if ( color.b < 1.0f ) color.b += 1.0f;
    }
}
