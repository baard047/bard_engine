/*
 * \file Shared.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 12:12
 */

#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include <bard/auxiliary/FileIO.h>
#include <glm/glm.hpp>

namespace bard
{

class Shader
{
public:
    using Ptr = std::shared_ptr< Shader >;

public:
    static Shader::Ptr create( std::string name,
                               const std::string & vertexSrc,
                               const std::string & fragmentSrc);

    static Shader::Ptr create( const Aux::FileIO::FilePath & path );

    virtual ~Shader() = default;

    const std::string & name() const noexcept;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setInt( const std::string & name, int value ) = 0;
    virtual void setIntArray( const std::string & name, int * values, uint32_t count ) = 0;
    virtual void setFloat( const std::string & name, float value ) = 0;
    virtual void setFloat3( const std::string & name, const glm::vec3 & value ) = 0;
    virtual void setFloat4( const std::string & name, const glm::vec4 & value ) = 0;
    virtual void setMat4( const std::string & name, const glm::mat4 & matrix ) = 0;

private:
    template< class ... Args >
    static Shader::Ptr createImpl( Args && ... args );

protected:
    Shader() = default;
    explicit Shader( std::string name ) : m_name( std::move( name ) ) {}

    std::string m_name;
};

class ShaderLibrary
{
    using Storage = std::unordered_map< std::string, Shader::Ptr >;

public:
    void add( const std::string & name, Shader::Ptr shader );
    void add( Shader::Ptr shader );
    Shader::Ptr load( const Aux::FileIO::FilePath & filepath );
    Shader::Ptr load( const std::string & name, const Aux::FileIO::FilePath & filepath );

    Shader::Ptr get( const std::string & name );

    bool exists( const std::string & name ) const;

private:
    Storage m_shaders;
};

}