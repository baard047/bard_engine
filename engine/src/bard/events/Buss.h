/*
 * \file Buss.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 26.12.2020
 * \time : 13:28
 */

#pragma once

#include "Event.h"

#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

#include <bard/core/Base.h>
#include <bard/auxiliary/SFINAE.h>
#include <bard/auxiliary/Singleton.h>

namespace bard::Events {

namespace detail {

template< class SubscriberT, class EventT, class = SFINAE::IsBaseOf< Event, EventT > >
using Callback = bool ( SubscriberT::* )( EventT & );

struct FunctionWrapper
{
    using Ptr = std::unique_ptr< FunctionWrapper >;
    bool operator()( Event & event ) { return call( event ); }
private:
    virtual bool call( Event & event ) = 0;
};

template< class SubscriberT, class EventT >
struct Handler : public FunctionWrapper
{
public:
    Handler( SubscriberT * const subscriber, Callback< SubscriberT, EventT > callback ) noexcept
            : subscriber( subscriber ),
              callback( callback ) {}

    bool call( Event & event ) override
    {
        BARD_CORE_ASSERT( subscriber, "Subscriber is nullptr" )
        if( subscriber )
        {
            return ( subscriber->*callback )( static_cast< EventT & >( event ) );
        }
        return false;
    }

    bool checkSubscriber( SubscriberT * const other ) //NOTE: for unsubscribe
    {
        return subscriber == other;
    }

private:
    SubscriberT * const subscriber;
    Callback< SubscriberT, EventT > callback;
};

}

class Buss : public Aux::Singleton< Buss >
{
    using Handlers = std::vector< detail::FunctionWrapper::Ptr >;

public:
    template< class EventT, class = SFINAE::IsBaseOf< Event, EventT > >
    void publish( EventT & event ) noexcept
    {
        auto found = subscribers.find( EventT::staticType );
        if( found != subscribers.end() )
        {
            for( const auto & handler : found->second )
            {
                BARD_CORE_ASSERT( handler, "null event handler" );
                if( handler )
                {
                    event.handled = ( *handler )( event );
                }
                if( event.handled ) { break; }
            }
        }
    }

    template< class SubscriberT, class EventT >
    void subscribe( SubscriberT * subscriber, detail::Callback< SubscriberT, EventT > callback )
    {
        auto handler = std::make_unique< detail::Handler< SubscriberT, EventT > >( subscriber, callback );
        subscribers[ EventT::staticType ].push_back( std::move( handler ) );
    }

    template< class EventT, class SubscriberT, class = SFINAE::IsBaseOf< Event, EventT >>
    void unsubscribe( SubscriberT * subscriber )
    {
        auto found = subscribers.find( EventT::staticType );
        if( found != subscribers.end() )
        {
            auto & handlers = found->second;

            auto it = std::remove_if( handlers.begin(), handlers.end(),
                                     [ subscriber ]( const auto & entry )
                                     {
                                         auto handler = dynamic_cast< detail::Handler< SubscriberT, EventT > * > ( entry.get() );
                                         return handler && handler->checkSubscriber( subscriber );
                                     } );
            handlers.erase( it, handlers.end() );

            if( handlers.empty() ) { subscribers.erase( found ); }
        }
        else { BARD_CORE_ASSERT( "No subscribers for event type {0}", EventT::staticType ); }
    }

private:
    Buss() : Singleton( nullptr ) {}
    friend class Singleton< Buss >;

private:
    std::unordered_map< Events::Type, Handlers > subscribers;
};

}
