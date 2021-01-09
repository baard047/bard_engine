/*
 * \file RendererAPI.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 08.01.2021
 * \time : 12:51
 */

#include "RendererAPI.h"

#include <glad/glad.h>

namespace OpenGL
{

void RendererAPI::setClearColor( const glm::vec4 & color )
{
    glClearColor( color.r, color.g, color.b, color.a );
}

void RendererAPI::clear()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void RendererAPI::drawIndexed( const bard::VertexArray::Ptr & vertexArray )
{
    glDrawElements( GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr );
}

}