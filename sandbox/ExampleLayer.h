/*
 * \file ExampleLayer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 09.01.2021
 * \time : 18:05
 */

#pragma once

#include <Engine.h>
#include <imgui.h>
#include <bard/renderer/Texture.h>

class ExampleLayer : public bard::Layer
{
public:
    ExampleLayer();

    void onImGuiRender() override;
    void onRender() override;
    void onUpdate( bard::Timestep ts ) override;

private:
    bard::ShaderLibrary m_shaders;

    bard::Shader::Ptr m_triangleShader;
    bard::VertexArray::Ptr m_triangleVA;

    bard::Shader::Ptr m_squareShader;
    bard::VertexArray::Ptr m_squareVA;

    bard::Texture2D::Ptr m_checkerboardTexture;
    bard::Texture2D::Ptr m_shipTexture;

    glm::vec3 m_trianglePos = { 1.f, 1.f, 1.f };
    glm::vec3 m_shipPos = { 0.f, 0.f, 0.f };
    glm::vec3 m_squaresColor = { 0.4f, 0.8f, 0.8f };

    bard::CameraController m_cameraController;
};

