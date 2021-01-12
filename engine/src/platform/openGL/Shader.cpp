/*
 * \file Shader.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 10.01.2021
 * \time : 13:33
 */

#include "Shader.h"
#include <bard/core/Base.h>

#include <glm/gtc/type_ptr.hpp>

namespace OpenGL
{

Shader::Shader( const Aux::FileIO::FilePath & path )
{
    auto bytes = Aux::FileIO::readFile( path );
    if( bytes )
    {
        auto sources = Parsing::ShaderParser::getSources( std::move( *bytes ) );
        m_name = Parsing::ShaderParser::getShaderName( path.c_str() );
        compileShaders( std::move( sources ) );
    }
    else { CORE_LOG_ERROR("Shader reading error! code: {0} path: {1}", bytes.getError(), path ); }
}

Shader::Shader( std::string name, const std::string & vertexSource, const std::string & fragmentSource )
        : bard::Shader( std::move( name ) )
{
    compileShaders( { { GL_VERTEX_SHADER,   vertexSource },
                      { GL_FRAGMENT_SHADER, fragmentSource } } );
}

Shader::~Shader()
{
    glDeleteProgram( m_program );
}

void Shader::bind() const
{
    glUseProgram( m_program );
}

void Shader::unbind() const
{
    glUseProgram( 0 );
}

void Shader::setInt( const std::string & name, int value )
{
    GLint location = glGetUniformLocation(m_program, name.c_str());
    glUniform1i(location, value);
}

void Shader::setIntArray( const std::string & name, int * values, uint32_t count )
{
    GLint location = glGetUniformLocation(m_program, name.c_str());
    glUniform1iv(location, count, values);
}

void Shader::setFloat( const std::string & name, float value )
{
    GLint location = glGetUniformLocation(m_program, name.c_str());
    glUniform1f(location, value);
}

void Shader::setFloat3( const std::string & name, const glm::vec3 & value )
{
    GLint location = glGetUniformLocation( m_program, name.c_str() );
    glUniform3f( location, value.x, value.y, value.z );
}

void Shader::setFloat4( const std::string & name, const glm::vec4 & value )
{
    GLint location = glGetUniformLocation(m_program, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setMat4( const std::string & name, const glm::mat4 & matrix )
{
    GLint location = glGetUniformLocation( m_program, name.c_str() );
    glUniformMatrix4fv( location, 1, GL_FALSE, glm::value_ptr( matrix ) );
}

void Shader::compileShaders( Shader::Sources && shaderSources ) noexcept
{
    BARD_CONDITION_ERROR(shaderSources.size() > 2, "We only support 2 shaders for now", return );

    GLuint program = glCreateProgram();
    std::array< GLenum, 2 > glShaderIDs{};

    int glShaderIDIndex = 0;
    for( const auto &[type, source] : shaderSources )
    {
        GLuint shader = glCreateShader( type );

        const GLchar * sourceCStr = source.c_str();
        glShaderSource( shader, 1, &sourceCStr, nullptr );

        glCompileShader( shader );

        GLint isCompiled = 0;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &isCompiled );
        if( isCompiled == GL_FALSE )
        {
            GLint maxLength = 0;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

            std::vector< GLchar > infoLog( maxLength );
            glGetShaderInfoLog( shader, maxLength, &maxLength, &infoLog[ 0 ] );

            glDeleteShader( shader );

            BARD_CONDITION_ERROR( true, infoLog.data(), break );
        }

        glAttachShader( program, shader );
        glShaderIDs[ glShaderIDIndex++ ] = shader;
    }

    m_program = program;
    glLinkProgram( program );

    GLint isLinked = 0;
    glGetProgramiv( program, GL_LINK_STATUS, ( int * ) &isLinked );
    if( isLinked == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

        // The maxLength includes the NULL character
        std::vector< GLchar > infoLog( maxLength );
        glGetProgramInfoLog( program, maxLength, &maxLength, &infoLog[ 0 ] );

        // We don't need the program anymore.
        glDeleteProgram( program );
        for( auto id : glShaderIDs ) { glDeleteShader( id ); }

        BARD_CONDITION_ERROR( true, infoLog.data(), return );
    }

    for( auto id : glShaderIDs )
    {
        glDetachShader( program, id );
        glDeleteShader( id );
    }
}

}