/*
 * \file ApplicationEvent.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 27.12.2020
 * \time : 22:02
 */

#pragma once

#include "Event.h"

namespace bard::Events {

struct WindowResize : public Event
{
    EVENT_CLASS_TYPE( Type::WindowResize )
    EVENT_CLASS_CATEGORY( Category::Application )

    WindowResize( uint32_t width, uint32_t height )
            : width( width ), height( height ) { }

    const uint32_t width;
    const uint32_t height;

    std::string toString() const override
    {
        std::stringstream stream;
        stream << "WindowResize: " << width << ", " << height;
        return stream.str();
    }
};

struct WindowClose : public Event
{
    EVENT_CLASS_TYPE( Type::WindowClose )
    EVENT_CLASS_CATEGORY( Category::Application )
};

struct AppTick : public Event
{
    EVENT_CLASS_TYPE( Type::AppTick )
    EVENT_CLASS_CATEGORY( Category::Application)
};

struct AppRender : public Event
{
    EVENT_CLASS_TYPE( Type::AppRender )
    EVENT_CLASS_CATEGORY( Category::Application )
};

}
