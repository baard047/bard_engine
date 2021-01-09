/*
 * \file VertexArray.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 07.01.2021
 * \time : 22:14
 */

#pragma once

#include <bard/renderer/VertexArray.h>

namespace OpenGL {

class VertexArray : public bard::VertexArray
{
    using VertexArrayObject = uint32_t;

public:
    VertexArray();
    ~VertexArray() override;

    void bind() const override;
    void unbind() const override;

    void addVertexBuffer( const bard::VertexBuffer::Ptr & vertexBuffer ) override;
    void setIndexBuffer( const bard::IndexBuffer::Ptr & indexBuffer ) override;

    const VertexBuffers & getVertexBuffers() const override;
    const bard::IndexBuffer::Ptr & getIndexBuffer() const override;

private:
    VertexBuffers m_vertexBuffers;
    bard::IndexBuffer::Ptr m_indexBuffer;
    VertexArrayObject m_buffer;
};

}