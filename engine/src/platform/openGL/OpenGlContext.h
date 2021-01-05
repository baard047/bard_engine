/*
 * \file OpenGlContext.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 05.01.2021
 * \time : 21:38
 */

#pragma once

#include <bard/renderer/GraphicsContext.h>

struct GLFWwindow;

namespace bard
{

class OpenGlContext : public GraphicsContext
{
public:
    explicit OpenGlContext( GLFWwindow * handle ) noexcept;

    void init() override;
    void swapBuffers() override;

private:
    GLFWwindow * m_windowHandle;
};

}
