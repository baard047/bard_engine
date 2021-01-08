/*
 * \file Sandbox.cpp
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 20.12.2020
 * \time : 15:27
 */

#include <Engine.h>

#include <imgui.h>

class ExampleLayer : public bard::Layer
{
public:
    ExampleLayer() : bard::Layer("Example Layer") {}

    void onImGuiRender() override
    {
        ImGui::Begin(m_debugName.c_str());
        ImGui::Text("Smth going on in actual application");
        ImGui::End();
    }
};

class Sandbox final : public bard::Application
{
public:
    Sandbox()
    {
        pushLayer( new ExampleLayer{} );
//        pushOverlay( new bard::ImGuiLayer{} );
        LOG_INFO( "Hello from application" );
    }
};

bard::Application * bard::createApplication()
{
    return new Sandbox{};
}
