/*
 * \file Profiler.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 16.01.2021
 * \time : 20:29
 */

#pragma once

#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

#include <bard/core/logging/Logger.h>
#include "Singleton.h"

namespace Aux::Profiling
{

using FloatingPointMicroseconds = std::chrono::duration< double, std::micro >;
using Microseconds = std::chrono::microseconds;

constexpr const auto DEFAULT_FILE_NAME = "profiling_results.json";

struct ProfileResult
{
    std::string name;

    FloatingPointMicroseconds start;
    Microseconds elapsedTime;
    std::thread::id threadID;
};

struct Session
{
    explicit Session( std::string name ) : name( std::move(name) ) {}
    std::string name;
};

class Profiler : public Aux::Singleton< Profiler >
{
public:
    void BeginSession(const std::string& name, const std::string& filepath = DEFAULT_FILE_NAME )
    {
        std::lock_guard lock(m_mutex);

        if (m_currentSession )
        {
            // If there is already a current session, then close it before beginning new one.
            // Subsequent profiling output meant for the original session will end up in the
            // newly opened session instead.  That's better than having badly formatted
            // profiling output.
            CORE_LOG_ERROR( "Profiler::BeginSession('{0}') when session '{1}' already open.",
                            name, m_currentSession->name );
            InternalEndSession();
        }

        m_outputStream.open( filepath );
        if( m_outputStream.is_open() )
        {
            m_currentSession = new Session( name );
            WriteHeader();
        }
        else { CORE_LOG_ERROR( "Profiler could not open results file '{0}'.", filepath ); }
    }

    void EndSession()
    {
        std::lock_guard lock(m_mutex);
        InternalEndSession();
    }

    void WriteProfile(const ProfileResult& result)
    {
        std::stringstream json;

        json << std::setprecision(3) << std::fixed;
        json << ",{";
        json << "\"cat\":\"function\",";
        json << "\"dur\":" << (result.elapsedTime.count()) << ',';
        json << "\"name\":\"" << result.name << "\",";
        json << "\"ph\":\"X\",";
        json << "\"pid\":0,";
        json << "\"tid\":" << result.threadID << ",";
        json << "\"ts\":" << result.start.count();
        json << "}";

        std::lock_guard lock(m_mutex);
        if (m_currentSession)
        {
            m_outputStream << json.str();
            m_outputStream.flush();
        }
    }

    ~Profiler() { EndSession(); }

private:
    friend class Aux::Singleton< Profiler >;
    Profiler() : Singleton( nullptr ) {}

    void WriteHeader()
    {
        m_outputStream << R"({"otherData": {},"traceEvents":[{})";
        m_outputStream.flush();
    }

    void WriteFooter()
    {
        m_outputStream << "]}";
        m_outputStream.flush();
    }

    // Note: you must already own lock on m_mutex before
    // calling InternalEndSession()
    void InternalEndSession()
    {
        if( m_currentSession )
        {
            WriteFooter();
            m_outputStream.close();
            delete m_currentSession;
            m_currentSession = nullptr;
        }
    }
private:
    std::mutex m_mutex;
    Session * m_currentSession = nullptr;
    std::ofstream m_outputStream;
};

class InstrumentationTimer
{
    using Clock = std::chrono::steady_clock;
    
public:
    explicit InstrumentationTimer( const char * name )
            : m_name( name ),
              m_startTimestamp( Clock::now() ),
              m_stopped( false )
    {
    }

    ~InstrumentationTimer()
    {
        if ( !m_stopped ) { Stop(); }
    }

    void Stop()
    {
        auto endTimepoint = Clock::now();
        auto highResStart = FloatingPointMicroseconds{ m_startTimestamp.time_since_epoch() };
        auto elapsedTime = std::chrono::time_point_cast< Microseconds >( endTimepoint ).time_since_epoch()
                           - std::chrono::time_point_cast< Microseconds >( m_startTimestamp ).time_since_epoch();

        Profiler::get().WriteProfile( { m_name, highResStart, elapsedTime, std::this_thread::get_id() } );

        m_stopped = true;
    }
private:
    const char * m_name;
    std::chrono::time_point< Clock > m_startTimestamp;
    bool m_stopped;
};

namespace detail {

template< size_t N >
struct ChangeResult
{
    char data[N];
};

template< size_t N, size_t K >
constexpr auto CleanupOutputString( const char(& expr)[N], const char(& remove)[K] )
{
    ChangeResult< N > result = {};

    size_t srcIndex = 0;
    size_t dstIndex = 0;
    while( srcIndex < N )
    {
        size_t matchIndex = 0;
        while( matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[ srcIndex + matchIndex ] == remove[ matchIndex ] )
        {
            matchIndex++;
        }

        if( matchIndex == K - 1 ) { srcIndex += matchIndex; }

        result.data[ dstIndex++ ] = expr[ srcIndex ] == '"' ? '\'' : expr[ srcIndex ];
        srcIndex++;
    }
    return result;
}
}

}

#ifdef BARD_USE_PROFILER
    // Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define FUNC_SIGNATURE __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define FUNC_SIGNATURE __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define FUNC_SIGNATURE __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define FUNC_SIGNATURE __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define FUNC_SIGNATURE __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define FUNC_SIGNATURE __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define FUNC_SIGNATURE __func__
	#else
		#define FUNC_SIGNATURE "FUNC_SIGNATURE unknown!"
	#endif

	#define BARD_PROFILE_BEGIN_SESSION(name, filepath) Aux::Profiling::Profiler::get().BeginSession(name, filepath)
	#define BARD_PROFILE_END_SESSION() Aux::Profiling::Profiler::get().EndSession()
	#define BARD_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = Aux::Profiling::detail::CleanupOutputString(name, "__cdecl ");\
											   Aux::Profiling::InstrumentationTimer timer##line(fixedName##line.data)
	#define BARD_PROFILE_SCOPE_LINE(name, line) BARD_PROFILE_SCOPE_LINE2(name, line)
	#define BARD_PROFILE_SCOPE(name) BARD_PROFILE_SCOPE_LINE(name, __LINE__)
	#define BARD_PROFILE_FUNCTION() BARD_PROFILE_SCOPE(FUNC_SIGNATURE)
#else
    #define BARD_PROFILE_BEGIN_SESSION(name, filepath)
    #define BARD_PROFILE_END_SESSION()
    #define BARD_PROFILE_SCOPE(name)
    #define BARD_PROFILE_FUNCTION()
#endif