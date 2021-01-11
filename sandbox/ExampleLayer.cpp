/*
 * \file ExampleLayer.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 09.01.2021
 * \time : 18:05
 */

#include "ExampleLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
        : bard::Layer( "Example Layer" ),
          m_cameraController( 1280.f / 720.f, true )
{
    using namespace bard;

    float vertices[3 * 7] =
    {
        -0.5f, -0.5f, 0.f, 0.8f, 0.2f, 0.8f, 1.f,
        0.5f, -0.5f, 0.f, 0.2f, 0.3f, 0.8f, 1.f,
        0.f, 0.5f, 0.f, 0.8f, 0.8f, 0.2f, 1.f,
    };

    m_triangleVA = VertexArray::create();
    auto vertexBuffer = VertexBuffer::create( vertices, sizeof( vertices ) );
    vertexBuffer->setLayout( { { ShaderDataType::Float3, "a_Position" },
                               { ShaderDataType::Float4, "a_Color" } } );

    uint32_t indices[3] = { 0, 1, 2 };
    m_triangleVA->addVertexBuffer( vertexBuffer );
    m_triangleVA->setIndexBuffer( IndexBuffer::create( indices, sizeof( indices ) / sizeof( uint32_t ) ) );

    ///
    float squareVertices[5 * 4] =
    {
        -0.5f, -0.5f, 0.f, 0.f, 0.f, //bottom left
         0.5f, -0.5f, 0.f, 1.f, 0.f, //bottom right
         0.5f,  0.5f, 0.f, 1.f, 1.f, //top right
        -0.5f,  0.5f, 0.f, 0.f, 1.f  //top left
    };

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    m_squareVA = VertexArray::create();
    auto squareVB = VertexBuffer::create( squareVertices, sizeof( squareVertices ),
                                          { { ShaderDataType::Float3, "a_Position" },
                                            { ShaderDataType::Float2, "a_TexCoord" } } );
    m_squareVA->addVertexBuffer( squareVB );
    m_squareVA->setIndexBuffer( IndexBuffer::create( squareIndices, sizeof( squareIndices ) / sizeof( uint32_t ) ) );

    std::string triangleVertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_viewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;
        out vec4 v_Color;

        void main()
        {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = u_viewProjection * u_Transform * vec4(a_Position, 1.0);
        }
    )";

    std::string triangleFragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;
        in vec4 v_Color;

        void main()
        {
            color = v_Color;
        }
    )";

    m_triangleShader = Shader::create("Triangle Shader", triangleVertexSrc, triangleFragmentSrc );

    std::string rectangleVertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_viewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            gl_Position = u_viewProjection * u_Transform * vec4(a_Position, 1.0);
        }
    )";

    std::string rectangleFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
    )";

    m_squareShader = Shader::create( "Flat color shader", rectangleVertexSrc, rectangleFragmentSrc );

///////////

    std::string textureVertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec2 a_TexCoord;

        uniform mat4 u_viewProjection;
        uniform mat4 u_Transform;

        out vec2 v_TexCoord;

        void main()
        {
            v_TexCoord = a_TexCoord;
            gl_Position = u_viewProjection * u_Transform * vec4(a_Position, 1.0);
        }
    )";

    std::string textureFragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec2 v_TexCoord;

        uniform sampler2D u_Texture;

        void main()
        {
        	color = texture(u_Texture, v_TexCoord);
        }
    )";

    m_textureShader = Shader::create( "Texture shader", textureVertexSrc, textureFragmentSrc );

    m_checkerboardTexture = bard::Texture2D::create( "assets/textures/Checkerboard.png");
    m_shipTexture = bard::Texture2D::create( "assets/textures/ship.png");

    m_textureShader->bind();
    m_textureShader->setInt( "u_Texture", 0 );
}

void ExampleLayer::onRender()
{
    bard::RenderCommand::setClearColor( { 0.1f, 0.1f, 0.1f, 1 } );
    bard::RenderCommand::clear();

    bard::Renderer::beginScene( m_cameraController.getCamera() );

    m_squareShader->bind();
    m_squareShader->setFloat3( "u_Color", m_squaresColor );

    constexpr static float padding = 0.11f;
    glm::mat4 scale = glm::scale( glm::mat4(1.0f), glm::vec3(0.1f) );
    for( int y = 0; y < 20; ++y )
    {
        for( int x = 0; x < 20; ++x )
        {
            glm::vec3 pos( (float)x * padding, (float)y * padding, 0.0f );
            glm::mat4 transform = glm::translate( glm::mat4(1.f), pos ) * scale;
            bard::Renderer::submit( m_squareShader, m_squareVA, transform );
        }
    }

    //Checkerboard
    m_checkerboardTexture->bind();
    bard::Renderer::submit( m_textureShader, m_squareVA,  glm::scale( glm::mat4(1.0f), glm::vec3(2.f) ) );

    //ship
    m_shipTexture->bind();
    glm::mat4 shipTransform{ glm::translate( glm::mat4( 1.f ), m_shipPos )
                             * glm::scale( glm::mat4( 1.0f ), glm::vec3( 0.7f ) ) };
    bard::Renderer::submit( m_textureShader, m_squareVA, shipTransform );

    //Triangle
    glm::mat4 transform = glm::translate( glm::mat4(1.f), m_trianglePos );
    bard::Renderer::submit( m_triangleShader, m_triangleVA, transform );

    bard::Renderer::endScene();
}

void ExampleLayer::onImGuiRender()
{
    constexpr static auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_DockNodeHost | ImGuiWindowFlags_NoMove;

    ImGui::Begin( m_debugName.c_str(), nullptr, flags );

    ImGui::Text("Triangle Position");
    ImGui::SliderFloat( "x", &m_trianglePos.x, -5.0f, 5.0f);
    ImGui::SliderFloat( "y", &m_trianglePos.y, -5.0f, 5.0f);
    ImGui::Spacing(); ImGui::Spacing();

    ImGui::Text("Ship position");
    ImGui::SliderFloat( "x pos", &m_shipPos.x, -10.0f, 10.0f);
    ImGui::SliderFloat( "y pos", &m_shipPos.y, -10.0f, 10.0f);
    ImGui::Spacing(); ImGui::Spacing();

    ImGui::ColorEdit3( "Squares Color", glm::value_ptr( m_squaresColor ) );

    ImGui::End();
}

void ExampleLayer::onUpdate( bard::Timestep ts )
{
    m_cameraController.onUpdate( ts );
}
