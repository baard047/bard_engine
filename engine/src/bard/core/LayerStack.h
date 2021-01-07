/*
 * \file LayerStack.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 03.01.2021
 * \time : 15:22
 */

#pragma once

#include "Layer.h"

namespace bard
{

class LayerStack
{
private:
    using Layers = std::vector< Layer * >;

public:
    LayerStack();
    ~LayerStack();

    void pushLayer( Layer * layer );
    void pushOverlay( Layer * overlay );
    void popLayer( Layer * layer );
    void popOverlay( Layer * overlay );

public:
    Layers::iterator begin() { return m_layers.begin(); }
    Layers::iterator end() { return m_layers.end(); }
    Layers::const_iterator begin() const { return m_layers.cbegin(); }
    Layers::const_iterator end() const { return m_layers.cend(); }

    Layers::reverse_iterator rbegin() { return m_layers.rbegin(); }
    Layers::reverse_iterator rend() { return m_layers.rend(); }
    Layers::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
    Layers::const_reverse_iterator rend() const { return m_layers.rend(); }

private:
    Layers m_layers;
    uint32_t m_layerInsertIndex;
};

}
