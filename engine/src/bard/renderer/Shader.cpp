/*
 * \file Shared.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 12:12
 */

#include "Shader.h"
#include <bard/core/Base.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace bard {

Shader::Shader( const std::string & vertexSource, const std::string & fragmentSource )
{
    ///NOTE: from https://www.khronos.org/opengl/wiki/Shader_Compilation#Example

// Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

// Send the vertex shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
    auto source = ( const GLchar * ) vertexSource.c_str();
    glShaderSource( vertexShader, 1, &source, nullptr );

// Compile the vertex shader
    glCompileShader( vertexShader );

    GLint isCompiled = 0;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &isCompiled );
    if( isCompiled == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetShaderiv( vertexShader, GL_INFO_LOG_LENGTH, &maxLength );

        // The maxLength includes the NULL character
        std::vector< GLchar > infoLog( maxLength );
        glGetShaderInfoLog( vertexShader, maxLength, &maxLength, &infoLog[ 0 ] );

        // We don't need the shader anymore.
        glDeleteShader( vertexShader );
        CORE_LOG_ERROR( "Vertex shared compilation failure! Reason: {0}", infoLog.data() );
        BARD_CORE_ASSERT( false, "Vertex shared compilation failure!" );
        return;
    }

// Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

// Send the fragment shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
    source = ( const GLchar * ) fragmentSource.c_str();
    glShaderSource( fragmentShader, 1, &source, nullptr );

// Compile the fragment shader
    glCompileShader( fragmentShader );

    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &isCompiled );
    if( isCompiled == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetShaderiv( fragmentShader, GL_INFO_LOG_LENGTH, &maxLength );

        // The maxLength includes the NULL character
        std::vector< GLchar > infoLog( maxLength );
        glGetShaderInfoLog( fragmentShader, maxLength, &maxLength, &infoLog[ 0 ] );

        // We don't need the shader anymore.
        glDeleteShader( fragmentShader );
        // Either of them. Don't leak shaders.
        glDeleteShader( vertexShader );

        CORE_LOG_ERROR( "Fragment shared compilation failure! Reason: {0}", infoLog.data() );
        BARD_CORE_ASSERT( false, "Fragment shared compilation failure!" );
        return;
    }

// Vertex and fragment shaders are successfully compiled.
// Now time to link them together into a program.
// Get a m_program object.
    m_program = glCreateProgram();

// Attach our shaders to our program
    glAttachShader( m_program, vertexShader );
    glAttachShader( m_program, fragmentShader );

// Link our program
    glLinkProgram( m_program );

// Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv( m_program, GL_LINK_STATUS, ( int * ) &isLinked );
    if( isLinked == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetProgramiv( m_program, GL_INFO_LOG_LENGTH, &maxLength );

        // The maxLength includes the NULL character
        std::vector< GLchar > infoLog( maxLength );
        glGetProgramInfoLog( m_program, maxLength, &maxLength, &infoLog[ 0 ] );

        // We don't need the m_program anymore.
        glDeleteProgram( m_program );
        // Don't leak shaders either.
        glDeleteShader( vertexShader );
        glDeleteShader( fragmentShader );

        CORE_LOG_ERROR( "Shader link failure! Reason: {0}", infoLog.data() );
        BARD_CORE_ASSERT( false, "Shader link failure!" );
        return;
    }

// Always detach shaders after a successful link.
    glDetachShader( m_program, vertexShader );
    glDetachShader( m_program, fragmentShader );
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

void Shader::setMat4( const std::string & name, const glm::mat4 & matrix )
{
    GLint location = glGetUniformLocation( m_program, name.c_str() );
    glUniformMatrix4fv( location, 1, GL_FALSE, glm::value_ptr( matrix ) );
}

}