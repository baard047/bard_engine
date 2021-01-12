/*
 * \file Expected.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 11.01.2021
 * \time : 12:59
 */

#pragma once

#include <type_traits>
#include <utility>
#include <cstdlib>
#include <variant>

namespace Aux
{

struct ExpectNothing final {};

template< typename ValueT, typename ErrorT >
class Expected final
{
    static_assert( !std::is_same< ValueT, ErrorT >::value
                   && !std::is_base_of< ValueT, ErrorT >::value
                   && !std::is_base_of< ErrorT, ValueT >::value
                   && !std::is_convertible< ErrorT, ValueT >::value
                   && !std::is_convertible< ValueT, ErrorT >::value,
                   "Types should not interfere"
    );

public:
    using ValueType = ValueT;
    using ErrorType = ErrorT;
    using SelfType = Expected< ValueType, ErrorType >;

public:
    Expected( ValueType && value ) noexcept ( std::is_nothrow_move_constructible< ValueType >::value )
            : payload( std::move( value ) )
    {

    }

    Expected( ErrorType && error ) noexcept ( std::is_nothrow_move_constructible< ErrorType >::value )
            : payload( std::move( error ) )
    {

    }

    Expected( const Expected & other ) = default;
    Expected( Expected && other ) noexcept = default;
    Expected & operator =( const Expected & other ) = default;
    Expected & operator =( Expected && other ) noexcept = default;

public:
    explicit operator bool() const noexcept
    {
        return nullptr != std::get_if< ValueT >( &payload );
    }

    ValueT & operator *() noexcept
    {
        if( const auto value = std::get_if< ValueT >( &payload ) )
        {
            return *value;
        }
        std::abort();
    }

    const ValueT & operator *() const noexcept
    {
        if( const auto value = std::get_if< ValueT >( &payload ) )
        {
            return *value;
        }
        std::abort();
    }

    ValueT * operator ->() noexcept
    {
        return std::get_if< ValueT >( &payload );
    }

    const ValueT * operator ->() const noexcept
    {
        return std::get_if< ValueT >( &payload );
    }

public:
    const ErrorT & getError() const noexcept
    {
        if( const auto error = std::get_if< ErrorT >( &payload ) )
        {
            return *error;
        }
        std::abort();
    }

    ErrorT & getError() noexcept
    {
        if( const auto error = std::get_if< ErrorT >( &payload ) )
        {
            return *error;
        }
        std::abort();
    }

private:
    std::variant< ValueT, ErrorT > payload;
};

template< typename ErrorT >
using NotExpected = Expected< ExpectNothing, ErrorT >;


}