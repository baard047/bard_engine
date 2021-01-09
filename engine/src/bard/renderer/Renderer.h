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
    static void beginScene( OrthographicCamera & camera );
    static void endScene();

    static void submit( const Shader::Ptr & shader, const VertexArray::Ptr & vertexArray,
                        const glm::mat4 & transform = glm::mat4(1.0f) );

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
