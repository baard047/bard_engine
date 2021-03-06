/*
 * \file RendererAPI.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 08.01.2021
 * \time : 12:30
 */

#pragma once

#include <glm/vec4.hpp>
#include "VertexArray.h"

namespace bard
{

class RendererAPI
{
public:
    enum class API : uint_least8_t
    {
        None = 0, OpenGL
    };

public:
    ~RendererAPI() = default;

    virtual void init() = 0;
    virtual void setViewPort( uint32_t x, uint32_t y, uint32_t width, uint32_t height ) = 0;

    inline static API getAPI() noexcept { return s_API; }

    virtual void setClearColor( const glm::vec4 & color ) = 0;
    virtual void clear() = 0;

    virtual void drawIndexed( const VertexArray::Ptr & vertexArray, uint32_t indexCount = 0 ) = 0;

private:
    static API s_API;
};

}
