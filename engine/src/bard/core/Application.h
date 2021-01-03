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

namespace bard
{

class Application
{
public:
    Application();
    virtual ~Application() = default;

    void run();

    void pushLayer( Layer * layer);
    void pushOverlay( Layer * overlay);

    inline WindowInterface & window() { return *m_window; }

private:
    void onWindowCloseEvent( Events::WindowClose & event );

private:
    LayerStack m_layerStack;
    Events::Manager::Ptr m_eventBuss;
    WindowInterface::Ptr m_window;

    bool m_running;
};

Application * createApplication();

}



