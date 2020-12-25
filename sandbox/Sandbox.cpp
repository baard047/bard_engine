/*
 * \file rd.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 20.12.2020
 * \time : 15:27
 */

#include <Engine.h>

class Sandbox final : public bard::Application
{
public:
    Sandbox() { LOG_INFO( "Hello from application" ); }
};

bard::Application * bard::createApplication()
{
    return new Sandbox{};
}
