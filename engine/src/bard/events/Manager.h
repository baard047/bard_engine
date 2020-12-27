/*
 * \file Manager.h
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

#include <bard/core/Base.h>
#include <bard/core/utils/SFINAE.h>

namespace bard::Events {

namespace detail {

struct FunctionWrapper
{
    using Ptr = std::unique_ptr< FunctionWrapper >;
    void operator()( Event & event ) { call( event ); }
private:
    virtual void call( Event & event ) = 0;
};

template< class SubscriberT, class EventT, class = SFINAE::IsBaseOf< EventT, Event > >
struct Handler : public FunctionWrapper
{
    using Callback = void ( SubscriberT::* )( EventT & );

public:
    Handler( SubscriberT * const subscriber, Callback callback ) noexcept
            : subscriber( subscriber ),
              callback( callback ) {}

    void call( EventT & event ) override
    {
        BARD_CORE_ASSERT( subscriber, "Subscriber is nullptr" )
        ( subscriber->*callback )( static_cast< EventT & >( event ) );
    }

private:
    SubscriberT * const subscriber;
    Callback callback;
};

}

class Manager
{
public:
    using Handlers = std::vector< FunctionWrapper::Ptr >;

public:
    template< class EventT, class = SFINAE::IsBaseOf< EventT, Event > >
    void publish( EventT & event ) noexcept
    {
        auto found = subscribers.find( EventT::type );
        if( found == subscribers.end() )
        {
            CORE_LOG_ERROR("No subscribers for event: {0}", event );
            return;
        }

        for( auto handler : found.second )
        {
            BARD_CORE_ASSERT( handler, "null event handler" );
            if( event.handled )
            {
                break;
            }

            handler->( event );
        }
    }

    template< class SubscriberT, class EventT, class = SFINAE::IsBaseOf< EventT, Event > >
    void subscribe( SubscriberT * subscriber, void ( SubscriberT::*callBack )( EventT & ) )
    {
        auto handler = std::make_unique< detail::Handler< SubscriberT, EventT > >( subscriber, callBack );

        auto found = subscribers.find( EventT::type );
        if( found == subscribers.end() )
        {
            subscribers.emplace( EventT::type, { std::move( handler ) } );
        }
        else { found.second.push_back( std::move( handler ) ); }
    }

private:
    std::unordered_map< Events::Type, Handlers > subscribers;
};

}
