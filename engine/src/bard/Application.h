/*
 * \file Application.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 24.12.2020
 * \time : 22:17
 */

#pragma once

namespace bard
{

class Application
{
public:
    Application();
    virtual ~Application();

    void run();
};

Application * createApplication();

}



