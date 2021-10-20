#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "entity.h"
#include "color_shift_entity.h"

namespace arch_a {
    class Engine {
    public:
        ~Engine();
        unsigned int add_entity( glm::vec2 _position, glm::vec2 _velocity, glm::vec3 _color );
        unsigned int add_entity( glm::vec2 _position, glm::vec2 _velocity, glm::vec3 _color, glm::vec3 _color_velocity );
        void remove_entity( unsigned int id );
        std::vector<Entity*> get_entities();
        void update();

    private:
        unsigned int current_entity_id = 0;
        std::vector<Entity*> entities;
    };
}

#endif
