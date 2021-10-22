#ifndef ARCH_C_COMPONENT_CONTAINER
#define ARCH_C_COMPONENT_CONTAINER

#include <cstdlib>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#include "types.h"

namespace arch_c {
    template <typename T, size_t N>
    class ComponentContainer {
    public:
        ComponentContainer() {
            data = new T[ N ];
        }

        ~ComponentContainer() {
            delete [] data;
        }

        T* add( Entity id ) {
            auto i = count;
            entity_to_component.emplace( id, count );
            ++count;

            return &data[ i ];
        }

        T* get( Entity id ) {
            auto i = entity_to_component[ id ];
            return &data[ i ];
        }

        void remove( Entity id ) {
            --count;

            // replace removed data with other, still active data
            auto i = entity_to_component[ id ];
            if ( i != count ) data[ i ] = data[ count ];

            // remove entry from unordered map
            entity_to_component.erase( id );

            // remap entity's id to new component index
            for ( auto& it : entity_to_component ) {
                if ( it.second == count ) {
                    it.second = i;
                }
            }
        }

    private:
        T* data;
        // map of entity ids to component array indices
        std::unordered_map<Entity, size_t> entity_to_component;
        size_t count = 0;
    };
};

#endif
