/*
 * \file Logger.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 24.12.2020
 * \time : 23:19
 */

#pragma once

#include <memory>
#include <string_view>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace bard::core {

//TODO singletone
class Logger
{
private:
    using Ptr = std::shared_ptr< spdlog::logger >;

public:
    static void init();
    static Ptr makeLogger( std::string_view name ) noexcept;

    inline static const Ptr & coreLogger() { return s_coreLogger; }
    inline static const Ptr & defaultClientLogger() { return s_clientLogger; }

private:
    static Ptr s_coreLogger;
    static Ptr s_clientLogger;
};

}

//TODO allow user define custom logger category

#define CORE_LOG_TRACE( ... )  SPDLOG_TRACE( __VA_ARGS__ )
#define CORE_LOG_DEBUG( ... )  SPDLOG_DEBUG( __VA_ARGS__ )
#define CORE_LOG_INFO( ... )  SPDLOG_INFO( __VA_ARGS__ )
#define CORE_LOG_WARN( ... )  SPDLOG_WARN( __VA_ARGS__ )
#define CORE_LOG_ERROR( ... )  SPDLOG_ERROR( __VA_ARGS__ )
#define CORE_LOG_CRITICAL( ... )  SPDLOG_CRITICAL( __VA_ARGS__ )

#define LOG_TRACE( ... )  SPDLOG_LOGGER_TRACE( bard::core::Logger::defaultClientLogger(), __VA_ARGS__ )
#define LOG_DEBUG( ... )  SPDLOG_LOGGER_DEBUG( bard::core::Logger::defaultClientLogger(), __VA_ARGS__ )
#define LOG_INFO( ... )  SPDLOG_LOGGER_INFO( bard::core::Logger::defaultClientLogger(), __VA_ARGS__ )
#define LOG_WARN( ... )  SPDLOG_LOGGER_WARN( bard::core::Logger::defaultClientLogger(), __VA_ARGS__ )
#define LOG_ERROR( ... )  SPDLOG_LOGGER_ERROR( bard::core::Logger::defaultClientLogger(), __VA_ARGS__ )
#define LOG_CRITICAL( ... )  SPDLOG_LOGGER_CRITICAL( bard::core::Logger::defaultClientLogger(), __VA_ARGS__ )