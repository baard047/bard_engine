/*
 * \file Singletone.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 22.10.2020
 * \time : 17:35
 */

#pragma once

#include <memory>
#include <mutex>

namespace bard {

template< typename HeirT >
class Singleton
{
public:
    Singleton() = delete;

    Singleton( const Singleton & ) = delete;

    Singleton & operator =( const Singleton & ) = delete;

    static HeirT & instance()
    {
        if( !m_instance )
        {
            static std::mutex mutex;
            std::lock_guard< std::mutex > lock( mutex );
            if( !m_instance ) { m_instance.reset( new HeirT() ); }
        }
        return *m_instance;
    }

protected:
    explicit Singleton( void * ) {}

private:
    static std::unique_ptr< HeirT > m_instance;
};

template< typename HeirT > std::unique_ptr< HeirT > Singleton< HeirT >::m_instance;

}
