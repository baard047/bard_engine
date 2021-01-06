/*
 * \file Buffer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:18
 */

#pragma once

#include "Layout.h"

namespace bard {

class VertexBuffer
{
public:
    static VertexBuffer * create( float * vertices, uint32_t size );

    virtual ~VertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    inline const BufferLayout & layout() const noexcept { return m_layout; }
    inline void setLayout( BufferLayout && layout ) noexcept { m_layout = std::move( layout ); }

    template< class ... Args >
    void setLayout( Args && ... args )
    {
        m_layout = { std::forward< Args >( args ) ... };
    }

private:
    BufferLayout m_layout;
};

class IndexBuffer
{
public:
    static IndexBuffer * create( uint32_t * indices, uint32_t count );

    virtual ~IndexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual uint32_t getCount() const = 0;
};

}
