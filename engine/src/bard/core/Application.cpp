/*
 * \file Application.cpp.cc
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 24.12.2020
 * \time : 22:17
 */

#include "Application.h"

#include <platform/linux/Window.h>

#include <glad/glad.h> //TODO temp

#include <bard/core/Input.h>

namespace bard {

namespace {

GLenum convert( ShaderDataType type )
{
    switch ( type )
    {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:      return GL_FLOAT;
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:      return GL_INT;
        case ShaderDataType::Bool:      return GL_BOOL;
        case ShaderDataType::None:      break;
    }

    BARD_CORE_ASSERT( false, "Unknown shared type!" );
    return 0;
}

}

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
    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray( m_vertexArray );

    float vertices[ 3 * 7 ] =
    {
        -0.5f, -0.5f, 0.f, 0.8f, 0.2f, 0.8f, 1.f,
        0.5f, -0.5f, 0.f, 0.2f, 0.3f, 0.8f, 1.f,
        0.f, 0.5f, 0.f, 0.8f, 0.8f, 0.2f, 1.f,
    };

    m_vertexBuffer.reset( VertexBuffer::create( vertices, sizeof( vertices ) ) );
    m_vertexBuffer->setLayout( { { ShaderDataType::Float3, "a_Position" },
                                 { ShaderDataType::Float4, "a_Color" } } );

    const auto & layout = m_vertexBuffer->layout();
    for( size_t index = 0; index < layout.size(); ++index )
    {
        const auto & elem = layout[index];
        glEnableVertexAttribArray( index);
        glVertexAttribPointer( index, elem.getComponentCount(), convert( elem.type ),
                               elem.normalized ? GL_TRUE : GL_FALSE,
                               layout.getStride(), ( const void * ) elem.offset );
    }

    uint32_t indices[3] = { 0, 1, 2 };
    m_indexBuffer.reset( IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)) );

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

    m_shader = std::make_unique< Shader >( vertexSrc, fragmentSrc );
    ///////
}

void Application::run()
{
    while( m_running )
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        ///////
        m_shader->bind();
        glBindVertexArray( m_vertexArray );
        glDrawElements( GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr );
        ///////

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