/*
 * \file Sandbox.cpp
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 20.12.2020
 * \time : 15:27
 */

#include <Engine.h>

#include "ExampleLayer.h"

class Sandbox final : public bard::Application
{
public:
    Sandbox()
    {
        pushLayer( new ExampleLayer{} );
//        pushOverlay( new bard::ImGuiLayer{} );
        LOG_INFO("Sandbox has been created!");
    }
};


int main( int argc, char ** argv )
{
    bard::EntryPoint entryPoint;
    entryPoint.run( new Sandbox{} );

    return 0;
}