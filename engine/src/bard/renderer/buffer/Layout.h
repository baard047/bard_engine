/*
 * \file Layout.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 19:01
 */

#pragma once

#include "Element.h"

namespace bard
{

class BufferLayout
{
    using Elements = std::vector< BufferElement >;

public:
    BufferLayout() = default;
    BufferLayout( BufferLayout && ) noexcept = default;
    BufferLayout & operator =( BufferLayout && ) noexcept = default;

    BufferLayout( std::initializer_list< BufferElement > elements )
            : m_elements( elements )
    {
        calculateOffsetsAndStride();
    }

    inline uint32_t getStride() const { return m_stride; }

    inline size_t size() const { return m_elements.size(); }

public:
    inline const BufferElement & operator[]( size_t index ) const
    {
        BARD_CORE_ASSERT( ( index < m_elements.size() ), "Out of bounds!" );
        return m_elements[ index ];
    }

    inline BufferElement & operator[]( size_t index )
    {
        BARD_CORE_ASSERT( ( index < m_elements.size() ), "Out of bounds!" );
        return m_elements[ index ];
    }

    Elements::iterator begin() { return m_elements.begin(); }
    Elements::iterator end() { return m_elements.end(); }
    Elements::const_iterator begin() const { return m_elements.cbegin(); }
    Elements::const_iterator end() const { return m_elements.cend(); }

private:
    void calculateOffsetsAndStride()
    {
        size_t offset = 0;
        m_stride = 0;
        for ( auto & element : m_elements )
        {
            element.offset = offset;
            offset += element.size;
            m_stride += element.size;
        }
    }

private:
    Elements m_elements;
    uint32_t m_stride = 0;
};

}