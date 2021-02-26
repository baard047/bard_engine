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
    bard::Renderer2D::resetStats();

    bard::RenderCommand::setClearColor( { 0.1f, 0.1f, 0.1f, 1 } );
    bard::RenderCommand::clear();

    bard::Renderer2D::BeginScene( m_cameraController.getCamera() );

    bard::Renderer2D::DrawQuad( { -5.0f, -5.0f, -0.1f }, { 10.f, 10.f }, m_checkerboardTexture, 10.f );
    bard::Renderer2D::DrawQuad( { -1.f, 0.f }, { 1.f, 1.f }, m_squaresColor );
    bard::Renderer2D::DrawQuad( { 0.5f, -0.5f }, { 0.5f, 0.75f }, m_squaresColor );

    ////test
    for( float y = -5.f; y < 5.f; y += 0.5f )
    {
        for( float x = -5.f; x < 5.f; x += 0.5f )
        {
            glm::vec4 color = { ( x + 5.f ) / 10.f, 0.4f, ( y + 5.f ) / 10.f, 0.75f };
            bard::Renderer2D::DrawQuad( { x, y }, { 0.45f, 0.45f }, color );
        }
    }

    bard::Renderer2D::EndScene();
}

void Sandbox2D::onImGuiRender()
{
    constexpr static auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_DockNodeHost
                                  | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize
                                  | ImGuiWindowFlags_NoSavedSettings;

    ImGui::SetWindowPos( m_debugName.c_str(), { 0, 0 } );

    auto stats = bard::Renderer2D::getStats();

    ImGui::Begin( m_debugName.c_str(), nullptr, flags );
    ImGui::Text("Renderer2D stats:");
    ImGui::Text("Draw calls: %d", stats.drawCalls);
    ImGui::Text("Quads: %d", stats.quadCount);
    ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
    ImGui::Text("Indices: %d", stats.getTotalIndexCount());
    ImGui::Spacing(); ImGui::Spacing();
    ImGui::ColorEdit4( "Squares Color", glm::value_ptr( m_squaresColor ) );
    ImGui::End();
}
