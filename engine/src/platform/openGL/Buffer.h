/*
 * \file OpenGlBuffer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:29
 */

#pragma once

#include <bard/renderer/buffer/Buffer.h>

namespace bard::OpenGL
{

using VertexBufferObject = uint32_t;

class VertexBuffer : public Base::VertexBuffer
{
public:
    VertexBuffer( float * vertices, uint32_t size );
    ~VertexBuffer() override;

    void bind() const override;
    void unbind() const override;

private:
    VertexBufferObject m_buffer = 0;
};

class IndexBuffer : public Base::IndexBuffer
{
public:
    IndexBuffer( uint32_t * indices, uint32_t count );
    ~IndexBuffer() override;

    void bind() const override;
    void unbind() const override;

    uint32_t getCount() const override { return m_count; }

private:
    VertexBufferObject m_buffer = 0;
    uint32_t m_count;
};

}
