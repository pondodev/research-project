#ifndef ARCH_A_ENTITY_H
#define ARCH_A_ENTITY_H

#include <glm/glm.hpp>

namespace arch_a {
    class Entity {
    public:
        Entity( unsigned int _id, glm::vec2 _position, glm::vec2 _velocity, glm::vec3 _color );
        virtual void update();
        unsigned int get_id();
        glm::vec2 get_position();
        glm::vec3 get_color();

    protected:
        glm::vec3 color;

    private:
        unsigned int id;
        glm::vec2 position;
        glm::vec2 velocity;
    };
}

#endif
