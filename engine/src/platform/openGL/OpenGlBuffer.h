/*
 * \file OpenGlBuffer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:29
 */

#pragma once

#include <bard/renderer/Buffer.h>

namespace bard
{

class OpenGLVertexBuffer : public VertexBuffer
{
public:
    using RendererId = uint32_t;

public:
    OpenGLVertexBuffer( float * vertices, uint32_t size );
    ~OpenGLVertexBuffer() override;

    void bind() const override;
    void unbind() const override;

private:
    RendererId m_rendererID = 0;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
    OpenGLIndexBuffer( uint32_t * indices, uint32_t count );
    ~OpenGLIndexBuffer() override;

    void bind() const override;
    void unbind() const override;

    uint32_t getCount() const override { return m_count; }

private:
    OpenGLVertexBuffer::RendererId m_rendererID = 0;
    uint32_t m_count;
};

}
