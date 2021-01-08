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

void Renderer::beginScene( OrthographicCamera & camera )
{
    m_sceneData->viewProjectionMatrix = camera.viewProjectionMatrix();
}

void Renderer::endScene()
{

}

void Renderer::submit( const Shader::Ptr & shader, const VertexArray::Ptr & vertexArray )
{
    shader->bind();
    shader->setMat4( "u_viewProjection", m_sceneData->viewProjectionMatrix );

    vertexArray->bind();
    RenderCommand::drawIndexed( vertexArray );
}

Renderer::SceneData::Ptr Renderer::m_sceneData = std::make_unique< Renderer::SceneData >();

}
