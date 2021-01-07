/*
 * \file Buffer.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:18
 */

#include "Buffer.h"

#include <bard/core/Base.h>
#include "bard/renderer/Renderer.h"

#include <platform/openGL/Buffer.h>

namespace bard::Base {

VertexBuffer::Ptr VertexBuffer::create( float * vertices, uint32_t size )
{
    switch ( Renderer::API )
    {
        case RendererAPI::None:
        BARD_CORE_ASSERT( false, "RendererAPI::None" );
            return nullptr;
        case RendererAPI::OpenGL:
            return std::make_shared< OpenGL::VertexBuffer >( vertices, size );
    }
    return nullptr;
}

VertexBuffer::Ptr VertexBuffer::create( float * vertices, uint32_t size, BufferLayout && layout )
{
    auto buffer = VertexBuffer::create( vertices, size );
    buffer->setLayout( std::move( layout ) );
    return buffer;
}

IndexBuffer::Ptr IndexBuffer::create( uint32_t * indices, uint32_t count )
{
    switch ( Renderer::API )
    {
        case RendererAPI::None:
        BARD_CORE_ASSERT( false, "RendererAPI::None" );
            return nullptr;
        case RendererAPI::OpenGL:
            return std::make_shared< OpenGL::IndexBuffer >( indices, count );
    }
    return nullptr;
}

}