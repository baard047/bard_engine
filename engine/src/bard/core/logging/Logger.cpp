/*
 * \file Logger.cpp.cc
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 24.12.2020
 * \time : 23:19
 */

#include "Logger.h"
#include <mutex>
#include <chrono>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/async_logger.h>
#include <spdlog/async.h>
#include <spdlog/cfg/env.h>

namespace bard::core {

namespace {
constexpr auto DEFAULT_LOGS_FOLDER = "./logs/";
constexpr auto DEFAULT_PATTERN = "[%d-%m-%-Y %H:%M:%S.%e] [%^%l%$] %n: %v";
constexpr auto MEGABYTE = 1024 * 1024;

struct ConsoleMutex final
{
    using mutex_t = std::mutex;
    static mutex_t & mutex() noexcept
    {
        static mutex_t s_mutex;
        return s_mutex;
    }
};

using ConsoleSink = spdlog::sinks::ansicolor_stdout_sink< ConsoleMutex >;
using FileSink = spdlog::sinks::rotating_file_sink< std::mutex >;
}

void Logger::init()
{
    static std::once_flag flag;

    std::call_once( flag, [ this ]() noexcept
    {
        spdlog::init_thread_pool( 8192, 1 );
        spdlog::cfg::load_env_levels();

        spdlog::set_level( spdlog::level::level_enum::trace );
        spdlog::set_pattern( DEFAULT_PATTERN );
        spdlog::flush_on( spdlog::level::critical );
        spdlog::flush_every( std::chrono::seconds{ 3 } );

        auto logger = makeLogger( "Engine" );
        spdlog::set_default_logger( logger );

        m_defaultLogger = makeLogger( "Application" );
    } );
}

Logger::Ptr Logger::makeLogger( std::string_view name ) noexcept
{
    if( auto alreadyExists = spdlog::get( name.data() ) )
    {
        return alreadyExists;
    }

    SPDLOG_INFO( "Adding new logger: {}", name.data() );

    std::vector< spdlog::sink_ptr > sinks{
            std::make_shared< ConsoleSink >(),
            std::make_shared< FileSink >( std::string{ DEFAULT_LOGS_FOLDER } + name.data() + ".txt",
                                          MEGABYTE * 10, 5 )
    };

    auto logger = std::make_shared< spdlog::async_logger >(
            name.data(),
            sinks.begin(), sinks.end(),
            spdlog::thread_pool(),
            spdlog::async_overflow_policy::block
    );

    logger->set_level( spdlog::level::level_enum::trace );
    logger->set_pattern( DEFAULT_PATTERN );
    logger->flush_on( spdlog::level::critical );

    spdlog::register_logger( logger );
    return logger;
}

Logger::Logger() : Singleton( nullptr ) {}

}