/*
 * \file Base.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 27.12.2020
 * \time : 13:22
 */

#pragma once

////temp
#include <string>
#include <cstdint>
#include <functional>
#include <memory>
////

#include "logging/Logger.h"

#ifdef BARD_ENABLE_ASSERTS
#include <csignal>
//NOTE: only for linux for now, simply breaks debug with no sigterm
#define BARD_CORE_ASSERT( condition, msg ) { if( !condition ){ CORE_LOG_ERROR( "Assertion failed: {0}", msg ); raise(SIGTRAP);} }
#define BARD_ASSERT( condition, msg ) { if( !condition ){ LOG_ERROR( "Assertion failed: {0}", msg ); raise(SIGTRAP);} }
#else
    #define BARD_ASSERT(...)
    #define BARD_CORE_ASSERT(...)
#endif
