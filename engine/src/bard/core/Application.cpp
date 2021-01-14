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
#include <bard/core/Timestep.h>
#include <bard/events/Buss.h>

namespace bard {

Application::Application()
        : m_window( Linux::Window::create( { "Bard Engine", 1280, 720 } ) ),
          m_ImGuiLayer( new ImGuiLayer{} )
{
    BARD_CORE_ASSERT( !m_instance, "Application already exist" );
    m_instance = this;
    Renderer::init();

    pushOverlay( m_ImGuiLayer );

    Events::Buss::get().subscribe( this, &Application::onWindowClose );
    Events::Buss::get().subscribe( this, &Application::onWindowResize );
}

void Application::run()
{
    while( m_running )
    {
        auto time = static_cast< float >( glfwGetTime() );
        Timestep timestep { time - m_lastFrameTime };
        m_lastFrameTime = time;

        if( !m_minimized )
        {
            for( auto layer : m_layerStack )
            {
                layer->onUpdate( timestep );
            }

            for( auto layer : m_layerStack )
            {
                layer->onRender();
            }

            //NOTE: move outside if statement with multipleViewports enabled
            m_ImGuiLayer->begin();
            for( auto layer : m_layerStack ) { layer->onImGuiRender(); }
            m_ImGuiLayer->end();
        }

        m_window->update();
    }
}

void Application::pushLayer( Layer * layer )
{
    m_layerStack.pushLayer( layer );
    layer->onAttach();
}

void Application::pushOverlay( Layer * overlay )
{
    m_layerStack.pushOverlay( overlay );
    overlay->onAttach();
}

bool Application::onWindowClose( Events::WindowClose & )
{
    m_running = false;
    return true;
}

bool Application::onWindowResize( Events::WindowResize & event )
{
    if( event.width == 0 || event.height == 0 )
    {
        m_minimized = true;
        return true;
    }

    Renderer::onWindowResize( event.width, event.height );
    m_minimized = false;
    return false;
}

Application * Application::m_instance = nullptr;

}