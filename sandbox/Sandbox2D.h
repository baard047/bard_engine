/*
 * \file Sandbox2D.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 14.01.2021
 * \time : 21:11
 */

#pragma once

#include <Engine.h>

class Sandbox2D : public bard::Layer
{
public:
    Sandbox2D();

    void onAttach() override;
    void onDetach() override;

    void onUpdate( bard::Timestep ts ) override;
    void onRender() override;

    void onImGuiRender() override;

private:
    bard::CameraController m_cameraController;

    bard::Texture2D::Ptr m_checkerboardTexture;

    glm::vec4 m_squaresColor = { 0.2f, 0.3f, 0.8f, 1.f };
};
