/*
 * \file OpenGlBuffer.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:29
 */

#include "OpenGlBuffer.h"

#include <glad/glad.h>

namespace bard::OpenGL
{

////////////////////////////// VertexBuffer //////////////////////////////

VertexBuffer::VertexBuffer( float * vertices, uint32_t size )
{
    glCreateBuffers( 1, &m_buffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_buffer );
    glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_buffer );
}

void VertexBuffer::bind() const
{
    glBindBuffer( GL_ARRAY_BUFFER, m_buffer );
}

void VertexBuffer::unbind() const
{
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


////////////////////////////// IndexBuffer //////////////////////////////

IndexBuffer::IndexBuffer( uint32_t * indices, uint32_t count )
    : m_count( count )
{
    glCreateBuffers( 1, &m_buffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_buffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( uint32_t ) * count, indices, GL_STATIC_DRAW );
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_buffer );
}

void IndexBuffer::bind() const
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_buffer );
}

void IndexBuffer::unbind() const
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

}