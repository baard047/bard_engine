/*
 * \file MouseEvent.h
 * \copyright (C) 2020 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 27.12.2020
 * \time : 22:02
 */

#pragma once

#include "Event.h"

namespace bard::Events {

struct MouseMoved : public Event
{
    EVENT_CLASS_TYPE( Type::MouseMoved )
    EVENT_CLASS_CATEGORY( Category::Mouse | Category::Input )

    MouseMoved( float x, float y ) : x( x ), y( y ) { }

    const float x;
    const float y;

    std::string toString() const override
    {
        std::stringstream stream;
        stream << "MouseMoved: " << x << ", " << y;
        return stream.str();
    }
};

struct MouseScrolled : public Event
{
    EVENT_CLASS_TYPE( Type::MouseScrolled )
    EVENT_CLASS_CATEGORY( Category::Mouse | Category::Input )

    MouseScrolled( float xOffset, float yOffset )
            : xOffset( xOffset ), yOffset( yOffset )
    {
    }

    const float xOffset;
    const float yOffset;

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolled: " << getXOffset() << ", " << getYOffset();
        return ss.str();
    }
};

struct MouseButton : public Event
{
    EVENT_CLASS_CATEGORY( Category::Mouse | Category::Input )
    const int button;

protected:
    explicit MouseButton( int button ) : button( button ) { }
};

struct MouseButtonPressed : public MouseButton
{
    EVENT_CLASS_TYPE( Type::MouseButtonPressed )
    explicit MouseButtonPressed( int button ) : MouseButton( button ) { }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressed: " << button;
        return ss.str();
    }
};

struct MouseButtonReleased : public MouseButton
{
    EVENT_CLASS_TYPE( Type::MouseButtonReleased )
    explicit MouseButtonReleased( int button) : MouseButton(button) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleased: " << m_button;
        return ss.str();
    }
};

}
