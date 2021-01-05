/*
 * \file ImGuiLayer.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 04.01.2021
 * \time : 22:08
 */

#include "ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

//TODO remove
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <bard/core/Application.h>

namespace bard {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

void ImGuiLayer::onAttach()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO & io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle & style = ImGui::GetStyle();
    if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
    {
        style.WindowRounding = 0.0f;
        style.Colors[ ImGuiCol_WindowBg ].w = 1.0f;
    }

    auto window = static_cast<GLFWwindow *>(Application::instance().window().getNativeWindow());

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL( window, true );
    ImGui_ImplOpenGL3_Init( "#version 410" );
}

void ImGuiLayer::onDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::end()
{
    ImGuiIO & io = ImGui::GetIO();
    Application & app = Application::instance();
    io.DisplaySize = ImVec2( ( float ) app.window().getWidth(), ( float ) app.window().getHeight() );

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

    if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
    {
        GLFWwindow * backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent( backup_current_context );
    }
}

void ImGuiLayer::onImGuiRender()
{
    static bool show = true;
    ImGui::ShowDemoWindow( &show );
}

}