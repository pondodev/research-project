#ifndef MAIN_H
#define MAIN_H

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define DEBUG_ACTIVE false
#define RENDERING_ACTIVE false
#define SINGLE_BUFFERING_ACTIVE true

#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "consts.h"
#include "shader.h"
#include "batch_renderer.h"
#include "test_harness.h"
#include "timer.h"

#include "architecture_a/engine.h"
#include "architecture_b/engine.h"
#include "architecture_b/entity.h"
#include "architecture_b/components.h"
#include "architecture_c/engine.h"
#include "architecture_c/components.h"
#include "architecture_d/engine.h"
#include "architecture_d/components.h"

void init_glfw_settings();
void framebuffer_size_callback( GLFWwindow* window, int width, int height );
void process_input( GLFWwindow* window );

// test a
void test_a_static();
void test_a_ramp_up();
void test_a_dynamic_ramp_up();

// test b
void test_b_static();
void test_b_ramp_up();
void test_b_dynamic_ramp_up();

// test c
void test_c_static();
void test_c_ramp_up();
void test_c_dynamic_ramp_up();

// test d
void test_d_static();
void test_d_ramp_up();
void test_d_dynamic_ramp_up();

#if DEBUG_ACTIVE
void GLAPIENTRY gl_message_callback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param );
#endif

#endif
