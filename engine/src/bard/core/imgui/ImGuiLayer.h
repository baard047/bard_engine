/*
 * \file ImGuiLayer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 04.01.2021
 * \time : 22:08
 */

#pragma once

#include <bard/core/Layer.h>

#include <bard/events/MouseEvent.h>
#include <bard/events/ApplicationEvent.h>
#include <bard/events/KeyEvent.h>

namespace bard {

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    void setupConnections() override;

    void attach() override;
    void update() override;

private:
    bool onMouseButtonPressed( Events::MouseButtonPressed & event );
    bool onMouseButtonReleased( Events::MouseButtonReleased & event );
    bool onMouseMoved( Events::MouseMoved & event );
    bool onMouseButtonScrolled( Events::MouseScrolled & event );

    bool onKeyPressed( Events::KeyPressed & event );
    bool onKeyReleased( Events::KeyReleased & event );
    bool onKeyTyped( Events::KeyTyped & event );

    bool onWindowResize( Events::WindowResize & event );

private:
    float m_time = 0.0f;
};

}
