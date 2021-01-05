/*
 * \file GraphicsContext.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 05.01.2021
 * \time : 21:37
 */

#pragma once

namespace bard
{

class GraphicsContext
{
public:
    virtual ~GraphicsContext() = default;

    virtual void init() = 0;
    virtual void swapBuffers() = 0;
};

}