/*
 * \file Context.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 05.01.2021
 * \time : 21:38
 */

#include "Context.h"
#include <bard/core/Base.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace OpenGL {

Context::Context( GLFWwindow * handle ) noexcept
        : m_windowHandle( handle )
{
    BARD_CORE_ASSERT(m_windowHandle, "Window handle is null");
}

void Context::init()
{
    glfwMakeContextCurrent( m_windowHandle );
    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    BARD_CORE_ASSERT(status, "Failed to initialize GLAD");

    if( status != 0 )
    {
        CORE_LOG_INFO("--- OpenGL Info:");
        CORE_LOG_INFO("--- Vendor: {0}", glGetString(GL_VENDOR));
        CORE_LOG_INFO("--- Renderer: {0}", glGetString(GL_RENDERER));
        CORE_LOG_INFO("--- Version: {0}", glGetString(GL_VERSION));
    }
}

void Context::swapBuffers()
{
    glfwSwapBuffers( m_windowHandle );
}

}