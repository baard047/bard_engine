/*
 * \file LayerStack.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 03.01.2021
 * \time : 15:22
 */

#include "LayerStack.h"

namespace bard
{

LayerStack::LayerStack() : m_layerInsertIndex( 0 ) { }

LayerStack::~LayerStack()
{
    for( auto layer : m_layers ) { delete layer; }
}

void LayerStack::pushLayer( Layer * layer )
{
    m_layers.emplace( m_layers.begin() + m_layerInsertIndex, layer );
    m_layerInsertIndex++;
}

void LayerStack::pushOverlay( Layer * overlay )
{
    m_layers.emplace_back( overlay );
}

void LayerStack::popLayer( Layer * layer )
{
    auto it = std::find( m_layers.begin(), m_layers.end(), layer );
    if( it != m_layers.end() )
    {
        m_layers.erase( it );
        m_layerInsertIndex--;
    }
}

void LayerStack::popOverlay( Layer * overlay )
{
    auto it = std::find( m_layers.begin(), m_layers.end(), overlay );
    if( it != m_layers.end() )
    {
        m_layers.erase( it );
    }
}

}