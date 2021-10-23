#ifndef ARCH_B_COMPONENTS_H
#define ARCH_B_COMPONENTS_H

#include <glm/glm.hpp>

#include "component_base.h"
#include "../dan_math.h"

namespace arch_b {
    class MovementComponent : public Component {
    public:
        MovementComponent( glm::vec2 _pos, glm::vec2 _vel );
        void move();
        glm::vec2 pos;

    private:
        glm::vec2 vel;
    };

    class ColorComponent : public Component {
    public:
        ColorComponent( glm::vec3 _value );
        void apply_velocity( glm::vec3 vel );
        glm::vec3 value;
    };

    class ColorVelocityComponent : public Component {
    public:
        ColorVelocityComponent( glm::vec3 _value );
        glm::vec3 value;
    };
}

#endif
