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

    inline static void drawIndexed( const VertexArray::Ptr & vertexArray, uint32_t count = 0 )
    {
        s_rendererAPI->drawIndexed( vertexArray, count );
    }

    inline static void setClearColor(const glm::vec4& color)
    {
        s_rendererAPI->setClearColor( color );
    }

    inline static void setViewPort( uint32_t x, uint32_t y, uint32_t width, uint32_t height )
    {
        s_rendererAPI->setViewPort( x, y, width, height );
    }

    inline static void clear()
    {
        s_rendererAPI->clear();
    }

private:
    static std::unique_ptr< RendererAPI > s_rendererAPI;
};

}