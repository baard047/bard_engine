/*
 * \file EntryPoint.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 24.12.2020
 * \time : 22:33
 */

#pragma once

#include "core/logging/Logger.h"

extern bard::Application * bard::createApplication();

int main( int argc, char ** argv )
{
    bard::core::Logger::init();
    CORE_LOG_INFO("info");
    CORE_LOG_TRACE("TRACE");
    CORE_LOG_WARN("some warn");
    CORE_LOG_ERROR("some error");
    CORE_LOG_DEBUG("debug message");
    CORE_LOG_CRITICAL("CRITICAL");

    auto app = bard::createApplication();
    app->run();
    delete app;

    return 0;
}