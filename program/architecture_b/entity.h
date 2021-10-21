#ifndef ARCH_B_ENTITY_H
#define ARCH_B_ENTITY_H

#include <vector>
#include <cstdlib>
#include <typeinfo>
#include <optional>

#include "component_base.h"

namespace arch_b {
    class Entity {
    public:
        Entity();
        ~Entity();
        unsigned int get_id();
        void add_component( Component* c );
        void remove_component( unsigned int id );
        template <typename T>
        std::optional<T*> get_component() {
            std::optional<T*> to_return;

            for ( auto c : components ) {
                if ( typeid(*c) == typeid(T) ) {
                    to_return = (T*)c;
                    break;
                }
            }

            return to_return;
        }

    private:
        static inline unsigned int next_id;
        unsigned int id;
        std::vector<Component*> components;
    };
}

#endif
