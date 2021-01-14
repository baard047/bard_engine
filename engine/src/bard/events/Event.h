/*
 * \file Event.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 25.12.2020
 * \time : 18:26
 */

#pragma once

#include "Types.h"

#include <string>
#include <ostream>
#include <sstream>

namespace bard::Events {

struct Event
{
    constexpr const static Type staticType = Type::None;
    constexpr const static int staticCategory = Category::None;

    template< class EventT >
    inline bool isInCategory() const
    {
        return staticCategory & EventT::staticCategory;
    }

    bool handled = false;
};

#define EVENT_CLASS_TYPE( type ) constexpr static const Type staticType = type;
#define EVENT_CLASS_CATEGORY( category ) constexpr static const int staticCategory = category;

}