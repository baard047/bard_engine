/*
 * \file Texture2D.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 10.01.2021
 * \time : 14:57
 */

#include "Texture2D.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <bard/core/Base.h>

namespace OpenGL
{

Texture2D::Texture2D( uint32_t width, uint32_t height )
{
    m_width = width;
    m_height = height;

    m_InternalFormat = GL_RGBA8;
    m_DataFormat = GL_RGBA;

    glCreateTextures( GL_TEXTURE_2D, 1, &m_rendererID );
    glTextureStorage2D( m_rendererID, 1, m_InternalFormat, m_width, m_height );

    glTextureParameteri( m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTextureParameteri( m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    glTextureParameteri( m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTextureParameteri( m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT );
}

Texture2D::Texture2D( std::string path )
        : m_path( std::move( path ) )
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc * data = stbi_load(m_path.c_str(), &width, &height, &channels, 0);
    if( !data )
    {
        CORE_LOG_ERROR( "Cant load image " + m_path );
        BARD_CORE_ASSERT(false, "" );
        return;
    }

    m_width = width;
    m_height = height;

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    m_InternalFormat = internalFormat;
    m_DataFormat = dataFormat;

    BARD_CORE_ASSERT( ( internalFormat & dataFormat ), "Format not supported!");

    glCreateTextures( GL_TEXTURE_2D, 1, &m_rendererID );
    glTextureStorage2D( m_rendererID, 1, internalFormat, m_width, m_height );

    glTextureParameteri( m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTextureParameteri( m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    glTextureParameteri( m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTextureParameteri( m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTextureSubImage2D( m_rendererID, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data );

    stbi_image_free( data );
}

Texture2D::~Texture2D()
{
    glDeleteTextures( 1, &m_rendererID );

}

void Texture2D::bind( uint32_t slot ) const
{
    glBindTextureUnit( slot, m_rendererID );
}

}