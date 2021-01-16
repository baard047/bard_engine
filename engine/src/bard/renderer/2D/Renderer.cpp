/*
 * \file Renderer.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 15.01.2021
 * \time : 9:41
 */

#include "Renderer.h"

#include <bard/renderer/Shader.h>
#include <bard/renderer/Texture.h>
#include <bard/renderer/VertexArray.h>
#include <bard/renderer/RenderCommand.h>

#include <glm/gtc/matrix_transform.hpp>

namespace bard
{

namespace {

struct Renderer2DData
{
    //TODO make unique pointers
    VertexArray::Ptr quadVA;
    Shader::Ptr textureShader;
    Texture2D::Ptr whiteTexture;
};

Renderer2DData * s_Data = nullptr;

}

void Renderer2D::init()
{
    if( !s_Data ) { s_Data = new Renderer2DData{}; }

    float squareVertices[5 * 4] =
    {
        -0.5f, -0.5f, 0.f, 0.f, 0.f,       //bottom left
         0.5f, -0.5f, 0.f, 1.f, 0.f,       //bottom right
         0.5f,  0.5f, 0.f, 1.f, 1.f,       //top right
        -0.5f,  0.5f, 0.f, 0.f, 1.f        //top left
    };

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    s_Data->quadVA = VertexArray::create();
    auto squareVB = VertexBuffer::create( squareVertices, sizeof( squareVertices ),
                                                { { ShaderDataType::Float3, "a_Position" },
                                                  { ShaderDataType::Float2, "a_TexCoord" }} );
    s_Data->quadVA->addVertexBuffer( squareVB );
    s_Data->quadVA->setIndexBuffer( IndexBuffer::create( squareIndices, sizeof( squareIndices ) / sizeof( uint32_t ) ) );

    s_Data->whiteTexture = Texture2D::create(1, 1);
    uint32_t white = 0xffffffff;
    s_Data->whiteTexture->setData( &white, sizeof( white ) );

    s_Data->textureShader = Shader::create( "assets/shaders/Texture.glsl" );
    s_Data->textureShader->bind();
    s_Data->textureShader->setInt("u_Texture", 0);
}

void Renderer2D::shutdown()
{
    delete s_Data;
}

void Renderer2D::BeginScene( const OrthographicCamera & camera )
{
    s_Data->textureShader->bind();
    s_Data->textureShader->setMat4( "u_viewProjection", camera.viewProjectionMatrix() );
}

void Renderer2D::EndScene()
{

}

void Renderer2D::DrawQuad( const glm::vec2 & pos, const glm::vec2 & size, const glm::vec4 & color )
{
    DrawQuad( { pos.x, pos.y, 0.f }, size, color );
}

void Renderer2D::DrawQuad( const glm::vec3 & pos, const glm::vec2 & size, const glm::vec4 & color )
{
    s_Data->textureShader->setFloat4( "u_Color", color );
    s_Data->whiteTexture->bind();

    auto transform = glm::translate( glm::mat4{ 1.f }, pos ) /* TODO * rotation */
                     * glm::scale( glm::mat4{ 1.f }, { size.x, size.y, 1.f } );
    s_Data->textureShader->setMat4( "u_Transform", transform );
    s_Data->quadVA->bind();
    RenderCommand::drawIndexed( s_Data->quadVA );
}

void Renderer2D::DrawQuad( const glm::vec2 & pos, const glm::vec2 & size, const Texture2D::Ptr & texture )
{
    DrawQuad( { pos.x, pos.y, 0.f }, size, texture );
}

void Renderer2D::DrawQuad( const glm::vec3 & pos, const glm::vec2 & size, const Texture2D::Ptr & texture )
{
    s_Data->textureShader->setFloat4( "u_Color", glm::vec4( 1.f ) ); //TODO setColor
    texture->bind();

    auto transform = glm::translate( glm::mat4{ 1.f }, pos ) /* TODO * rotation */
                     * glm::scale( glm::mat4{ 1.f }, { size.x, size.y, 1.f } );
    s_Data->textureShader->setMat4( "u_Transform", transform );
    //TODO apply color later

    s_Data->quadVA->bind();
    RenderCommand::drawIndexed( s_Data->quadVA );
}

}