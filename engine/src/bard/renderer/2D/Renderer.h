/*
 * \file Renderer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 15.01.2021
 * \time : 9:41
 */

#pragma once

#include <bard/renderer/Renderer.h>
#include <bard/renderer/camera/OrthographicCamera.h>
#include <bard/renderer/Texture.h>

namespace bard
{

class Renderer2D
{
public:
    static void init() noexcept;
    static void shutdown() noexcept;

    static void BeginScene( const OrthographicCamera & camera ) noexcept;
    static void EndScene() noexcept;

    static void DrawQuad( const glm::vec2 & pos, const glm::vec2 & size, const glm::vec4 & color ) noexcept;
    static void DrawQuad( const glm::vec3 & pos, const glm::vec2 & size, const glm::vec4 & color ) noexcept;
    static void DrawQuad( const glm::mat4 & transform, const glm::vec4& color ) noexcept;

    static void DrawQuad( const glm::vec2 & pos, const glm::vec2 & size, const Texture2D::Ptr & texture, float tilingFactor = 1.0 ) noexcept;
    static void DrawQuad( const glm::vec3 & pos, const glm::vec2 & size, const Texture2D::Ptr & texture, float tilingFactor = 1.0 ) noexcept;
    static void DrawQuad( const glm::mat4 & transform, const Texture2D::Ptr & texture, float tilingFactor = 1.0 ) noexcept;

    struct Statistics
    {
        uint32_t drawCalls = 0;
        uint32_t quadCount = 0;

        uint32_t getTotalVertexCount() const { return quadCount * 4; }
        uint32_t getTotalIndexCount() const { return quadCount * 6; }
    };

    static void resetStats();
    static Statistics getStats();

private:
    static void StartBatch() noexcept;
    static void NextBatch() noexcept;
    static void Flush() noexcept;

public:
    Renderer2D() = delete;

};

}

