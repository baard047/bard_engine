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
}

void Application::run()
{
    while( m_running )
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

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