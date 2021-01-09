/*
 * \file Timestep.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 09.01.2021
 * \time : 19:05
 */

#pragma once

namespace bard {

class Timestep
{
public:
    explicit Timestep( float time = 0.0f )
            : m_Time( time )
    {
    }

    operator float() const { return m_Time; }

    float seconds() const { return m_Time; }
    float milliseconds() const { return m_Time * 1000.0f; }

private:
    float m_Time;
};

}