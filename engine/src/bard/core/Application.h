/*
 * \file Application.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 24.12.2020
 * \time : 22:17
 */

#pragma once

#include "WindowInterface.h"
#include <bard/events/ApplicationEvent.h>
#include <bard/core/LayerStack.h>
#include <bard/core/imgui/ImGuiLayer.h>

#include <bard/renderer/Shader.h> //TODO rm
#include <bard/renderer/buffer/Buffer.h>

namespace bard
{

class Application
{
public:
    virtual ~Application() = default;

    void run();

    void pushLayer( Layer * layer);
    void pushOverlay( Layer * overlay);

    inline static Application & instance() { return *m_instance; }
    inline WindowInterface & window() { return *m_window; }

protected:
    Application();

private:
    bool onWindowCloseEvent( Events::WindowClose & event );

private:
    LayerStack m_layerStack;
    Events::Manager::Ptr m_eventBuss;
    WindowInterface::Ptr m_window;
    ImGuiLayer * m_ImGuiLayer;

    //TODO rm
    uint32_t m_vertexArray;
    std::unique_ptr< Shader > m_shader;
    std::unique_ptr< VertexBuffer > m_vertexBuffer;
    std::unique_ptr< IndexBuffer > m_indexBuffer;

    bool m_running;

private:
    static Application * m_instance;
};

Application * createApplication();

}



