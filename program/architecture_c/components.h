#ifndef ARCH_C_COMPONENT_H
#define ARCH_C_COMPONENT_H

namespace arch_c {
    struct PositionComponent {
        float x;
        float y;
    };

    struct VelocityComponent {
        float x;
        float y;
    };

    struct ColorComponent {
        float r;
        float g;
        float b;
    };

    struct ColorVelocityComponent {
        float r;
        float g;
        float b;
    };
}

#endif
