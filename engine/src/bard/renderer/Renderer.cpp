/*
 * \file Renderer.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:43
 */

#include "Renderer.h"

namespace bard
{

void Renderer::beginScene()
{

}

void Renderer::endScene()
{

}

void Renderer::submit( const VertexArray::Ptr & vertexArray )
{
    vertexArray->bind();
    RenderCommand::drawIndexed( vertexArray );
}

}
