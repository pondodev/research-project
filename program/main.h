#ifndef MAIN_H
#define MAIN_H

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define DEBUG_ACTIVE false
#define RENDERING_ACTIVE false

#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "consts.h"
#include "shader.h"
#include "batch_renderer.h"
#include "test_harness.h"

#include "architecture_a/engine.h"

void init_glfw_settings();
void framebuffer_size_callback( GLFWwindow* window, int width, int height );
void process_input( GLFWwindow* window );

// test a
void test_a_static();
void test_a_ramp_up();
void test_a_dynamic_ramp_up();

#if DEBUG_ACTIVE
void GLAPIENTRY gl_message_callback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param );
#endif

#endif
