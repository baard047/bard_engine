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

namespace bard {

VertexBuffer::Ptr VertexBuffer::create( uint32_t size )
{
    return createImpl( size );
}

VertexBuffer::Ptr VertexBuffer::create( float * vertices, uint32_t size )
{
    return createImpl( vertices, size );
}

VertexBuffer::Ptr VertexBuffer::create( float * vertices, uint32_t size, BufferLayout && layout )
{
    auto buffer = VertexBuffer::create( vertices, size );
    buffer->setLayout( std::move( layout ) );
    return buffer;
}

template< class... Args >
VertexBuffer::Ptr VertexBuffer::createImpl( Args && ... args )
{
    switch ( Renderer::getAPI() )
    {
        case RendererAPI::API::None: BARD_CORE_ASSERT( false, "RendererAPI::None" ); return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared< OpenGL::VertexBuffer >(  std::forward<Args>( args )... );
    }
    return nullptr;
}

IndexBuffer::Ptr IndexBuffer::create( uint32_t * indices, uint32_t count )
{
    switch ( Renderer::getAPI() )
    {
        case RendererAPI::API::None: BARD_CORE_ASSERT( false, "RendererAPI::None" ); return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared< OpenGL::IndexBuffer >( indices, count );
    }
    return nullptr;
}

}