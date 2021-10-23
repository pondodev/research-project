#ifndef ARCH_D_TYPES_H
#define ARCH_D_TYPES_H

#include <cstdint>

namespace arch_d {
    typedef uint32_t Entity;
    typedef enum {
        Movable      = 0x0010,
        Color         = 0x0100,
        ColorVelocity = 0x1000
    } ComponentFlag;
}

#endif
