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

struct QuadVertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;
//    float texIndex;
//    float tilingFactor;
};

struct Renderer2DData
{
    //per draw call
    static constexpr const uint32_t MAX_QUADS = 20000;
    static constexpr const uint32_t MAX_VERTICES = MAX_QUADS * 4;
    static constexpr const uint32_t MAX_INDICES = MAX_QUADS * 6;

    VertexArray::Ptr quadVA;
    VertexBuffer::Ptr quadVB;
    Shader::Ptr textureShader;
    Texture2D::Ptr whiteTexture;

    uint32_t quadIndexCount = 0;
    QuadVertex * quadVertexBufferBase = nullptr;
    QuadVertex * quadVertexBufferPtr = nullptr;
};

Renderer2DData s_Data;

}

void Renderer2D::init()
{
    s_Data.quadVA = VertexArray::create();
    s_Data.quadVB = VertexBuffer::create( Renderer2DData::MAX_VERTICES * sizeof( QuadVertex ) );
    s_Data.quadVB->setLayout( { { ShaderDataType::Float3, "a_Position" },
                                { ShaderDataType::Float4, "a_Color" },
                                { ShaderDataType::Float2, "a_TexCoord" } } );

    s_Data.quadVA->addVertexBuffer( s_Data.quadVB );

    s_Data.quadVertexBufferBase = new QuadVertex[Renderer2DData::MAX_VERTICES ];


    auto * quadIndices = new uint32_t[ Renderer2DData::MAX_INDICES ];
    uint32_t offset = 0;
    for (uint32_t i = 0; i < Renderer2DData::MAX_INDICES; i += 6)
    {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;

        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += 4;
    }
    //TODO maybe change to shared_ptr later. Its right away send in GPU for now
    s_Data.quadVA->setIndexBuffer( IndexBuffer::create( quadIndices, Renderer2DData::MAX_INDICES ) );
    delete[] quadIndices;

    s_Data.whiteTexture = Texture2D::create(1, 1);
    uint32_t white = 0xffffffff;
    s_Data.whiteTexture->setData( &white, sizeof( white ) );

    s_Data.textureShader = Shader::create( "assets/shaders/Texture.glsl" );
    s_Data.textureShader->bind();
    s_Data.textureShader->setInt("u_Texture", 0);
}

void Renderer2D::shutdown()
{
    delete[] s_Data.quadVertexBufferBase;
}

void Renderer2D::BeginScene( const OrthographicCamera & camera )
{
    s_Data.textureShader->bind();
    s_Data.textureShader->setMat4( "u_viewProjection", camera.viewProjectionMatrix() );

    s_Data.quadVertexBufferPtr = s_Data.quadVertexBufferBase;
    s_Data.quadIndexCount = 0;
}

void Renderer2D::EndScene()
{
    auto dataSize = ( uint32_t ) ( ( uint8_t * ) s_Data.quadVertexBufferPtr - ( uint8_t * ) s_Data.quadVertexBufferBase );
    s_Data.quadVB->setData( s_Data.quadVertexBufferBase, dataSize );

    Flush();
}

void Renderer2D::Flush()
{
    RenderCommand::drawIndexed( s_Data.quadVA, s_Data.quadIndexCount );
}

void Renderer2D::DrawQuad( const glm::vec2 & pos, const glm::vec2 & size, const glm::vec4 & color )
{
    DrawQuad( { pos.x, pos.y, 0.f }, size, color );
}

void Renderer2D::DrawQuad( const glm::vec3 & pos, const glm::vec2 & size, const glm::vec4 & color )
{
    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

    s_Data.quadVertexBufferPtr->position = pos;
    s_Data.quadVertexBufferPtr->color = color;
    s_Data.quadVertexBufferPtr->texCoord = textureCoords[0];
    s_Data.quadVertexBufferPtr++;

    s_Data.quadVertexBufferPtr->position = { pos.x + size.x, pos.y, 0.f };
    s_Data.quadVertexBufferPtr->color = color;
    s_Data.quadVertexBufferPtr->texCoord = textureCoords[1];
    s_Data.quadVertexBufferPtr++;

    s_Data.quadVertexBufferPtr->position = { pos.x + size.x, pos.y + size.y, 0.f };
    s_Data.quadVertexBufferPtr->color = color;
    s_Data.quadVertexBufferPtr->texCoord = textureCoords[2];
    s_Data.quadVertexBufferPtr++;

    s_Data.quadVertexBufferPtr->position = { pos.x, pos.y + size.y, 0.f };
    s_Data.quadVertexBufferPtr->color = color;
    s_Data.quadVertexBufferPtr->texCoord = textureCoords[3];
    s_Data.quadVertexBufferPtr++;

    s_Data.quadIndexCount += 6;

//    s_Data.whiteTexture->bind();

/*    auto transform = glm::translate( glm::mat4{ 1.f }, pos ) *//* TODO * rotation *//*
                     * glm::scale( glm::mat4{ 1.f }, { size.x, size.y, 1.f } );
    s_Data.textureShader->setMat4( "u_Transform", transform );
    s_Data.quadVA->bind();
    RenderCommand::drawIndexed( s_Data.quadVA );*/
}

void Renderer2D::DrawQuad( const glm::vec2 & pos, const glm::vec2 & size, const Texture2D::Ptr & texture )
{
    DrawQuad( { pos.x, pos.y, 0.f }, size, texture );
}

void Renderer2D::DrawQuad( const glm::vec3 & pos, const glm::vec2 & size, const Texture2D::Ptr & texture )
{
    s_Data.textureShader->setFloat4( "u_Color", glm::vec4( 1.f ) ); //TODO setColor
    texture->bind();

    auto transform = glm::translate( glm::mat4{ 1.f }, pos ) /* TODO * rotation */
                     * glm::scale( glm::mat4{ 1.f }, { size.x, size.y, 1.f } );
    s_Data.textureShader->setMat4( "u_Transform", transform );
    //TODO apply color later

    s_Data.quadVA->bind();
    RenderCommand::drawIndexed( s_Data.quadVA );
}

}