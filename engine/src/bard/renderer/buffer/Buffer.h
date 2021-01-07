/*
 * \file Buffer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:18
 */

#pragma once

#include <memory>
#include "Layout.h"

namespace bard {
namespace Base {

class VertexBuffer
{
public:
    using Ptr = std::shared_ptr< VertexBuffer >;

public:
    static VertexBuffer::Ptr create( float * vertices, uint32_t size );
    static VertexBuffer::Ptr create( float * vertices, uint32_t size, BufferLayout && layout );

    virtual ~VertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    inline const BufferLayout & layout() const noexcept
    {
        return m_layout;
    }

    inline void setLayout( BufferLayout && layout ) noexcept
    {
        m_layout = std::move( layout );
    }

protected:
    BufferLayout m_layout;
};

class IndexBuffer
{
public:
    using Ptr = std::shared_ptr< IndexBuffer >;

public:
    static IndexBuffer::Ptr create( uint32_t * indices, uint32_t count );

    virtual ~IndexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual uint32_t getCount() const = 0;
};

}

using VertexBuffer = Base::VertexBuffer;
using IndexBuffer = Base::IndexBuffer;

}
