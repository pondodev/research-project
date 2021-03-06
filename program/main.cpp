#include "main.h"

int main() {
    test_a_static();
    test_a_ramp_up();
    test_a_dynamic_ramp_up();

    test_b_static();
    test_b_ramp_up();
    test_b_dynamic_ramp_up();

    test_c_static();
    test_c_ramp_up();
    test_c_dynamic_ramp_up();

    //test_d_static();
    //test_d_ramp_up();
    //test_d_dynamic_ramp_up();

    std::cout << "done!" << std::endl;

    return 0;
}

void init_glfw_settings() {
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    #if SINGLE_BUFFERING_ACTIVE
    glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_FALSE );
    #endif
}

// callback function to handle when the window resizes
void framebuffer_size_callback( GLFWwindow* window, int width, int height ) {
    glViewport( 0, 0, width, height );
}

// handle all input here
void process_input( GLFWwindow* window ) {
    // close window on pressing esc
    if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) {
        glfwSetWindowShouldClose( window, true );
    }
}

void test_a_static() {
    std::cout << "running test a static..." << std::endl;

    init_glfw_settings();

    // create window object
    GLFWwindow* window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "test a static",
        NULL,
        NULL );

    // ensure creation was successful 
    if ( window == NULL ) {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();

        return;
    }

    // set context
    glfwMakeContextCurrent( window );

    // load glad before we make any opengl calls
    if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
        std::cerr << "failed to initialise glad" << std::endl;

        return;
    }

    // set gl viewport size, and set glfw callback for window resize
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    #if DEBUG_ACTIVE
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( gl_message_callback, 0 );
    #endif

    Shader visual_shader( "shader.vert", "shader.frag" );
    BatchRenderer renderer;

    // engine init
    arch_a::Engine engine;

    for ( int i = 0; i < STATIC_TEST_ENTITY_COUNT; i++ ) {
        int color_shift_flag = rand() % 2;
        glm::vec2 pos = { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ) };
        glm::vec2 vel = { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
        glm::vec3 col = { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) };

        if ( color_shift_flag ) {
            glm::vec3 col_vel { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
            engine.add_entity( pos, vel, col, col_vel );
        } else {
            engine.add_entity( pos, vel, col );
        }
    }

    TestHarness::init();

    while ( !glfwWindowShouldClose( window ) ) {
        // input
        process_input( window );

        // update
        engine.update();
        if ( TestHarness::update() ) {
            glfwSetWindowShouldClose( window, true );
        }

        // draw
        #if RENDERING_ACTIVE
        renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

        auto entities = engine.get_entities();
        visual_shader.use();
        for ( auto e : entities ) {
            renderer.draw_square(
                e->get_position(),
                e->get_color(),
                0.05f
            );
        }

        renderer.render( &visual_shader );
        #endif

        // poll glfw events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers( window );
    }

    // clean up resources upon successful exit
    glfwTerminate();
    auto avg = TestHarness::get_average();
    std::cout << "test a static: " << avg << std::endl;
}

void test_a_ramp_up() {
    std::cout << "running test a ramp up..." << std::endl;

    for ( int entity_count = RAMP_UP_TEST_ENTITY_COUNT_START; entity_count <= RAMP_UP_TEST_ENTITY_COUNT_MAX; entity_count += RAMP_UP_TEST_ENTITY_COUNT_INCREMENT ) {
        init_glfw_settings();

        // create window object
        std::stringstream title;
        title << "test a ramp up " << entity_count;
        GLFWwindow* window = glfwCreateWindow(
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            title.str().c_str(),
            NULL,
            NULL );

        // ensure creation was successful 
        if ( window == NULL ) {
            std::cerr << "failed to create glfw window" << std::endl;
            glfwTerminate();

            return;
        }

        // set context
        glfwMakeContextCurrent( window );

        // load glad before we make any opengl calls
        if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
            std::cerr << "failed to initialise glad" << std::endl;

            return;
        }

        // set gl viewport size, and set glfw callback for window resize
        glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
        glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

        #if DEBUG_ACTIVE
        glEnable( GL_DEBUG_OUTPUT );
        glDebugMessageCallback( gl_message_callback, 0 );
        #endif

        Shader visual_shader( "shader.vert", "shader.frag" );
        BatchRenderer renderer;

        // engine init
        arch_a::Engine engine;

        for ( int i = 0; i < entity_count; i++ ) {
            int color_shift_flag = rand() % 2;
            glm::vec2 pos = { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ) };
            glm::vec2 vel = { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
            glm::vec3 col = { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) };

            if ( color_shift_flag ) {
                glm::vec3 col_vel { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
                engine.add_entity( pos, vel, col, col_vel );
            } else {
                engine.add_entity( pos, vel, col );
            }
        }

        TestHarness::init();

        while ( !glfwWindowShouldClose( window ) ) {
            // input
            process_input( window );

            // update
            engine.update();
            if ( TestHarness::update() ) {
                glfwSetWindowShouldClose( window, true );
            }

            // draw
            #if RENDERING_ACTIVE
            renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

            auto entities = engine.get_entities();
            visual_shader.use();
            for ( auto e : entities ) {
                renderer.draw_square(
                    e->get_position(),
                    e->get_color(),
                    0.05f
                );
            }

            renderer.render( &visual_shader );
            #endif

            // poll glfw events and swap buffers
            glfwPollEvents();
            glfwSwapBuffers( window );
        }

        // clean up resources upon successful exit
        glfwTerminate();
        auto avg = TestHarness::get_average();
        std::cout << "test a ramp up " << entity_count << ": " << avg << std::endl;
    }
}

void test_a_dynamic_ramp_up() {
    std::cout << "running test a dynamic ramp up..." << std::endl;

    init_glfw_settings();

    // create window object
    GLFWwindow* window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "test a dynamic ramp up",
        NULL,
        NULL );

    // ensure creation was successful 
    if ( window == NULL ) {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();

        return;
    }

    // set context
    glfwMakeContextCurrent( window );

    // load glad before we make any opengl calls
    if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
        std::cerr << "failed to initialise glad" << std::endl;

        return;
    }

    // set gl viewport size, and set glfw callback for window resize
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    #if DEBUG_ACTIVE
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( gl_message_callback, 0 );
    #endif

    Shader visual_shader( "shader.vert", "shader.frag" );
    BatchRenderer renderer;

    // engine init
    arch_a::Engine engine;
    bool ascending = true;
    unsigned int entity_count = 0;

    Timer::start();

    while ( !glfwWindowShouldClose( window ) ) {
        // input
        process_input( window );

        // update
        engine.update();
        if ( ascending ) {
            int color_shift_flag = rand() % 2;
            glm::vec2 pos = { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ) };
            glm::vec2 vel = { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
            glm::vec3 col = { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) };

            if ( color_shift_flag ) {
                glm::vec3 col_vel { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
                engine.add_entity( pos, vel, col, col_vel );
            } else {
                engine.add_entity( pos, vel, col );
            }

            entity_count++;
            if ( entity_count >= DYNAMIC_RAMP_UP_TEST_ENTITY_COUNT_MAX ) {
                ascending = false;
            }
        } else {
            engine.pop_entity();
            entity_count--;
            if ( entity_count <= DYNAMIC_RAMP_UP_TEST_ENTITY_COUNT_MIN ) {
                glfwSetWindowShouldClose( window, true );
            }
        }

        // draw
        #if RENDERING_ACTIVE
        renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

        auto entities = engine.get_entities();
        visual_shader.use();
        for ( auto e : entities ) {
            renderer.draw_square(
                e->get_position(),
                e->get_color(),
                0.05f
            );
        }

        renderer.render( &visual_shader );
        #endif

        // poll glfw events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers( window );
    }

    Timer::end();

    // clean up resources upon successful exit
    glfwTerminate();
    std::cout << "test a dynamic ramp up: " << Timer::get_time_seconds() << std::endl;
}

void test_b_static() {
    std::cout << "running test b static..." << std::endl;

    init_glfw_settings();

    // create window object
    GLFWwindow* window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "test b static",
        NULL,
        NULL );

    // ensure creation was successful 
    if ( window == NULL ) {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();

        return;
    }

    // set context
    glfwMakeContextCurrent( window );

    // load glad before we make any opengl calls
    if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
        std::cerr << "failed to initialise glad" << std::endl;

        return;
    }

    // set gl viewport size, and set glfw callback for window resize
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    #if DEBUG_ACTIVE
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( gl_message_callback, 0 );
    #endif

    Shader visual_shader( "shader.vert", "shader.frag" );
    BatchRenderer renderer;

    // engine init
    arch_b::Engine engine;

    for ( int i = 0; i < STATIC_TEST_ENTITY_COUNT; i++ ) {
        int color_shift_flag = rand() % 2;
        auto e = new arch_b::Entity();
        auto mov = new arch_b::MovementComponent( glm::vec2 { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ) }, glm::vec2 { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) } );
        auto col = new arch_b::ColorComponent( glm::vec3 { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) } );

        e->add_component( mov );
        e->add_component( col );

        if ( color_shift_flag ) {
            auto col_vel = new arch_b::ColorVelocityComponent( glm::vec3 { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) } );
            e->add_component( col_vel );
        }

        engine.add_entity( e );
    }

    TestHarness::init();

    while ( !glfwWindowShouldClose( window ) ) {
        // input
        process_input( window );

        // update
        engine.update();
        if ( TestHarness::update() ) {
            glfwSetWindowShouldClose( window, true );
        }

        // draw
        #if RENDERING_ACTIVE
        renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

        auto entities = engine.get_all_entities();
        visual_shader.use();
        for ( auto e : entities ) {
            auto mov = e->get_component<arch_b::MovementComponent>();
            auto col = e->get_component<arch_b::ColorComponent>();
            if ( mov.has_value() && col.has_value() ) {
                renderer.draw_square(
                    mov.value()->pos,
                    col.value()->value,
                    0.05f
                );
            }
        }

        renderer.render( &visual_shader );
        #endif

        // poll glfw events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers( window );
    }

    // clean up resources upon successful exit
    glfwTerminate();
    auto avg = TestHarness::get_average();
    std::cout << "test b static: " << avg << std::endl;
}

void test_b_ramp_up() {
    std::cout << "running test b ramp up..." << std::endl;

    for ( int entity_count = RAMP_UP_TEST_ENTITY_COUNT_START; entity_count <= RAMP_UP_TEST_ENTITY_COUNT_MAX; entity_count += RAMP_UP_TEST_ENTITY_COUNT_INCREMENT ) {
        init_glfw_settings();

        // create window object
        std::stringstream title;
        title << "test b ramp up " << entity_count;
        GLFWwindow* window = glfwCreateWindow(
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            title.str().c_str(),
            NULL,
            NULL );

        // ensure creation was successful 
        if ( window == NULL ) {
            std::cerr << "failed to create glfw window" << std::endl;
            glfwTerminate();

            return;
        }

        // set context
        glfwMakeContextCurrent( window );

        // load glad before we make any opengl calls
        if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
            std::cerr << "failed to initialise glad" << std::endl;

            return;
        }

        // set gl viewport size, and set glfw callback for window resize
        glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
        glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

        #if DEBUG_ACTIVE
        glEnable( GL_DEBUG_OUTPUT );
        glDebugMessageCallback( gl_message_callback, 0 );
        #endif

        Shader visual_shader( "shader.vert", "shader.frag" );
        BatchRenderer renderer;

        // engine init
        arch_b::Engine engine;

        for ( int i = 0; i < entity_count; i++ ) {
            int color_shift_flag = rand() % 2;
            auto e = new arch_b::Entity();
            auto mov = new arch_b::MovementComponent( glm::vec2 { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ) }, glm::vec2 { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) } );
            auto col = new arch_b::ColorComponent( glm::vec3 { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) } );

            e->add_component( mov );
            e->add_component( col );

            if ( color_shift_flag ) {
                auto col_vel = new arch_b::ColorVelocityComponent( glm::vec3 { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) } );
                e->add_component( col_vel );
            }

            engine.add_entity( e );
        }

        TestHarness::init();

        while ( !glfwWindowShouldClose( window ) ) {
            // input
            process_input( window );

            // update
            engine.update();
            if ( TestHarness::update() ) {
                glfwSetWindowShouldClose( window, true );
            }

            // draw
            #if RENDERING_ACTIVE
            renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

            auto entities = engine.get_all_entities();
            visual_shader.use();
            for ( auto e : entities ) {
                auto mov = e->get_component<arch_b::MovementComponent>();
                auto col = e->get_component<arch_b::ColorComponent>();
                if ( mov.has_value() && col.has_value() ) {
                    renderer.draw_square(
                        mov.value()->pos,
                        col.value()->value,
                        0.05f
                    );
                }
            }

            renderer.render( &visual_shader );
            #endif

            // poll glfw events and swap buffers
            glfwPollEvents();
            glfwSwapBuffers( window );
        }

        // clean up resources upon successful exit
        glfwTerminate();
        auto avg = TestHarness::get_average();
        std::cout << "test b ramp up " << entity_count << ": " << avg << std::endl;
    }
}

void test_b_dynamic_ramp_up() {
    std::cout << "running test b dynamic ramp up..." << std::endl;

    init_glfw_settings();

    // create window object
    GLFWwindow* window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "test b dynamic ramp up",
        NULL,
        NULL );

    // ensure creation was successful 
    if ( window == NULL ) {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();

        return;
    }

    // set context
    glfwMakeContextCurrent( window );

    // load glad before we make any opengl calls
    if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
        std::cerr << "failed to initialise glad" << std::endl;

        return;
    }

    // set gl viewport size, and set glfw callback for window resize
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    #if DEBUG_ACTIVE
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( gl_message_callback, 0 );
    #endif

    Shader visual_shader( "shader.vert", "shader.frag" );
    BatchRenderer renderer;

    // engine init
    arch_b::Engine engine;
    bool ascending = true;
    unsigned int entity_count = 0;

    Timer::start();

    while ( !glfwWindowShouldClose( window ) ) {
        // input
        process_input( window );

        // update
        engine.update();
        if ( ascending ) {
            int color_shift_flag = rand() % 2;
            auto e = new arch_b::Entity();
            auto mov = new arch_b::MovementComponent( glm::vec2 { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ) }, glm::vec2 { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) } );
            auto col = new arch_b::ColorComponent( glm::vec3 { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) } );

            e->add_component( mov );
            e->add_component( col );

            if ( color_shift_flag ) {
                auto col_vel = new arch_b::ColorVelocityComponent( glm::vec3 { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) } );
                e->add_component( col_vel );
            }

            engine.add_entity( e );

            entity_count++;
            if ( entity_count >= DYNAMIC_RAMP_UP_TEST_ENTITY_COUNT_MAX ) {
                ascending = false;
            }
        } else {
            engine.pop_entity();
            entity_count--;
            if ( entity_count <= DYNAMIC_RAMP_UP_TEST_ENTITY_COUNT_MIN ) {
                glfwSetWindowShouldClose( window, true );
            }
        }

        // draw
        #if RENDERING_ACTIVE
        renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

        auto entities = engine.get_all_entities();
        visual_shader.use();
        for ( auto e : entities ) {
            auto mov = e->get_component<arch_b::MovementComponent>();
            auto col = e->get_component<arch_b::ColorComponent>();
            if ( mov.has_value() && col.has_value() ) {
                renderer.draw_square(
                    mov.value()->pos,
                    col.value()->value,
                    0.05f
                );
            }
        }

        renderer.render( &visual_shader );
        #endif

        // poll glfw events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers( window );
    }

    Timer::end();

    // clean up resources upon successful exit
    glfwTerminate();
    std::cout << "test b dynamic ramp up: " << Timer::get_time_seconds() << std::endl;
}

void test_c_static() {
    std::cout << "running test c static..." << std::endl;

    init_glfw_settings();

    // create window object
    GLFWwindow* window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "test c static",
        NULL,
        NULL );

    // ensure creation was successful 
    if ( window == NULL ) {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();

        return;
    }

    // set context
    glfwMakeContextCurrent( window );

    // load glad before we make any opengl calls
    if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
        std::cerr << "failed to initialise glad" << std::endl;

        return;
    }

    // set gl viewport size, and set glfw callback for window resize
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    #if DEBUG_ACTIVE
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( gl_message_callback, 0 );
    #endif

    Shader visual_shader( "shader.vert", "shader.frag" );
    BatchRenderer renderer;

    // engine init
    arch_c::Engine engine;
    std::vector<arch_c::Entity> active_entities;

    for ( int i = 0; i < STATIC_TEST_ENTITY_COUNT; ++i ) {
        auto e = engine.add_entity();
        if ( e.has_value() ) {
            auto entity = e.value();
            active_entities.push_back( entity );
            auto mov = engine.add_movable_component( entity );
            auto col = engine.add_color_component( entity );

            *mov = arch_c::MovableComponent { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
            *col = arch_c::ColorComponent { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) };

            int color_shift_flag = rand() % 2;
            if ( color_shift_flag ) {
                auto col_vel = engine.add_color_velocity_component( entity );
                *col_vel = arch_c::ColorVelocityComponent { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
            }
        }
    }

    TestHarness::init();

    while ( !glfwWindowShouldClose( window ) ) {
        // input
        process_input( window );

        // update
        engine.movement_system();
        engine.color_shift_system();
        if ( TestHarness::update() ) {
            glfwSetWindowShouldClose( window, true );
        }

        // draw
        #if RENDERING_ACTIVE
        renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

        visual_shader.use();
        for ( auto& entity : active_entities ) {
            auto mov = engine.get_movable_component( entity );
            auto col = engine.get_color_component( entity );
            renderer.draw_square(
                glm::vec2 { mov->pos_x, mov->pos_y },
                glm::vec3 { col->r, col->g, col->b },
                0.05f
            );
        }

        renderer.render( &visual_shader );
        #endif

        // poll glfw events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers( window );
    }

    // clean up resources upon successful exit
    glfwTerminate();
    auto avg = TestHarness::get_average();
    std::cout << "test c static: " << avg << std::endl;
}

void test_c_ramp_up() {
    std::cout << "running test c ramp up..." << std::endl;

    for ( int entity_count = RAMP_UP_TEST_ENTITY_COUNT_START; entity_count <= RAMP_UP_TEST_ENTITY_COUNT_MAX; entity_count += RAMP_UP_TEST_ENTITY_COUNT_INCREMENT ) {
        init_glfw_settings();

        // create window object
        std::stringstream title;
        title << "test c ramp up " << entity_count;
        GLFWwindow* window = glfwCreateWindow(
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            title.str().c_str(),
            NULL,
            NULL );

        // ensure creation was successful 
        if ( window == NULL ) {
            std::cerr << "failed to create glfw window" << std::endl;
            glfwTerminate();

            return;
        }

        // set context
        glfwMakeContextCurrent( window );

        // load glad before we make any opengl calls
        if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
            std::cerr << "failed to initialise glad" << std::endl;

            return;
        }

        // set gl viewport size, and set glfw callback for window resize
        glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
        glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

        #if DEBUG_ACTIVE
        glEnable( GL_DEBUG_OUTPUT );
        glDebugMessageCallback( gl_message_callback, 0 );
        #endif

        Shader visual_shader( "shader.vert", "shader.frag" );
        BatchRenderer renderer;

        // engine init
        arch_c::Engine engine;
        std::vector<arch_c::Entity> active_entities;

        for ( int i = 0; i < STATIC_TEST_ENTITY_COUNT; ++i ) {
            auto e = engine.add_entity();
            if ( e.has_value() ) {
                auto entity = e.value();
                active_entities.push_back( entity );
                auto mov = engine.add_movable_component( entity );
                auto col = engine.add_color_component( entity );

                *mov = arch_c::MovableComponent { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
                *col = arch_c::ColorComponent { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) };

                int color_shift_flag = rand() % 2;
                if ( color_shift_flag ) {
                    auto col_vel = engine.add_color_velocity_component( entity );
                    *col_vel = arch_c::ColorVelocityComponent { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
                }
            }
        }

        TestHarness::init();

        while ( !glfwWindowShouldClose( window ) ) {
            // input
            process_input( window );

            // update
            engine.movement_system();
            engine.color_shift_system();
            if ( TestHarness::update() ) {
                glfwSetWindowShouldClose( window, true );
            }

            // draw
            #if RENDERING_ACTIVE
            renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

            visual_shader.use();
            for ( auto& entity : active_entities ) {
                auto mov = engine.get_movable_component( entity );
                auto col = engine.get_color_component( entity );
                renderer.draw_square(
                    glm::vec2 { mov->pos_x, mov->pos_y },
                    glm::vec3 { col->r, col->g, col->b },
                    0.05f
                );
            }

            renderer.render( &visual_shader );
            #endif

            // poll glfw events and swap buffers
            glfwPollEvents();
            glfwSwapBuffers( window );
        }

        // clean up resources upon successful exit
        glfwTerminate();
        auto avg = TestHarness::get_average();
        std::cout << "test c ramp up " << entity_count << ": " << avg << std::endl;
    }
}

void test_c_dynamic_ramp_up() {
    std::cout << "running test c dynamic ramp up..." << std::endl;

    init_glfw_settings();

    // create window object
    GLFWwindow* window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "test c dynamic ramp up",
        NULL,
        NULL );

    // ensure creation was successful 
    if ( window == NULL ) {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();

        return;
    }

    // set context
    glfwMakeContextCurrent( window );

    // load glad before we make any opengl calls
    if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
        std::cerr << "failed to initialise glad" << std::endl;

        return;
    }

    // set gl viewport size, and set glfw callback for window resize
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    #if DEBUG_ACTIVE
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( gl_message_callback, 0 );
    #endif

    Shader visual_shader( "shader.vert", "shader.frag" );
    BatchRenderer renderer;

    // engine init
    arch_c::Engine engine;
    std::vector<arch_c::Entity> active_entities;
    bool ascending = true;
    unsigned int entity_count = 0;

    Timer::start();

    while ( !glfwWindowShouldClose( window ) ) {
        // input
        process_input( window );

        // update
        engine.movement_system();
        engine.color_shift_system();
        if ( ascending ) {
            auto e = engine.add_entity();
            if ( e.has_value() ) {
                auto entity = e.value();
                active_entities.push_back( entity );
                auto mov = engine.add_movable_component( entity );
                auto col = engine.add_color_component( entity );

                *mov = arch_c::MovableComponent { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
                *col = arch_c::ColorComponent { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) };

                int color_shift_flag = rand() % 2;
                if ( color_shift_flag ) {
                    auto col_vel = engine.add_color_velocity_component( entity );
                    *col_vel = arch_c::ColorVelocityComponent { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
                }

                entity_count++;
                if ( entity_count >= DYNAMIC_RAMP_UP_TEST_ENTITY_COUNT_MAX ) {
                    ascending = false;
                }
            }
        } else {
            engine.remove_entity( active_entities.back() );
            active_entities.pop_back();
            entity_count--;
            if ( entity_count <= DYNAMIC_RAMP_UP_TEST_ENTITY_COUNT_MIN ) {
                glfwSetWindowShouldClose( window, true );
            }
        }

        // draw
        #if RENDERING_ACTIVE
        renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

        visual_shader.use();
        for ( auto& entity : active_entities ) {
            auto mov = engine.get_movable_component( entity );
            auto col = engine.get_color_component( entity );
            renderer.draw_square(
                glm::vec2 { mov->pos_x, mov->pos_y },
                glm::vec3 { col->r, col->g, col->b },
                0.05f
            );
        }

        renderer.render( &visual_shader );
        #endif

        // poll glfw events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers( window );
    }

    Timer::end();

    // clean up resources upon successful exit
    glfwTerminate();
    std::cout << "test c dynamic ramp up: " << Timer::get_time_seconds() << std::endl;
}

void test_d_static() {
    std::cout << "running test d static..." << std::endl;

    init_glfw_settings();

    // create window object
    GLFWwindow* window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "test d static",
        NULL,
        NULL );

    // ensure creation was successful 
    if ( window == NULL ) {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();

        return;
    }

    // set context
    glfwMakeContextCurrent( window );

    // load glad before we make any opengl calls
    if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
        std::cerr << "failed to initialise glad" << std::endl;

        return;
    }

    // set gl viewport size, and set glfw callback for window resize
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    #if DEBUG_ACTIVE
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( gl_message_callback, 0 );
    #endif

    Shader visual_shader( "shader.vert", "shader.frag" );
    BatchRenderer renderer;

    // engine init
    arch_d::Engine engine;
    std::vector<arch_d::Entity> active_entities;

    //for ( int i = 0; i < STATIC_TEST_ENTITY_COUNT; ++i ) {
    for ( int i = 0; i < 10; ++i ) {
        auto e = engine.add_entity();
        if ( e.has_value() ) {
            auto entity = e.value();
            active_entities.push_back( entity );
            auto mov = engine.add_movable_component( entity );
            auto col = engine.add_color_component( entity );

            *mov = arch_d::MovableComponent { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
            *col = arch_d::ColorComponent { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) };

            int color_shift_flag = rand() % 2;
            if ( color_shift_flag ) {
                auto col_vel = engine.add_color_velocity_component( entity );
                *col_vel = arch_d::ColorVelocityComponent { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
            }
        }
    }

    TestHarness::init();

    while ( !glfwWindowShouldClose( window ) ) {
        // input
        process_input( window );

        // update
        engine.movement_system();
        engine.color_shift_system();
        if ( TestHarness::update() ) {
            glfwSetWindowShouldClose( window, true );
        }

        // draw
        #if RENDERING_ACTIVE
        renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

        visual_shader.use();
        for ( auto& entity : active_entities ) {
            auto mov = engine.get_movable_component( entity );
            auto col = engine.get_color_component( entity );
            renderer.draw_square(
                glm::vec2 { mov->pos_x, mov->pos_y },
                glm::vec3 { col->r, col->g, col->b },
                0.05f
            );
        }

        renderer.render( &visual_shader );
        #endif

        // poll glfw events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers( window );
    }

    // clean up resources upon successful exit
    glfwTerminate();
    auto avg = TestHarness::get_average();
    std::cout << "test d static: " << avg << std::endl;
}

void test_d_ramp_up() {
    std::cout << "running test d ramp up..." << std::endl;

    for ( int entity_count = RAMP_UP_TEST_ENTITY_COUNT_START; entity_count <= RAMP_UP_TEST_ENTITY_COUNT_MAX; entity_count += RAMP_UP_TEST_ENTITY_COUNT_INCREMENT ) {
        init_glfw_settings();

        // create window object
        std::stringstream title;
        title << "test d ramp up " << entity_count;
        GLFWwindow* window = glfwCreateWindow(
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            title.str().c_str(),
            NULL,
            NULL );

        // ensure creation was successful 
        if ( window == NULL ) {
            std::cerr << "failed to create glfw window" << std::endl;
            glfwTerminate();

            return;
        }

        // set context
        glfwMakeContextCurrent( window );

        // load glad before we make any opengl calls
        if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
            std::cerr << "failed to initialise glad" << std::endl;

            return;
        }

        // set gl viewport size, and set glfw callback for window resize
        glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
        glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

        #if DEBUG_ACTIVE
        glEnable( GL_DEBUG_OUTPUT );
        glDebugMessageCallback( gl_message_callback, 0 );
        #endif

        Shader visual_shader( "shader.vert", "shader.frag" );
        BatchRenderer renderer;

        // engine init
        arch_d::Engine engine;
        std::vector<arch_d::Entity> active_entities;

        for ( int i = 0; i < STATIC_TEST_ENTITY_COUNT; ++i ) {
            auto e = engine.add_entity();
            if ( e.has_value() ) {
                auto entity = e.value();
                active_entities.push_back( entity );
                auto mov = engine.add_movable_component( entity );
                auto col = engine.add_color_component( entity );

                *mov = arch_d::MovableComponent { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
                *col = arch_d::ColorComponent { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) };

                int color_shift_flag = rand() % 2;
                if ( color_shift_flag ) {
                    auto col_vel = engine.add_color_velocity_component( entity );
                    *col_vel = arch_d::ColorVelocityComponent { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
                }
            }
        }

        TestHarness::init();

        while ( !glfwWindowShouldClose( window ) ) {
            // input
            process_input( window );

            // update
            engine.movement_system();
            engine.color_shift_system();
            if ( TestHarness::update() ) {
                glfwSetWindowShouldClose( window, true );
            }

            // draw
            #if RENDERING_ACTIVE
            renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

            visual_shader.use();
            for ( auto& entity : active_entities ) {
                auto mov = engine.get_movable_component( entity );
                auto col = engine.get_color_component( entity );
                renderer.draw_square(
                    glm::vec2 { mov->pos_x, mov->pos_y },
                    glm::vec3 { col->r, col->g, col->b },
                    0.05f
                );
            }

            renderer.render( &visual_shader );
            #endif

            // poll glfw events and swap buffers
            glfwPollEvents();
            glfwSwapBuffers( window );
        }

        // clean up resources upon successful exit
        glfwTerminate();
        auto avg = TestHarness::get_average();
        std::cout << "test d ramp up " << entity_count << ": " << avg << std::endl;
    }
}

void test_d_dynamic_ramp_up() {
    std::cout << "running test d dynamic ramp up..." << std::endl;

    init_glfw_settings();

    // create window object
    GLFWwindow* window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "test d dynamic ramp up",
        NULL,
        NULL );

    // ensure creation was successful 
    if ( window == NULL ) {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();

        return;
    }

    // set context
    glfwMakeContextCurrent( window );

    // load glad before we make any opengl calls
    if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
        std::cerr << "failed to initialise glad" << std::endl;

        return;
    }

    // set gl viewport size, and set glfw callback for window resize
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    #if DEBUG_ACTIVE
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( gl_message_callback, 0 );
    #endif

    Shader visual_shader( "shader.vert", "shader.frag" );
    BatchRenderer renderer;

    // engine init
    arch_d::Engine engine;
    std::vector<arch_d::Entity> active_entities;
    bool ascending = true;
    unsigned int entity_count = 0;

    Timer::start();

    while ( !glfwWindowShouldClose( window ) ) {
        // input
        process_input( window );

        // update
        engine.movement_system();
        engine.color_shift_system();
        if ( ascending ) {
            auto e = engine.add_entity();
            if ( e.has_value() ) {
                auto entity = e.value();
                active_entities.push_back( entity );
                auto mov = engine.add_movable_component( entity );
                auto col = engine.add_color_component( entity );

                *mov = arch_d::MovableComponent { rand_f( -1.0, 1.0 ), rand_f( -1.0, 1.0 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
                *col = arch_d::ColorComponent { rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ), rand_f( 0.0, 1.0 ) };

                int color_shift_flag = rand() % 2;
                if ( color_shift_flag ) {
                    auto col_vel = engine.add_color_velocity_component( entity );
                    *col_vel = arch_d::ColorVelocityComponent { rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ), rand_f( -0.01, 0.01 ) };
                }

                entity_count++;
                if ( entity_count >= DYNAMIC_RAMP_UP_TEST_ENTITY_COUNT_MAX ) {
                    ascending = false;
                }
            }
        } else {
            engine.remove_entity( active_entities.back() );
            active_entities.pop_back();
            entity_count--;
            if ( entity_count <= DYNAMIC_RAMP_UP_TEST_ENTITY_COUNT_MIN ) {
                glfwSetWindowShouldClose( window, true );
            }
        }

        // draw
        #if RENDERING_ACTIVE
        renderer.clear( glm::vec3( 0.1f, 0.1f, 0.1f ) );

        visual_shader.use();
        for ( auto& entity : active_entities ) {
            auto mov = engine.get_movable_component( entity );
            auto col = engine.get_color_component( entity );
            renderer.draw_square(
                glm::vec2 { mov->pos_x, mov->pos_y },
                glm::vec3 { col->r, col->g, col->b },
                0.05f
            );
        }

        renderer.render( &visual_shader );
        #endif

        // poll glfw events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers( window );
    }

    Timer::end();

    // clean up resources upon successful exit
    glfwTerminate();
    std::cout << "test d dynamic ramp up: " << Timer::get_time_seconds() << std::endl;
}

#if DEBUG_ACTIVE
// more information at https://www.khronos.org/opengl/wiki/Debug_Output
void GLAPIENTRY gl_message_callback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param ) {
    // parse source
    std::string source_name;
    switch ( source ) {
        case GL_DEBUG_SOURCE_API:
            source_name = "GL_DEBUG_SOURCE_API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            source_name = "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            source_name = "GL_DEBUG_SOURCE_SHADER_COMPILER";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            source_name = "GL_DEBUG_SOURCE_THIRD_PARTY";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            source_name = "GL_DEBUG_SOURCE_APPLICATION";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            source_name = "GL_DEBUG_SOURCE_OTHER";
            break;

        default:
            source_name = "UNKNOWN";
            break;
    }

    // parse type
    std::string type_name;
    switch ( type ) {
        case GL_DEBUG_TYPE_ERROR:
            type_name = "GL_DEBUG_TYPE_ERROR";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            type_name = "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            type_name = "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            type_name = "GL_DEBUG_TYPE_PORTABILITY";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            type_name = "GL_DEBUG_TYPE_PERFORMANCE";
            break;

        case GL_DEBUG_TYPE_MARKER:
            type_name = "GL_DEBUG_TYPE_MARKER";
            break;

        case GL_DEBUG_TYPE_PUSH_GROUP:
            type_name = "GL_DEBUG_TYPE_PUSH_GROUP";
            break;

        case GL_DEBUG_TYPE_POP_GROUP:
            type_name = "GL_DEBUG_TYPE_POP_GROUP";
            break;

        case GL_DEBUG_TYPE_OTHER:
            type_name = "GL_DEBUG_TYPE_OTHER";
            break;

        default:
            type_name = "UNKNOWN";
            break;
    }

    // parse severity
    std::string severity_name;
    switch ( severity ) {
        case GL_DEBUG_SEVERITY_HIGH:
            severity_name = "GL_DEBUG_SEVERITY_HIGH";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            severity_name = "GL_DEBUG_SEVERITY_MEDIUM";
            break;

        case GL_DEBUG_SEVERITY_LOW:
            severity_name = "GL_DEBUG_SEVERITY_LOW";
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severity_name = "GL_DEBUG_SEVERITY_NOTIFICATION";
            break;

        default:
            severity_name = "UNKNOWN";
            break;
    }


    // print message
    std::cerr << "GL CALLBACK:\n";
    std::cerr << "source: " << source_name << "\n";
    std::cerr << "type: " << type_name << "\n";
    std::cerr << "severity: " << severity_name << "\n";
    std::cerr << "message: " << message << "\n";
    std::cerr << std::endl;
}
#endif
