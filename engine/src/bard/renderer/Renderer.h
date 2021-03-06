/*
 * \file Renderer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:43
 */

#pragma once

#include <cstdint>
#include "RenderCommand.h"

#include "camera/OrthographicCamera.h"
#include "Shader.h"

namespace bard
{

class Renderer
{
public:
    static void init();

    static void BeginScene( OrthographicCamera & camera );
    static void EndScene();

    static void Submit( const Shader::Ptr & shader, const VertexArray::Ptr & vertexArray,
                        const glm::mat4 & transform = glm::mat4( 1.0f ) );

    static void onWindowResize( uint32_t width, uint32_t height );

    inline static RendererAPI::API getAPI() noexcept { return RendererAPI::getAPI();  }

private:
    struct SceneData
    {
        using Ptr = std::unique_ptr< SceneData >;
        glm::mat4 viewProjectionMatrix;
    };

    static SceneData::Ptr m_sceneData;
};

}
