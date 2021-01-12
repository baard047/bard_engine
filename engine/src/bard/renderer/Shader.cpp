/*
 * \file Shared.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 12:12
 */

#include "Shader.h"
#include <bard/renderer/Renderer.h>
#include <platform/openGL/Shader.h>

namespace bard {

Shader::Ptr Shader::create( std::string name, const std::string & vertexSrc, const std::string & fragmentSrc )
{
    return createImpl( std::move( name ), vertexSrc, fragmentSrc );
}

Shader::Ptr Shader::create( const Aux::FileIO::FilePath & path )
{
    return createImpl( path );
}

template< class... Args >
Shader::Ptr Shader::createImpl( Args && ... args )
{
    switch ( Renderer::getAPI() )
    {
        case RendererAPI::API::None:
            BARD_CORE_ASSERT( false, "RendererAPI::None" ); return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared< OpenGL::Shader>( std::forward<Args>( args )... );
    }

    return nullptr;
}
}