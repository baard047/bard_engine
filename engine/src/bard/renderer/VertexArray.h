/*
 * \file VertexArray.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 07.01.2021
 * \time : 21:48
 */

#pragma once

#include <vector>

#include "buffer/Buffer.h"

namespace bard
{
namespace Base
{

class VertexArray
{
public:
    using Ptr = std::shared_ptr< VertexArray >;
    using VertexBuffers = std::vector< VertexBuffer::Ptr >;

public:
    static VertexArray::Ptr create();
    virtual ~VertexArray() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void addVertexBuffer( const VertexBuffer::Ptr & vertexBuffer ) = 0;
    virtual void setIndexBuffer( const IndexBuffer::Ptr & indexBuffer ) = 0;

    virtual const VertexBuffers & getVertexBuffers() const = 0;
    virtual const IndexBuffer::Ptr & getIndexBuffer() const = 0;
};

}

using VertexArray = Base::VertexArray;

}
