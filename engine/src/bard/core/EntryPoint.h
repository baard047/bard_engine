/*
 * \file EntryPoint.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 24.12.2020
 * \time : 22:33
 */

#pragma once

#include "Application.h"
#include "Base.h"

namespace bard
{

struct EntryPoint
{
    explicit EntryPoint( )
    {
         bard::core::Logger::get().init();
         CORE_LOG_INFO("================ Running bard engine ================");
    }

    inline void run( Application * application )
    {
//        BARD_PROFILE_BEGIN_SESSION( "Runtime", "profile-runtime.json" );
        if( m_application )
        {
            BARD_CORE_ASSERT(false, "Application already running!");
            delete m_application;
        }

        m_application = application;
        m_application->run();
//        BARD_PROFILE_END_SESSION();
    }

    ~EntryPoint()
    {
        delete m_application;
    }

private:
    Application * m_application = nullptr;
};

}
