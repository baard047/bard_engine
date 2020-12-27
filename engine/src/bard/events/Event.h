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

namespace bard::Events {

struct Event
{
    constexpr const static Type staticType = Type::None;
    virtual Type type() const = 0;
    virtual int32_t categoryFlags() const = 0

    virtual const char * name() const = 0;
    virtual std::string toString() const { return name(); }

    inline bool isInCategory(Category category)
    {
        return categoryFlags() & category;
    }

    bool handled = false;
};

inline std::ostream & operator <<( std::ostream & os, const Event & e )
{
    return os << e.toString();
}

#define EVENT_CLASS_TYPE(type) constexpr const static Type staticType = type;\
                               virtual Type type() const override { return staticType; } \
                               virtual const char* name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) int32_t categoryFlags() const override { return category; }

}