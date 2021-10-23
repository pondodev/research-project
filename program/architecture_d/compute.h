#ifndef COMPUTE_H
#define COMPUTE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Compute {
    public:
    unsigned int id;
    unsigned int tex1;
    unsigned int tex2;

    Compute( const char* path, glm::uvec2 size ) {
        work_size = size;

        // read in shader code
        std::string compute_code;
        std::ifstream file;

        file.exceptions( std::ifstream::failbit | std::ifstream::badbit );

        try {
            file.open( path );
            std::stringstream file_stream;
            file_stream << file.rdbuf();
            file.close();

            compute_code = file_stream.str();
        } catch ( std::ifstream::failure e ) {
            std::cerr << "failed to read compute shader file" << std::endl;
        }

        const char* c_shader_code = compute_code.c_str();

        // compile shader
        unsigned int shader;

        shader = glCreateShader( GL_COMPUTE_SHADER );
        glShaderSource( shader, 1, &c_shader_code, NULL );
        glCompileShader( shader );

        // create program
        id = glCreateProgram();
        glAttachShader( id, shader );
        glLinkProgram( id );

        // cleanup
        glDeleteShader( shader );

        // create input/output textures
        glGenTextures( 1, &tex1 );
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, tex1 );

        // turns out we need this. huh.
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

        // create empty texture
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, size.x, size.y, 0, GL_RGBA, GL_FLOAT, NULL );
        glBindImageTexture( 0, tex1, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32F );

        // do the same for the second texture
        glGenTextures( 1, &tex2 );
        glActiveTexture( GL_TEXTURE1 );
        glBindTexture( GL_TEXTURE_2D, tex2 );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, size.x, size.y, 0, GL_RGBA, GL_FLOAT, NULL );
        glBindImageTexture( 0, tex1, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32F );
    }

    ~Compute() {
        glDeleteProgram( id );
    }

    void use() {
        glUseProgram( id );
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, tex1 );
    }

    void dispatch() {
        // just keep it simple, 2d work group
        glDispatchCompute( work_size.x, work_size.y, 1 );
    }

    void wait() {
        glMemoryBarrier( GL_ALL_BARRIER_BITS );
    }

    void set_values( int tex, float* values ) {
        if ( tex == 1 ) {
            glActiveTexture( GL_TEXTURE0 );
            glBindTexture( GL_TEXTURE_2D, tex1 );
        } else {
            glActiveTexture( GL_TEXTURE1 );
            glBindTexture( GL_TEXTURE_2D, tex2 );
        }

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, work_size.x, work_size.y, 0, GL_RGBA, GL_FLOAT, values );
    }

    std::vector<float> get_values() {
        unsigned int collection_size = work_size.x * work_size.y;
        std::vector<float> compute_data( collection_size );
        glGetTexImage( GL_TEXTURE_2D, 0, GL_RED, GL_FLOAT, compute_data.data() );

        return compute_data;
    }

private:
    glm::uvec2 work_size;
};

#endif
