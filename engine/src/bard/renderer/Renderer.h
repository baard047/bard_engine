/*
 * \file Renderer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:43
 */

#pragma once

#include <cstdint>
#include "RenderCommand.h"

namespace bard
{

class Renderer
{
public:
    static void beginScene();
    static void endScene();

    static void submit( const VertexArray::Ptr & vertexArray );

    inline static RendererAPI::API getAPI() noexcept { return RendererAPI::getAPI();  }
};

}
