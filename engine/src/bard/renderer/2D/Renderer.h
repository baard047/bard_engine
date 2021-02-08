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
    static void init();
    static void shutdown();

    static void BeginScene( const OrthographicCamera & camera );
    static void EndScene();

    static void Flush();

    static void DrawQuad( const glm::vec2 & pos, const glm::vec2 & size, const glm::vec4 & color );
    static void DrawQuad( const glm::vec3 & pos, const glm::vec2 & size, const glm::vec4 & color );

    static void DrawQuad( const glm::vec2 & pos, const glm::vec2 & size, const Texture2D::Ptr & texture, float tilingFactor = 1.0 );
    static void DrawQuad( const glm::vec3 & pos, const glm::vec2 & size, const Texture2D::Ptr & texture, float tilingFactor = 1.0 );

public:
    Renderer2D() = delete;

};

}

