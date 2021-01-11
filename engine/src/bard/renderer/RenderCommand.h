/*
 * \file RenderCommand.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 08.01.2021
 * \time : 12:37
 */

#pragma once

#include "RendererAPI.h"

namespace bard
{

class RenderCommand
{
public:
    inline static void init()
    {
        s_rendererAPI->init();
    }

    inline static void drawIndexed( const VertexArray::Ptr & vertexArray )
    {
        s_rendererAPI->drawIndexed( vertexArray );
    }

    inline static void setClearColor(const glm::vec4& color)
    {
        s_rendererAPI->setClearColor( color );
    }

    inline static void clear()
    {
        s_rendererAPI->clear();
    }

private:
    static std::unique_ptr< RendererAPI > s_rendererAPI;
};

}