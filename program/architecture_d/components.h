#ifndef ARCH_D_COMPONENT_H
#define ARCH_D_COMPONENT_H

namespace arch_d {
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
