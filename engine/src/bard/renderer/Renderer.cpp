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

void Renderer::init()
{
    RenderCommand::init();
}

void Renderer::beginScene( OrthographicCamera & camera )
{
    m_sceneData->viewProjectionMatrix = camera.viewProjectionMatrix();
}

void Renderer::endScene()
{

}

void Renderer::submit( const Shader::Ptr & shader, const VertexArray::Ptr & vertexArray,
                       const glm::mat4 & transform )
{
    shader->bind();
    shader->setMat4( "u_viewProjection", m_sceneData->viewProjectionMatrix );
    shader->setMat4( "u_Transform", transform );

    vertexArray->bind();
    RenderCommand::drawIndexed( vertexArray );
}

Renderer::SceneData::Ptr Renderer::m_sceneData = std::make_unique< Renderer::SceneData >();

}
