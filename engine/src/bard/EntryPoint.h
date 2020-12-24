/*
 * \file EntryPoint.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 24.12.2020
 * \time : 22:33
 */

#pragma once

extern bard::Application * bard::createApplication();

int main( int argc, char ** argv )
{
//    Bard::Logger::init();

    auto app = bard::createApplication();
    app->run();
    delete app;

    return 0;
}