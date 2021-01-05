/*
 * \file Input.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 05.01.2021
 * \time : 14:48
 */

#include <bard/core/Input.h>
#include <bard/core/Application.h>

#include <GLFW/glfw3.h>

namespace bard {

namespace {
GLFWwindow * getGLFWWindow()
{
    return static_cast<GLFWwindow *>(Application::instance().window().getNativeWindow());
}
}

bool Input::isKeyPressed( KeyCode key )
{
    auto state = glfwGetKey( getGLFWWindow(), static_cast<int32_t>(key) );
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isMouseButtonPressed( MouseCode button )
{
    auto state = glfwGetMouseButton( getGLFWWindow(), static_cast<int32_t>(button) );
    return state == GLFW_PRESS;
}

std::pair<float, float> Input::getMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos( getGLFWWindow(), &xpos, &ypos );

    return { ( float ) xpos, ( float ) ypos };
}

float Input::getMouseX()
{
    return getMousePosition().first;
}

float Input::getMouseY()
{
    return getMousePosition().second;
}

}