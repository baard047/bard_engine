/*
 * \file Sandbox.cpp
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 20.12.2020
 * \time : 15:27
 */

#include <Engine.h>

#include <imgui.h>

class ExampleLayer : public bard::Layer
{
public:
    ExampleLayer()
            : bard::Layer( "Example Layer" )
    {
        using namespace bard;

        float vertices[ 3 * 7 ] =
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
        m_triangleVA->setIndexBuffer( IndexBuffer::create( indices, sizeof(indices) / sizeof(uint32_t)) );

        ///
        float squareVertices[3 * 4] =
                {
                        -0.65f, -0.65f, 0.f,
                        0.65f, -0.65f, 0.f,
                        0.65f, 0.65f, 0.f,
                        -0.65f, 0.65f, 0.f
                };

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        m_squareVA = VertexArray::create();
        auto squareVB = VertexBuffer::create( squareVertices, sizeof( squareVertices ),
                                              { { ShaderDataType::Float3, "a_Position" } } );
        m_squareVA->addVertexBuffer( squareVB );
        m_squareVA->setIndexBuffer( IndexBuffer::create( squareIndices, sizeof(squareIndices) / sizeof(uint32_t)) );

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = v_Color;
            }
        )";

        m_triangleShader = std::make_shared< Shader >( vertexSrc, fragmentSrc );

        std::string vertexSrc2 = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc2 = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(0.4, 0.8, 0.8, 1.0);
            }
        )";

        m_squareShader = std::make_shared< Shader >( vertexSrc2, fragmentSrc2 );
    }

    void onImGuiRender() override
    {
        ImGui::Begin(m_debugName.c_str());
        ImGui::Text("Smth going on in actual application");
        ImGui::End();
    }

    void onRender() override
    {
        bard::RenderCommand::setClearColor( { 0.1f, 0.1f, 0.1f, 1 } );
        bard::RenderCommand::clear();

        bard::Renderer::beginScene();

        m_squareShader->bind();
        bard::Renderer::submit( m_squareVA );

        m_triangleShader->bind();
        bard::Renderer::submit( m_triangleVA );

        bard::Renderer::endScene();;
    }

private:
    bard::Shader::Ptr m_triangleShader;
    bard::VertexArray::Ptr m_triangleVA;

    bard::Shader::Ptr m_squareShader;
    bard::VertexArray::Ptr m_squareVA;
};

class Sandbox final : public bard::Application
{
public:
    Sandbox()
    {
        pushLayer( new ExampleLayer{} );
//        pushOverlay( new bard::ImGuiLayer{} );
        LOG_INFO( "Hello from application" );
    }
};

bard::Application * bard::createApplication()
{
    return new Sandbox{};
}
