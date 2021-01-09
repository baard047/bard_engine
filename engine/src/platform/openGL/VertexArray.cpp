/*
 * \file VertexArray.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 07.01.2021
 * \time : 22:14
 */

#include "VertexArray.h"

#include <glad/glad.h>

namespace OpenGL {

using namespace bard;

namespace {

GLenum convert( ShaderDataType type )
{
    switch ( type )
    {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:      return GL_FLOAT;
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:      return GL_INT;
        case ShaderDataType::Bool:      return GL_BOOL;
        case ShaderDataType::None:      break;
    }

    BARD_CORE_ASSERT( false, "Unknown shared type!" );
    return 0;
}

}

VertexArray::VertexArray()
{
    glCreateVertexArrays( 1, &m_buffer );
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays( 1, &m_buffer );
}

void VertexArray::bind() const
{
    glBindVertexArray( m_buffer );
}

void VertexArray::unbind() const
{
    glBindVertexArray( 0 );
}

void VertexArray::addVertexBuffer( const VertexBuffer::Ptr & vertexBuffer )
{
    const auto & layout = vertexBuffer->layout();
    if( layout.size() == 0 )
    {
        BARD_CORE_ASSERT( false, "Layout is empty!");
        return;
    }

    glBindVertexArray( m_buffer );
    vertexBuffer->bind();

    for( size_t index = 0; index < layout.size(); ++index )
    {
        const auto & elem = layout[ index ];
        glEnableVertexAttribArray( index );
        glVertexAttribPointer( index, elem.getComponentCount(), convert( elem.type ),
                               elem.normalized ? GL_TRUE : GL_FALSE,
                               layout.getStride(), ( const void * ) elem.offset );
    }

    m_vertexBuffers.emplace_back( vertexBuffer );
}

void VertexArray::setIndexBuffer( const IndexBuffer::Ptr & indexBuffer )
{
    glBindVertexArray( m_buffer );
    indexBuffer->bind();

    m_indexBuffer = indexBuffer;
}

const VertexArray::VertexBuffers & VertexArray::getVertexBuffers() const
{
    return m_vertexBuffers;
}

const IndexBuffer::Ptr & VertexArray::getIndexBuffer() const
{
    return m_indexBuffer;
}
}
