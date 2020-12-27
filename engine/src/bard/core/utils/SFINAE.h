/*
 * \file Utils.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 26.12.2020
 * \time : 13:46
 */

#pragma once

#include <type_traits>
#include <string>

namespace bard::SFINAE {

template< class BaseT, class T >
using IsBaseOf = typename std::enable_if_t< std::is_base_of< BaseT, T >::value, T >;

template< class One, class Two >
using IsSame = typename std::enable_if_t< std::is_same< One, Two >::value >;

template< class T >
using IsUnsigned = typename std::enable_if_t< std::is_unsigned< T >::value
                                              && !std::is_same< T, bool >::value >;

template< class T >
using IsInt = typename std::enable_if_t< std::is_signed< T >::value
                                         && !std::is_floating_point< T >::value
                                         && !std::is_same< T, bool >::value >;

template< class T >
using IsFloatingPoint = typename std::enable_if_t< std::is_floating_point< T >::value >;

template< class T >
using IsBool = typename std::enable_if_t< std::is_same< T, bool >::value >;

template< class T >
using IsString = typename std::enable_if_t< std::is_convertible< T, std::string >::value >;

}