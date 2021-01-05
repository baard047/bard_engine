/*
 * \file rd.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 20.12.2020
 * \time : 15:27
 */

#include <Engine.h>

class ExampleLayer : public bard::Layer
{
public:
    ExampleLayer() : bard::Layer("Example") {}

    void update() override { }
};

class Sandbox final : public bard::Application
{
public:
    Sandbox()
    {
        pushLayer( new ExampleLayer{} );
        pushOverlay( new bard::ImGuiLayer{} );
        LOG_INFO( "Hello from application" );
    }
};

bard::Application * bard::createApplication()
{
    return new Sandbox{};
}
