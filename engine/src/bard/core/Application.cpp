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

    glGenBuffers( 1, &m_vertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );

    float vertices[ 3 * 3 ] =
    {
        -0.5f, -0.5f, 0.f,
        0.5f, -0.5f, 0.f,
        0.f, 0.5f, 0.f
    };

    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers( 1, &m_indexBuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer );

    uint32_t  indices[3] = { 0, 1 , 2 };
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );
    ///////
}

void Application::run()
{
    while( m_running )
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        ///////
        glBindVertexArray( m_vertexArray );
        glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );
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