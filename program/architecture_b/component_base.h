#ifndef ARCH_B_COMPONENT_BASE_H
#define ARCH_B_COMPONENT_BASE_H

namespace arch_b {
    class Component {
    public:
        Component();
        virtual unsigned int get_id(); // virtual so RTTI works

    private:
        static inline unsigned int next_id;
        unsigned int id;
    };
}

#endif
