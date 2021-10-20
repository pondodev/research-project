#ifndef COLOR_SHIFT_ENTITY_H
#define COLOR_SHIFT_ENTITY_H

#include <glm/glm.hpp>

#include "entity.h"

namespace arch_a {
    class ColorShiftEntity : public Entity {
    public:
        ColorShiftEntity( unsigned int _id, glm::vec2 _position, glm::vec2 _velocity, glm::vec3 _color, glm::vec3 _color_velocity );
        void update() override;

    private:
        glm::vec3 color_velocity;
    };
}

#endif
