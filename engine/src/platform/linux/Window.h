/*
 * \file Window.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 02.01.2021
 * \time : 15:09
 */

#pragma once

#include <GLFW/glfw3.h>

#include <bard/core/WindowInterface.h>
#include <bard/renderer/GraphicsContext.h>

namespace bard::Linux {

class Window : public WindowInterface
{
public:
    ~Window() override;

    static WindowInterface::Ptr create( const WindowInterface::Properties & props );

    uint32_t getWidth() const override;
    uint32_t getHeight() const override;

    void update() override;

    void setVSync( bool enabled ) override;
    bool isVSync() const override;

    void * getNativeWindow() const override;

protected:
    explicit Window( const WindowInterface::Properties & props );

private:
    void setGLFWCallbacks();

private:
    struct WindowData
    {
        std::string title;
        uint32_t width, height;
        bool vSync;
    };

    GLFWwindow * m_window;
    std::unique_ptr< GraphicsContext > m_context;
    WindowData m_data;
};

}