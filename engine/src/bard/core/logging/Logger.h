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

#include <bard/auxiliary/Singleton.h>

namespace bard::core {

class Logger : public Aux::Singleton< Logger >
{
    using Ptr = std::shared_ptr< spdlog::logger >;

public:
    void init();

    inline const Ptr & defaultClientLogger() { return m_defaultLogger; }

private:
    Ptr makeLogger( std::string_view name ) noexcept;

private:
    Ptr m_defaultLogger;

private:
    friend class Singleton< Logger >;
    Logger();
};

}

//TODO allow user define custom logger category

#define CORE_LOG_TRACE( ... )  SPDLOG_TRACE( __VA_ARGS__ )
#define CORE_LOG_DEBUG( ... )  SPDLOG_DEBUG( __VA_ARGS__ )
#define CORE_LOG_INFO( ... )  SPDLOG_INFO( __VA_ARGS__ )
#define CORE_LOG_WARN( ... )  SPDLOG_WARN( __VA_ARGS__ )
#define CORE_LOG_ERROR( ... )  SPDLOG_ERROR( __VA_ARGS__ )
#define CORE_LOG_CRITICAL( ... )  SPDLOG_CRITICAL( __VA_ARGS__ )

#define LOG_TRACE( ... )  SPDLOG_LOGGER_TRACE( bard::core::Logger::get().defaultClientLogger(), __VA_ARGS__ )
#define LOG_DEBUG( ... )  SPDLOG_LOGGER_DEBUG( bard::core::Logger::get().defaultClientLogger(), __VA_ARGS__ )
#define LOG_INFO( ... )  SPDLOG_LOGGER_INFO( bard::core::Logger::get().defaultClientLogger(), __VA_ARGS__ )
#define LOG_WARN( ... )  SPDLOG_LOGGER_WARN( bard::core::Logger::get().defaultClientLogger(), __VA_ARGS__ )
#define LOG_ERROR( ... )  SPDLOG_LOGGER_ERROR( bard::core::Logger::get().defaultClientLogger(), __VA_ARGS__ )
#define LOG_CRITICAL( ... )  SPDLOG_LOGGER_CRITICAL( bard::core::Logger::get().defaultClientLogger(), __VA_ARGS__ )