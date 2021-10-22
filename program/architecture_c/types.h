#ifndef ARCH_C_TYPES_H
#define ARCH_C_TYPES_H

#include <cstdint>

namespace arch_c {
    typedef uint32_t Entity;
    typedef enum {
        Position      = 0x0001,
        Velocity      = 0x0010,
        Color         = 0x0100,
        ColorVelocity = 0x1000
    } ComponentFlag;
}

#endif
