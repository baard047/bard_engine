/*
 * \file Layer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 03.01.2021
 * \time : 15:20
 */

#pragma once

#include "Base.h"
#include <bard/core/Timestep.h>

namespace bard
{

class Layer
{
public:
    explicit Layer( std::string layerName = "Layer" )
            : m_debugName( std::move( layerName ) ) { }

    virtual ~Layer() = default;

    virtual void onAttach() {}
    virtual void onDetach() {}

    virtual void onUpdate( Timestep ) {}
    virtual void onRender() {}

    virtual void onImGuiRender() {}

    inline const std::string & getName() const { return m_debugName; }

protected:
    std::string m_debugName;
};

}