#ifndef BATCH_RENDERER_H
#define BATCH_RENDERER_H

#include <vector>
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "dan_math.h"

class BatchRenderer {
public:
    BatchRenderer() {
        // create our vertex buffer and array objects
        glGenBuffers( 1, &vbo );
        glGenBuffers( 1, &ebo );
        glGenVertexArrays( 1, &vao );

        // bind the vbo, ebo, and vao
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
        glBindVertexArray( vao );

        // set attributes
        // position
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, stride, (void*) 0 );
        glEnableVertexAttribArray( 0 );
        // color
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, stride, (void*) (2 * sizeof(float)) );
        glEnableVertexAttribArray( 1 );

        square_count = 0;
    }

    ~BatchRenderer() {
        glDeleteBuffers( 1, &vbo );
        glDeleteBuffers( 1, &ebo );
        glDeleteVertexArrays( 1, &vao );
    }

    void clear( glm::vec3 color ) {
        // prepare collections for new render
        vbo_data.clear();
        ebo_data.clear();
        square_count = 0;

        // clear the screen
        glClearColor( color.r, color.g, color.b, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
    }

    // i know this is really bad, but i don't want to waste my time
    // on rendering when that's not the point of the project
    void draw_square( glm::vec2 pos, glm::vec3 color, float size ) {
        const size_t quad_array_size = stride * 4; // stride * vertex count
        float temp_vbo[ quad_array_size ];

        // place position and colour data
        temp_vbo[ 0 ] = pos.x;
        temp_vbo[ 1 ] = pos.y;
        temp_vbo[ 2 ] = color.r;
        temp_vbo[ 3 ] = color.g;
        temp_vbo[ 4 ] = color.b;

        temp_vbo[ 5 ] = pos.x + size;
        temp_vbo[ 6 ] = pos.y;
        temp_vbo[ 7 ] = color.r;
        temp_vbo[ 8 ] = color.g;
        temp_vbo[ 9 ] = color.b;

        temp_vbo[ 10 ] = pos.x;
        temp_vbo[ 11 ] = pos.y - size;
        temp_vbo[ 12 ] = color.r;
        temp_vbo[ 13 ] = color.g;
        temp_vbo[ 14 ] = color.b;

        temp_vbo[ 15 ] = pos.x + size;
        temp_vbo[ 16 ] = pos.y - size;
        temp_vbo[ 17 ] = color.r;
        temp_vbo[ 18 ] = color.g;
        temp_vbo[ 19 ] = color.b;

        const size_t ebo_size = 6;
        unsigned int temp_ebo[ ebo_size ] = { 0, 1, 2, 1, 2, 3 };

        // send data to gpu and draw
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof(float) * quad_array_size, temp_vbo, GL_DYNAMIC_DRAW );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * ebo_size, temp_ebo, GL_DYNAMIC_DRAW );

        glBindVertexArray( vao );
        glDrawElements( GL_TRIANGLES, ebo_size, GL_UNSIGNED_INT, NULL );
    }

    // takes in 2d ndc pos and 8-bit color
    void add_square( glm::vec2 pos, glm::vec3 color, float size ) {
        // top left, top right, bottom right, bottom left
        push_vert( pos.x, pos.y, color.r, color.g, color.b );
        push_vert( pos.x+size, pos.y, color.r, color.g, color.b );
        push_vert( pos.x, pos.y-size, color.r, color.g, color.b );
        push_vert( pos.x+size, pos.y-size, color.r, color.g, color.b );

        // add indices to ebo
        unsigned int ebo_offset = square_count * 4;
        // first tri
        ebo_data.emplace_back( ebo_offset );
        ebo_data.emplace_back( ebo_offset+1 );
        ebo_data.emplace_back( ebo_offset+2 );
        // second tri
        ebo_data.emplace_back( ebo_offset+1 );
        ebo_data.emplace_back( ebo_offset+2 );
        ebo_data.emplace_back( ebo_offset+3 );

        square_count++;
    }

    void render( Shader* shader ) {
        shader->use();

        // send data to gl
        auto vbo_ptr = vbo_data.data();
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vbo_ptr) * vbo_data.size(), vbo_ptr, GL_DYNAMIC_DRAW );

        auto ebo_ptr = ebo_data.data();
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(ebo_ptr) * ebo_data.size(), ebo_ptr, GL_DYNAMIC_DRAW );

        // actually render
        glBindVertexArray( vao );
        glDrawElements( GL_TRIANGLES, ebo_data.size(), GL_UNSIGNED_INT, NULL );
    }

private:
    const unsigned int stride = 5 * sizeof(float); // vec2 pos, vec3 color

    unsigned int vbo, ebo, vao;
    std::vector<float> vbo_data;
    std::vector<unsigned int> ebo_data;
    unsigned int square_count;

    void push_vert( float x, float y, float r, float g, float b ) {
        // coords are in ndc
        // TODO: mvp matrix?
        vbo_data.emplace_back( x );
        vbo_data.emplace_back( y );

        vbo_data.emplace_back( r );
        vbo_data.emplace_back( g );
        vbo_data.emplace_back( b );
    }
};

#endif
