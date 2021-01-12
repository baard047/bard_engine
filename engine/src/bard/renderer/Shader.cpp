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

const std::string & Shader::name() const noexcept
{
    return m_name;
}

/* *********************************** */

void ShaderLibrary::add( const std::string & name, Shader::Ptr shader )
{
    BARD_CONDITION_ERROR( exists( name ), "Shader " + name + " already exists!", return );
    m_shaders.emplace( name, std::move( shader ) );
}

void ShaderLibrary::add( Shader::Ptr shader )
{
    BARD_CONDITION_ERROR( exists( shader->name() ), "Shader " + shader->name() + " already exists!", return );
    m_shaders.emplace( shader->name(), std::move( shader ) );
}

Shader::Ptr ShaderLibrary::load( const Aux::FileIO::FilePath & filepath )
{
    auto shader = Shader::create( filepath );
    BARD_CONDITION_ERROR( exists( shader->name() ), "Shader " + shader->name() + " already exists!", return{} );
    auto it = m_shaders.emplace( shader->name(), std::move( shader ) );
    return it.first->second;
}

Shader::Ptr ShaderLibrary::load( const std::string & name, const Aux::FileIO::FilePath & filepath )
{
    auto shader = Shader::create( filepath );
    BARD_CONDITION_ERROR( exists( name ), "Shader " + name + " already exists!", return{} );
    auto it = m_shaders.emplace( name, std::move( shader ) );
    return it.first->second;
}

Shader::Ptr ShaderLibrary::get( const std::string & name )
{
    auto it = m_shaders.find( name );
    return it != m_shaders.end() ? it->second : nullptr;
}

bool ShaderLibrary::exists( const std::string & name ) const
{
    return m_shaders.find( name ) != m_shaders.end();
}

}
