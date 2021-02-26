/*
 * \file Renderer.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 15.01.2021
 * \time : 9:41
 */

#include "Renderer.h"

#include <array>

#include <bard/renderer/Shader.h>
#include <bard/renderer/Texture.h>
#include <bard/renderer/VertexArray.h>
#include <bard/renderer/RenderCommand.h>

#include <glm/gtc/matrix_transform.hpp>

namespace bard
{

namespace {

//per draw call
constexpr const uint32_t MAX_QUADS = 20000;
constexpr const uint32_t MAX_VERTICES = MAX_QUADS * 4;
constexpr const uint32_t MAX_INDICES = MAX_QUADS * 6;
constexpr const uint32_t MAX_TEXTURE_SLOTS = 32;

constexpr size_t QUAD_VERTEX_COUNT = 4;
constexpr glm::vec4 QUAD_VERTEX_POSITIONS[ QUAD_VERTEX_COUNT ] =
{
    { -0.5f, -0.5f, 0.0f, 1.0f },
    {  0.5f, -0.5f, 0.0f, 1.0f },
    {  0.5f,  0.5f, 0.0f, 1.0f },
    { -0.5f,  0.5f, 0.0f, 1.0f }
};

constexpr glm::vec2 TEXTURE_COORDINATES[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

struct QuadVertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;
    float textureIndex;
    float tilingFactor;
};

struct Renderer2DData
{
    VertexArray::Ptr quadVA;
    VertexBuffer::Ptr quadVB;
    Shader::Ptr textureShader;
    Texture2D::Ptr whiteTexture;

    uint32_t quadIndexCount = 0;
    QuadVertex * quadVertexBufferBase = nullptr;
    QuadVertex * quadVertexBufferPtr = nullptr;

    std::array< Texture2D::Ptr, MAX_TEXTURE_SLOTS > textureSlots;
    uint32_t textureSlotIndex = 1; // 0 = white texture

    Renderer2D::Statistics stats;
};

Renderer2DData s_Data;

}

void Renderer2D::init() noexcept
{
    s_Data.quadVA = VertexArray::create();
    s_Data.quadVB = VertexBuffer::create( MAX_VERTICES * sizeof( QuadVertex ) );
    s_Data.quadVB->setLayout( { { ShaderDataType::Float3, "a_Position" },
                                { ShaderDataType::Float4, "a_Color"    },
                                { ShaderDataType::Float2, "a_TexCoord" },
                                { ShaderDataType::Float,  "a_TexIndex" },
                                { ShaderDataType::Float,  "a_TilingFactor" }} );

    s_Data.quadVA->addVertexBuffer( s_Data.quadVB );

    s_Data.quadVertexBufferBase = new QuadVertex[ MAX_VERTICES ];


    auto * quadIndices = new uint32_t[ MAX_INDICES ];
    uint32_t offset = 0;
    for (uint32_t i = 0; i < MAX_INDICES; i += 6)
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
    s_Data.quadVA->setIndexBuffer( IndexBuffer::create( quadIndices, MAX_INDICES ) );
    delete[] quadIndices;

    s_Data.whiteTexture = Texture2D::create(1, 1);
    uint32_t white = 0xffffffff;
    s_Data.whiteTexture->setData( &white, sizeof( white ) );

    int32_t samplers[ MAX_TEXTURE_SLOTS ];
    for( uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++ )
    {
        samplers[ i ] = i;
    }

    s_Data.textureShader = Shader::create( "assets/shaders/Texture.glsl" );
    s_Data.textureShader->bind();
    s_Data.textureShader->setIntArray( "u_Textures", samplers, MAX_TEXTURE_SLOTS );

    s_Data.textureSlots[ 0 ] = s_Data.whiteTexture;  // Set first texture slot to 0
}

void Renderer2D::shutdown() noexcept
{
    delete[] s_Data.quadVertexBufferBase;
}

void Renderer2D::BeginScene( const OrthographicCamera & camera ) noexcept
{
    s_Data.textureShader->bind();
    s_Data.textureShader->setMat4( "u_viewProjection", camera.viewProjectionMatrix() );

    StartBatch();
}

void Renderer2D::EndScene() noexcept
{
    Flush();
}

void Renderer2D::StartBatch() noexcept
{
    s_Data.quadIndexCount = 0;
    s_Data.quadVertexBufferPtr = s_Data.quadVertexBufferBase;

    s_Data.textureSlotIndex = 1;
}

void Renderer2D::NextBatch() noexcept
{
    Flush();
    StartBatch();
}

void Renderer2D::Flush() noexcept
{
    if( s_Data.quadIndexCount == 0 )
    {
        return;
    }

    auto dataSize = ( uint32_t ) ( ( uint8_t * ) s_Data.quadVertexBufferPtr - ( uint8_t * ) s_Data.quadVertexBufferBase );
    s_Data.quadVB->setData( s_Data.quadVertexBufferBase, dataSize );

    for( uint32_t i = 0; i < s_Data.textureSlotIndex; i++ )
    {
        s_Data.textureSlots[ i ]->bind( i );
    }

    RenderCommand::drawIndexed( s_Data.quadVA, s_Data.quadIndexCount );
    s_Data.stats.drawCalls++;
}

void Renderer2D::DrawQuad( const glm::vec2 & pos, const glm::vec2 & size, const glm::vec4 & color ) noexcept
{
    DrawQuad( { pos.x, pos.y, 0.f }, size, color );
}

void Renderer2D::DrawQuad( const glm::vec3 & pos, const glm::vec2 & size, const glm::vec4 & color ) noexcept
{
    glm::mat4 transform = glm::translate( glm::mat4{ 1.f }, pos ) /* TODO * rotation */
                          * glm::scale( glm::mat4{ 1.f }, { size.x, size.y, 1.f } );
    DrawQuad( transform, color );
}

void Renderer2D::DrawQuad( const glm::mat4 & transform, const glm::vec4 & color ) noexcept
{
    static constexpr float whiteTextureIndex = 0.0f;
    static constexpr float tilingFactor = 1.0;

    if (s_Data.quadIndexCount >= MAX_INDICES )
    {
        NextBatch();
    }

    for( size_t i = 0; i < QUAD_VERTEX_COUNT; ++i )
    {
        s_Data.quadVertexBufferPtr->position = transform * QUAD_VERTEX_POSITIONS[ i ];
        s_Data.quadVertexBufferPtr->color = color;
        s_Data.quadVertexBufferPtr->texCoord = TEXTURE_COORDINATES[ i ];
        s_Data.quadVertexBufferPtr->textureIndex = whiteTextureIndex;
        s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
        s_Data.quadVertexBufferPtr++;
    }

    s_Data.quadIndexCount += 6;

    s_Data.stats.quadCount++;
}

void Renderer2D::DrawQuad( const glm::vec2 & pos, const glm::vec2 & size, const Texture2D::Ptr & texture, float tilingFactor ) noexcept
{
    DrawQuad( { pos.x, pos.y, 0.f }, size, texture, tilingFactor );
}

void Renderer2D::DrawQuad( const glm::vec3 & pos, const glm::vec2 & size, const Texture2D::Ptr & texture, float tilingFactor ) noexcept
{
    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    constexpr glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

    if (s_Data.quadIndexCount >= MAX_INDICES )
    {
        NextBatch();
    }

    float textureIndex = 0.0f;
    for ( uint32_t i = 1; i < s_Data.textureSlotIndex; i++ )
    {
        if ( *s_Data.textureSlots[ i ] == *texture )
        {
            textureIndex = static_cast< float >( i );
            break;
        }
    }

    if( textureIndex == 0.0f )
    {
        if (s_Data.quadIndexCount >= MAX_TEXTURE_SLOTS )
        {
            NextBatch();
        }

        textureIndex = static_cast< float >( s_Data.textureSlotIndex );
        s_Data.textureSlots[ s_Data.textureSlotIndex ] = texture;
        s_Data.textureSlotIndex++;
    }

    s_Data.quadVertexBufferPtr->position = pos;
    s_Data.quadVertexBufferPtr->color = color;
    s_Data.quadVertexBufferPtr->texCoord = textureCoords[0];
    s_Data.quadVertexBufferPtr->textureIndex = textureIndex;
    s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    s_Data.quadVertexBufferPtr++;

    s_Data.quadVertexBufferPtr->position = { pos.x + size.x, pos.y, 0.f };
    s_Data.quadVertexBufferPtr->color = color;
    s_Data.quadVertexBufferPtr->texCoord = textureCoords[1];
    s_Data.quadVertexBufferPtr->textureIndex = textureIndex;
    s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    s_Data.quadVertexBufferPtr++;

    s_Data.quadVertexBufferPtr->position = { pos.x + size.x, pos.y + size.y, 0.f };
    s_Data.quadVertexBufferPtr->color = color;
    s_Data.quadVertexBufferPtr->texCoord = textureCoords[2];
    s_Data.quadVertexBufferPtr->textureIndex = textureIndex;
    s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    s_Data.quadVertexBufferPtr++;

    s_Data.quadVertexBufferPtr->position = { pos.x, pos.y + size.y, 0.f };
    s_Data.quadVertexBufferPtr->color = color;
    s_Data.quadVertexBufferPtr->texCoord = textureCoords[3];
    s_Data.quadVertexBufferPtr->textureIndex = textureIndex;
    s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    s_Data.quadVertexBufferPtr++;

    s_Data.quadIndexCount += 6;

    s_Data.stats.quadCount++;

/*    s_Data.textureShader->setFloat4( "u_Color", glm::vec4( 1.f ) ); //TODO setColor
    texture->bind();

    auto transform = glm::translate( glm::mat4{ 1.f }, pos ) *//* TODO * rotation *//*
                     * glm::scale( glm::mat4{ 1.f }, { size.x, size.y, 1.f } );
    s_Data.textureShader->setMat4( "u_Transform", transform );
    //TODO apply color later

    s_Data.quadVA->bind();
    RenderCommand::drawIndexed( s_Data.quadVA );*/
}

void Renderer2D::DrawQuad( const glm::mat4 & transform, const Texture2D::Ptr & texture, float tilingFactor ) noexcept
{
    //TODO
}

void Renderer2D::resetStats()
{
    std::memset( &s_Data.stats, 0, sizeof( Statistics ) );
}

Renderer2D::Statistics Renderer2D::getStats()
{
    return s_Data.stats;
}

}