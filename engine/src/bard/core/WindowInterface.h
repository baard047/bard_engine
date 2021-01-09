/*
 * \file Window.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 02.01.2021
 * \time : 14:54
 */

#pragma once

#include "Base.h"

namespace bard
{

class WindowInterface
{
public:
    using Ptr = std::unique_ptr< WindowInterface >;

public:
    struct Properties
    {
        Properties( std::string title, uint32_t width, uint32_t height )
         : title( std::move( title ) ), width( width ), height( height ) {}

        std::string title;
        uint32_t width;
        uint32_t height;
    };

public:
    virtual ~WindowInterface() = default;

    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;

    virtual void update() = 0;

    virtual void setVSync( bool enabled ) = 0;
    virtual bool isVSync() const = 0;

    virtual void * getNativeWindow() const = 0;
};

}