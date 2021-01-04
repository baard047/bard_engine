/*
 * \file Layer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 03.01.2021
 * \time : 15:20
 */

#pragma once

#include "Base.h"
#include <bard/events/Manager.h>

namespace bard
{

class Layer
{
public:
    explicit Layer( std::string layerName = "Layer" )
            : m_debugName( std::move( layerName ) ) { }

    virtual ~Layer() = default;

    inline void setEventBuss( Events::Manager::Ptr buss ) noexcept
    {
        m_eventBuss = std::move( buss );
        setupConnections();
    }

    //function to implement on client side.
    virtual void setupConnections() {}

    virtual void attach() {}
    virtual void detach() {}
    virtual void update() {}

    inline const std::string & getName() const { return m_debugName; }

protected:
    std::string m_debugName;
    Events::Manager::Ptr m_eventBuss;
};

}