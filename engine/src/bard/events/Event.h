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
    //TODO rm all virtual methods
    virtual int categoryFlags() const = 0;

    virtual std::string toString() const { return name(); }
    virtual const char * name() const = 0;

    inline bool isInCategory( Category category ) const
    {
        return categoryFlags() & category;
    }

    bool handled = false;
};

inline std::ostream & operator <<( std::ostream & os, const Event & e )
{
    return os << e.toString();
}

#define EVENT_CLASS_TYPE(type) constexpr static const Type staticType = type; \
                               virtual const char * name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) int categoryFlags() const override { return category; }

}