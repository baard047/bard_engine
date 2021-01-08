/*
 * \file Application.cpp.cc
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 24.12.2020
 * \time : 22:17
 */

#include "Application.h"

#include <platform/linux/Window.h>
#include <bard/renderer/Renderer.h>

namespace bard {

Application::Application()
        : m_eventBuss( std::make_shared< Events::Manager >() ),
          m_window( Linux::Window::create( { "Bard Engine", 1280, 720 } ) ),
          m_ImGuiLayer( new ImGuiLayer{} ),
          m_running( true )
{
    //TODO temp, proper singleton
    BARD_CORE_ASSERT( !m_instance, "Application already exist" );
    m_instance = this;
    m_window->setEventCallback( m_eventBuss );

    pushOverlay( m_ImGuiLayer );

    m_eventBuss->subscribe( this, &Application::onWindowCloseEvent );

    ///////
    float vertices[ 3 * 7 ] =
    {
        -0.5f, -0.5f, 0.f, 0.8f, 0.2f, 0.8f, 1.f,
        0.5f, -0.5f, 0.f, 0.2f, 0.3f, 0.8f, 1.f,
        0.f, 0.5f, 0.f, 0.8f, 0.8f, 0.2f, 1.f,
    };

    m_vertexArray = VertexArray::create();
    auto vertexBuffer = VertexBuffer::create( vertices, sizeof( vertices ) );
    vertexBuffer->setLayout( { { ShaderDataType::Float3, "a_Position" },
                               { ShaderDataType::Float4, "a_Color" } } );

    uint32_t indices[3] = { 0, 1, 2 };
    m_vertexArray->addVertexBuffer( vertexBuffer );
    m_vertexArray->setIndexBuffer( IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)) );

    ////////

    float squareVertices[3 * 4] =
    {
        -0.65f, -0.65f, 0.f,
        0.65f, -0.65f, 0.f,
        0.65f, 0.65f, 0.f,
        -0.65f, 0.65f, 0.f
    };

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    m_squareVertexArray = VertexArray::create();
    auto squareVB = VertexBuffer::create( squareVertices, sizeof( squareVertices ),
                                          { { ShaderDataType::Float3, "a_Position" } } );
    m_squareVertexArray->addVertexBuffer( squareVB );
    m_squareVertexArray->setIndexBuffer( IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)) );

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

    m_shader = std::make_shared< Shader >( vertexSrc, fragmentSrc );

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

    m_shader2 = std::make_shared< Shader >( vertexSrc2, fragmentSrc2 );
    ///////
}

void Application::run()
{
    while( m_running )
    {
        RenderCommand::setClearColor( { 0.1f, 0.1f, 0.1f, 1 } );
        RenderCommand::clear();

        Renderer::beginScene();

        m_shader2->bind();
        Renderer::submit( m_squareVertexArray );

        m_shader->bind();
        Renderer::submit( m_vertexArray );

        Renderer::endScene();;

        for( auto layer : m_layerStack )
        {
            layer->onUpdate();
        }

        m_ImGuiLayer->begin();
        for( auto layer : m_layerStack ) { layer->onImGuiRender(); }
        m_ImGuiLayer->end();

        m_window->update();
    }
}

void Application::pushLayer( Layer * layer )
{
    layer->setEventBuss( m_eventBuss );
    m_layerStack.pushLayer( layer );
    layer->onAttach();
}

void Application::pushOverlay( Layer * overlay )
{
    overlay->setEventBuss( m_eventBuss );
    m_layerStack.pushOverlay( overlay );
    overlay->onAttach();
}

bool Application::onWindowCloseEvent( Events::WindowClose & )
{
    m_running = false;
    return true;
}

Application * Application::m_instance = nullptr;

}