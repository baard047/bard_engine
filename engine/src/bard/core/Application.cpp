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
#include <bard/core/utils/Timestep.h>
#include <bard/events/Buss.h>

namespace bard {

Application::Application()
        : m_window( Linux::Window::create( { "Bard Engine", 1280, 720 } ) ),
          m_ImGuiLayer( new ImGuiLayer{} ),
          m_running( true )
{
    BARD_CORE_ASSERT( !m_instance, "Application already exist" );
    m_instance = this;
    Renderer::init();

    pushOverlay( m_ImGuiLayer );

    Events::Buss::get().subscribe( this, &Application::onWindowCloseEvent );
}

void Application::run()
{
    while( m_running )
    {
        auto time = static_cast< float >( glfwGetTime() );
        Timestep timestep { time - m_lastFrameTime };
        m_lastFrameTime = time;

        for( auto layer : m_layerStack )
        {
            layer->onUpdate( timestep );
        }

        for( auto layer : m_layerStack )
        {
            layer->onRender();
        }

        m_ImGuiLayer->begin();
        for( auto layer : m_layerStack ) { layer->onImGuiRender(); }
        m_ImGuiLayer->end();

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

bool Application::onWindowCloseEvent( Events::WindowClose & )
{
    m_running = false;
    return true;
}

Application * Application::m_instance = nullptr;

}