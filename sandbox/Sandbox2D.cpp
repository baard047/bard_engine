/*
 * \file Sandbox2D.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 14.01.2021
 * \time : 21:11
 */

#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
        : bard::Layer( "Sandbox2D Layer" ),
          m_cameraController( 1280.f / 720.f )
{
}

void Sandbox2D::onAttach()
{
    m_checkerboardTexture = bard::Texture2D::create( "assets/textures/Checkerboard.png" );
}

void Sandbox2D::onDetach()
{
}

void Sandbox2D::onUpdate( bard::Timestep ts )
{
    m_cameraController.onUpdate( ts );
}

void Sandbox2D::onRender()
{
    bard::RenderCommand::setClearColor( { 0.1f, 0.1f, 0.1f, 1 } );
    bard::RenderCommand::clear();

    bard::Renderer2D::BeginScene( m_cameraController.getCamera() );

//    bard::Renderer2D::DrawQuad( { 0.1f, 0.f, -0.1f }, { 10.f, 10.f }, m_checkerboardTexture );
    bard::Renderer2D::DrawQuad( { -1.f, 0.f }, { 0.8f, 0.8f }, { 0.7f, 0.2f, 0.3f, 1.f } );
    bard::Renderer2D::DrawQuad( { 0.5f, -0.5f }, { 0.5f, 0.75f }, m_squaresColor );

    bard::Renderer2D::EndScene();
}

void Sandbox2D::onImGuiRender()
{
    constexpr static auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_DockNodeHost
                                  | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize
                                  | ImGuiWindowFlags_NoSavedSettings;

    ImGui::SetWindowPos( m_debugName.c_str(), { 0, 0 } );

    ImGui::Begin( m_debugName.c_str(), nullptr, flags );
    ImGui::ColorEdit4( "Squares Color", glm::value_ptr( m_squaresColor ) );
    ImGui::End();
}
