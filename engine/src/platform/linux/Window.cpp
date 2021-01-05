/*
 * \file Window.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 02.01.2021
 * \time : 15:09
 */

#include "Window.h"

#include <bard/events/ApplicationEvent.h>
#include <bard/events/KeyEvent.h>
#include <bard/events/MouseEvent.h>

#include <platform/openGL/OpenGlContext.h>

namespace bard::Linux {

namespace {
void GLFWErrorCallback( int error, const char * description )
{
    CORE_LOG_ERROR( "GLFW error ({0}): {1}", error, description );
}

bool s_GLFWinitialized = false;
}

Window::Window( const WindowInterface::Properties & props )
{
    m_data.title = props.title;
    m_data.width = props.width;
    m_data.height = props.height;

    CORE_LOG_INFO( "Creating window {0} ({1}, {2})", props.title, props.width, props.height );

    if( !s_GLFWinitialized )
    {
        int success = glfwInit();
        BARD_CORE_ASSERT( success, "Could not initialize GLFW!" );

        glfwSetErrorCallback( GLFWErrorCallback );

        s_GLFWinitialized = true;
    }

    m_window = glfwCreateWindow( ( int ) props.width, ( int ) props.height, props.title.c_str(), nullptr, nullptr );

    m_context = std::make_unique< OpenGlContext >( m_window );
    m_context->init();

    glfwSetWindowUserPointer( m_window, &m_data );
    setVSync( true );

    setGLFWCallbacks();
}

Window::~Window()
{
    glfwDestroyWindow( m_window );
}

void Window::setGLFWCallbacks()
{
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow * window, int width, int height)
    {
        auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data->width = width;
        data->height = height;

        Events::WindowResize event( width, height );
        data->eventBuss->publish( event );
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow * window)
    {
        auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        Events::WindowClose event;
        data->eventBuss->publish( event );
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow * window, int key, int /*scancode*/, int action, int /*modes*/)
    {
        auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
            case GLFW_PRESS:
            {
                Events::KeyPressed event(key, 0);
                data->eventBuss->publish( event );
                break;
            }
            case GLFW_RELEASE:
            {
                Events::KeyReleased event(key);
                data->eventBuss->publish( event );
                break;
            }
            case GLFW_REPEAT:
            {
                Events::KeyPressed event(key, 1);
                data->eventBuss->publish( event );
                break;
            }
        }
    });

    glfwSetCharCallback(m_window, [](GLFWwindow * window, unsigned int keycode)
    {
        auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        Events::KeyTyped event( static_cast< int >( keycode ) );
        data->eventBuss->publish( event );
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow * window, int button, int action, int /*modes*/)
    {
        auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
            case GLFW_PRESS:
            {
                Events::MouseButtonPressed event(button);
                data->eventBuss->publish( event );
                break;
            }
            case GLFW_RELEASE:
            {
                Events::MouseButtonReleased event(button);
                data->eventBuss->publish( event );
                break;
            }
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow * window, double xOffset, double yOffset)
    {
        auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        Events::MouseScrolled event((float)xOffset, (float)yOffset);
        data->eventBuss->publish( event );
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow * window, double x, double y)
    {
        auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        Events::MouseMoved event( (float)x, (float)y );
        data->eventBuss->publish( event );
    });
}

void Window::update()
{
    glfwPollEvents();
    m_context->swapBuffers();
}

uint32_t Window::getWidth() const
{
    return m_data.width;
}

uint32_t Window::getHeight() const
{
    return m_data.height;
}

void Window::setEventCallback( EventBuss buss )
{
    m_data.eventBuss = std::move( buss );
}

void Window::setVSync( bool enabled )
{
    glfwSwapInterval( enabled ? 1 : 0 );
    m_data.vSync = enabled;
}

bool Window::isVSync() const
{
    return m_data.vSync;
}

WindowInterface::Ptr Window::create( const WindowInterface::Properties & props )
{
    return std::make_unique< Linux::Window >( props );
}

void * Window::getNativeWindow() const
{
    return m_window;
}

}