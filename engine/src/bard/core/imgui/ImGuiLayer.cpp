/*
 * \file ImGuiLayer.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 04.01.2021
 * \time : 22:08
 */

#include "ImGuiLayer.h"

#include <imgui.h>
#include <platform/openGL/ImguiOpenGl_Renderer.h>

//TODO remove
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <bard/core/Application.h>

namespace bard {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

void ImGuiLayer::setupConnections()
{
    m_eventBuss->subscribe( this, &ImGuiLayer::onMouseButtonPressed );
    m_eventBuss->subscribe( this, &ImGuiLayer::onMouseButtonReleased );
    m_eventBuss->subscribe( this, &ImGuiLayer::onMouseMoved );
    m_eventBuss->subscribe( this, &ImGuiLayer::onMouseButtonScrolled );
    m_eventBuss->subscribe( this, &ImGuiLayer::onKeyPressed );
    m_eventBuss->subscribe( this, &ImGuiLayer::onKeyReleased );
    m_eventBuss->subscribe( this, &ImGuiLayer::onKeyTyped );
    m_eventBuss->subscribe( this, &ImGuiLayer::onWindowResize );
}

void ImGuiLayer::attach()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    auto io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    //TODO change on my own keycodes
    io.KeyMap[ ImGuiKey_Tab ] = GLFW_KEY_TAB;
    io.KeyMap[ ImGuiKey_LeftArrow ] = GLFW_KEY_LEFT;
    io.KeyMap[ ImGuiKey_RightArrow ] = GLFW_KEY_RIGHT;
    io.KeyMap[ ImGuiKey_UpArrow ] = GLFW_KEY_UP;
    io.KeyMap[ ImGuiKey_DownArrow ] = GLFW_KEY_DOWN;
    io.KeyMap[ ImGuiKey_PageUp ] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ ImGuiKey_PageDown ] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ ImGuiKey_Home ] = GLFW_KEY_HOME;
    io.KeyMap[ ImGuiKey_End ] = GLFW_KEY_END;
    io.KeyMap[ ImGuiKey_Insert ] = GLFW_KEY_INSERT;
    io.KeyMap[ ImGuiKey_Delete ] = GLFW_KEY_DELETE;
    io.KeyMap[ ImGuiKey_Backspace ] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ ImGuiKey_Space ] = GLFW_KEY_SPACE;
    io.KeyMap[ ImGuiKey_Enter ] = GLFW_KEY_ENTER;
    io.KeyMap[ ImGuiKey_Escape ] = GLFW_KEY_ESCAPE;
    io.KeyMap[ ImGuiKey_A ] = GLFW_KEY_A;
    io.KeyMap[ ImGuiKey_C ] = GLFW_KEY_C;
    io.KeyMap[ ImGuiKey_V ] = GLFW_KEY_V;
    io.KeyMap[ ImGuiKey_X ] = GLFW_KEY_X;
    io.KeyMap[ ImGuiKey_Y ] = GLFW_KEY_Y;
    io.KeyMap[ ImGuiKey_Z ] = GLFW_KEY_Z;

    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::update()
{
    ImGuiIO &io = ImGui::GetIO();
    auto &window = Application::instance().window();
    io.DisplaySize = ImVec2( window.getWidth(), window.getHeight() );

    auto time = static_cast<float>(glfwGetTime());
    io.DeltaTime = m_time > 0.0 ? ( time - m_time ) : ( 1.0f / 60.0f );
    m_time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//    Layer::update();
}

bool ImGuiLayer::onMouseButtonPressed( Events::MouseButtonPressed & event )
{
    ImGuiIO & io = ImGui::GetIO();
    io.MouseDown[ event.button ] = true;
    return false;
}

bool ImGuiLayer::onMouseButtonReleased( Events::MouseButtonReleased & event )
{
    ImGuiIO & io = ImGui::GetIO();
    io.MouseDown[ event.button ] = false;
    return false;
}

bool ImGuiLayer::onMouseMoved( Events::MouseMoved & event )
{
    ImGuiIO & io = ImGui::GetIO();
    io.MousePos = ImVec2( event.x, event.y );
    return false;
}

bool ImGuiLayer::onMouseButtonScrolled( Events::MouseScrolled & event )
{
    ImGuiIO & io = ImGui::GetIO();
    io.MouseWheelH += event.xOffset;
    io.MouseWheel += event.yOffset;
    return false;
}

bool ImGuiLayer::onKeyPressed( Events::KeyPressed & event )
{
    ImGuiIO & io = ImGui::GetIO();
    io.KeysDown[ event.keycode ] = true;

    //TODO change keycodes on my own codes
    io.KeyCtrl = io.KeysDown[ GLFW_KEY_LEFT_CONTROL ] || io.KeysDown[ GLFW_KEY_RIGHT_CONTROL ];
    io.KeyShift = io.KeysDown[ GLFW_KEY_LEFT_SHIFT ] || io.KeysDown[ GLFW_KEY_RIGHT_SHIFT ];
    io.KeyAlt = io.KeysDown[ GLFW_KEY_LEFT_ALT ] || io.KeysDown[ GLFW_KEY_RIGHT_ALT ];
    io.KeySuper = io.KeysDown[ GLFW_KEY_LEFT_SUPER ] || io.KeysDown[ GLFW_KEY_RIGHT_SUPER ];

    return false;
}

bool ImGuiLayer::onKeyReleased( Events::KeyReleased & event )
{
    ImGuiIO & io = ImGui::GetIO();
    io.KeysDown[ event.keycode ] = false;
    return false;
}

bool ImGuiLayer::onKeyTyped( Events::KeyTyped & event )
{
    ImGuiIO & io = ImGui::GetIO();
    if( event.keycode > 0 && event.keycode < 0x10000 )
    {
        io.AddInputCharacter( static_cast<uint16_t>(event.keycode) );
    }
    return false;
}

bool ImGuiLayer::onWindowResize( Events::WindowResize & event )
{
    ImGuiIO & io = ImGui::GetIO();
    io.DisplaySize = ImVec2( event.width, event.height );
    io.DisplayFramebufferScale = ImVec2( 1.0f, 1.0f );
    glViewport( 0, 0, event.width, event.height );
    return false;
}

}