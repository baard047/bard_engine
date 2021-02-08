/*
 * \file Texture2D.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 10.01.2021
 * \time : 14:57
 */

#pragma once

#include <bard/renderer/Texture.h>

namespace OpenGL
{

using GLenum = unsigned int;

class Texture2D : public bard::Texture2D
{
public:
    Texture2D( uint32_t width, uint32_t height );
    explicit Texture2D( std::string  path );

    ~Texture2D() override;

    void setData( void * data, uint32_t size ) override;

    void bind( uint32_t slot ) const override;

    bool operator ==( const Texture & other ) const override;

private:
    std::string m_path;
    GLenum m_InternalFormat, m_DataFormat;
};

}
