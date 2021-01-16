/*
 * \file Texture.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 10.01.2021
 * \time : 14:57
 */

#pragma once

#include <cstdint>
#include <memory>

namespace bard
{

class Texture
{
public:
    using RendererID = uint32_t;

public:
    virtual ~Texture() = default;

    virtual void setData(void * data, uint32_t size) = 0;
    virtual void bind( uint32_t slot = 0 ) const = 0;

public:
    uint32_t width() const noexcept;
    uint32_t height() const noexcept;
    RendererID rendererID() const noexcept;

protected:
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    RendererID m_rendererID = 0;
};

class Texture2D : public Texture
{
public:
    using Ptr = std::shared_ptr< Texture2D >;

public:
    static Texture2D::Ptr create( uint32_t width, uint32_t height );
    static Texture2D::Ptr create( const std::string & path );
};

}
