#ifndef ARCH_C_COMPONENT_H
#define ARCH_C_COMPONENT_H

namespace arch_c {
    struct MovableComponent {
        float pos_x;
        float pos_y;
        float vel_x;
        float vel_y;
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
