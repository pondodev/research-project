#ifndef ARCH_B_ENGINE_H
#define ARCH_B_ENGINE_H

#include <vector>
#include <optional>

#include "entity.h"
#include "component_base.h"
#include "components.h"

namespace arch_b {
    class Engine {
    public:
        ~Engine();
        void add_entity( Entity* entity );
        void remove_entity( unsigned int id );
        std::optional<Entity*> get_entity( unsigned int id );
        std::vector<Entity*> get_all_entities();
        void update();

    private:
        std::vector<Entity*> entities;
    };
}

#endif
