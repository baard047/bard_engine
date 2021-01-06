/*
 * \file Buffer.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:18
 */

#include "Buffer.h"

#include <bard/core/Base.h>
#include "Renderer.h"

#include <platform/openGL/OpenGlBuffer.h>

namespace bard
{

VertexBuffer * VertexBuffer::create( float * vertices, uint32_t size )
{
    switch ( Renderer::API )
    {
        case RendererAPI::None: BARD_CORE_ASSERT(false, "RendererAPI::None"); return nullptr;
        case RendererAPI::OpenGL: return new OpenGLVertexBuffer( vertices, size );
    }
    return nullptr;
}

IndexBuffer * IndexBuffer::create( uint32_t * indices, uint32_t count )
{
    switch ( Renderer::API )
    {
        case RendererAPI::None: BARD_CORE_ASSERT(false, "RendererAPI::None"); return nullptr;
        case RendererAPI::OpenGL: return new OpenGLIndexBuffer( indices, count );
    }
    return nullptr;
}
}