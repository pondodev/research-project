#ifndef ARCH_C_TYPES_H
#define ARCH_C_TYPES_H

#include <cstdint>

namespace arch_c {
    typedef uint32_t Entity;
    typedef enum {
        Movable       = 0b100,
        Color         = 0b010,
        ColorVelocity = 0b001
    } ComponentFlag;
}

#endif
