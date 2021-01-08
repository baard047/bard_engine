/*
 * \file RendererAPI.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 08.01.2021
 * \time : 12:51
 */

#pragma once

#include <bard/renderer/RendererAPI.h>

namespace bard::OpenGL
{

class RendererAPI : public Base::RendererAPI
{
public:
    void setClearColor( const glm::vec4 & color ) override;
    void clear() override;
    void drawIndexed( const VertexArray::Ptr & vertexArray ) override;
};

}
