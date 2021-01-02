/*
 * \file Application.cpp.cc
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 24.12.2020
 * \time : 22:17
 */

#include "Application.h"

#include <platform/linux/Window.h>

namespace bard {

Application::Application()
        : m_eventBuss( std::make_shared< Events::Manager >() ),
          m_window( Linux::Window::create( { "Bard Engine", 1280, 720 } ) ),
          m_running( true )
{
    m_window->setEventCallback( m_eventBuss );

    //TODO rm
    m_eventBuss->subscribe( this, &Application::onEvent );
    m_eventBuss->unsubscribe< Events::Event >( this );
}

Application::~Application()
{

}

void Application::run()
{
    while( m_running )
    {
        m_window->update();
    }
}

//TODO rm
void Application::onEvent( Events::Event & event )
{
    CORE_LOG_INFO( "wow, event buss working: {0}", event );
}

}