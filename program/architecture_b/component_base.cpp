#include "component_base.h"

namespace arch_b {
    Component::Component() {
        id = next_id;
        next_id++;
    }

    unsigned int Component::get_id() {
        return id;
    }
}
