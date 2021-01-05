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

    void onAttach() override;
    void onDetach() override;
    void onImGuiRender() override;

    void begin();
    void end();

private:
    float m_time = 0.0f;
};

}
