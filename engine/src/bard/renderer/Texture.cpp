/*
 * \file Texture.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 10.01.2021
 * \time : 14:57
 */

#include "Texture.h"

#include <bard/renderer/Renderer.h>
#include <platform/openGL/Texture2D.h>

namespace bard
{

uint32_t Texture::width() const noexcept
{
    return m_width;
}

uint32_t Texture::height() const noexcept
{
    return m_height;
}

Texture::RendererID Texture::rendererID() const noexcept
{
    return m_rendererID;
}

Texture2D::Ptr Texture2D::create( uint32_t width, uint32_t height )
{
    switch ( Renderer::getAPI() )
    {
        case RendererAPI::API::None: BARD_CORE_ASSERT( false, "RendererAPI::None" ); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared< OpenGL::Texture2D>( width, height );
    }
    return nullptr;
}

Texture2D::Ptr Texture2D::create( const std::string & path )
{
    switch ( Renderer::getAPI() )
    {
        case RendererAPI::API::None: BARD_CORE_ASSERT( false, "RendererAPI::None" ); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared< OpenGL::Texture2D>( path );
    }
    return nullptr;
}

}