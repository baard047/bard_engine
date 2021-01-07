/*
 * \file VertexArray.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 07.01.2021
 * \time : 22:14
 */

#pragma once

#include <bard/renderer/VertexArray.h>

namespace bard::OpenGL {

class VertexArray : public Base::VertexArray
{
    using VertexArrayObject = uint32_t;

public:
    VertexArray();
    ~VertexArray() override;

    void bind() const override;
    void unbind() const override;

    void addVertexBuffer( const VertexBuffer::Ptr & vertexBuffer ) override;
    void setIndexBuffer( const IndexBuffer::Ptr & indexBuffer ) override;

    const VertexBuffers & getVertexBuffers() const override;
    const IndexBuffer::Ptr & getIndexBuffer() const override;

private:
    VertexBuffers m_vertexBuffers;
    IndexBuffer::Ptr m_indexBuffer;
    VertexArrayObject m_buffer;
};

}