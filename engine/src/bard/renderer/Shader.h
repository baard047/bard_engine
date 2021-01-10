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

    virtual ~Shader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setInt( const std::string & name, int value ) = 0;
    virtual void setIntArray( const std::string & name, int * values, uint32_t count ) = 0;
    virtual void setFloat( const std::string & name, float value ) = 0;
    virtual void setFloat3( const std::string & name, const glm::vec3 & value ) = 0;
    virtual void setFloat4( const std::string & name, const glm::vec4 & value ) = 0;
    virtual void setMat4( const std::string & name, const glm::mat4 & matrix ) = 0;

protected:
    explicit Shader( std::string name ) : m_name( std::move( name ) ) {}

    std::string m_name;
};

}