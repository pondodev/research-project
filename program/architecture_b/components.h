#ifndef ARCH_B_COMPONENTS_H
#define ARCH_B_COMPONENTS_H

#include <glm/glm.hpp>

#include "component_base.h"
#include "../dan_math.h"

namespace arch_b {
    class PositionComponent : public Component {
    public:
        PositionComponent( glm::vec2 _value );
        void apply_velocity( glm::vec2 vel );
        glm::vec2 value;
    };

    class VelocityComponent : public Component {
    public:
        VelocityComponent( glm::vec2 _value );
        glm::vec2 value;
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
