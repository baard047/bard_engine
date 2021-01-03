/*
 * \file Key.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 27.12.2020
 * \time : 22:01
 */

#pragma once

#include "Event.h"

namespace bard::Events {

struct Key : public Event
{
    EVENT_CLASS_CATEGORY( Category::Keyboard | Category::Input )
    const int keycode;

protected:
    explicit Key( int keycode) : keycode( keycode ) {}
};

struct KeyPressed : public Key
{
    EVENT_CLASS_TYPE( Type::KeyPressed )
    const int repeatCount;

    KeyPressed( int keycode, int repeatCount )
            : Key( keycode ), repeatCount( repeatCount ) { }

    std::string toString() const override
    {
        std::stringstream stream;
        stream << "KeyPressed: " << keycode << " (" << repeatCount << " repeats)";
        return stream.str();
    }
};

struct KeyReleased : public Key
{
    EVENT_CLASS_TYPE( Type::KeyReleased )
    explicit KeyReleased( int keycode ) : Key( keycode ) { }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyReleased: " << keycode;
        return ss.str();
    }
};

struct KeyTyped : public Key
{
    EVENT_CLASS_TYPE( Type::KeyTyped )
    explicit KeyTyped( int keycode) : Key( keycode ) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyTyped: " << keycode;
        return ss.str();
    }
};

}