/*
 * \file VertexArray.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 07.01.2021
 * \time : 21:48
 */

#include "VertexArray.h"
#include "bard/renderer/Renderer.h"

#include <platform/openGL/VertexArray.h>

namespace bard::Base
{

VertexArray::Ptr VertexArray::create()
{
    switch ( Renderer::getAPI() )
    {
        case RendererAPI::API::None: BARD_CORE_ASSERT( false, "RendererAPI::None" ); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared< OpenGL::VertexArray>();
    }
    return nullptr;
}

}