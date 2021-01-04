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

namespace bard {

Application::Application()
        : m_eventBuss( std::make_shared< Events::Manager >() ),
          m_window( Linux::Window::create( { "Bard Engine", 1280, 720 } ) ),
          m_running( true )
{
    BARD_CORE_ASSERT( !m_instance, "Do a proper singleton, lazy dumbass" );
    m_instance = this;
    m_window->setEventCallback( m_eventBuss );
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
            layer->update();
        }
        m_window->update();
    }
}

void Application::pushLayer( Layer * layer )
{
    layer->setEventBuss( m_eventBuss );
    m_layerStack.pushLayer( layer );
    layer->attach();
}

void Application::pushOverlay( Layer * overlay )
{
    overlay->setEventBuss( m_eventBuss );
    m_layerStack.pushOverlay( overlay );
    overlay->attach();
}

bool Application::onWindowCloseEvent( Events::WindowClose & event )
{
    m_running = false;
    return true;
}

//TODO rm
Application * Application::m_instance = nullptr;

}