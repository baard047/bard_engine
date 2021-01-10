/*
 * \file Shader.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 10.01.2021
 * \time : 13:33
 */

#pragma once

#include <bard/renderer/Shader.h>

namespace OpenGL {

class Shader : public bard::Shader
{
public:
    Shader( std::string name,
            const std::string &vertexSrc, const std::string & fragmentSrc );
    ~Shader() override;

    void bind() const override;
    void unbind() const override;

    void setInt( const std::string & name, int value ) override;
    void setIntArray( const std::string & name, int * values, uint32_t count ) override;
    void setFloat( const std::string & name, float value ) override;
    void setFloat3( const std::string & name, const glm::vec3 & value ) override;
    void setFloat4( const std::string & name, const glm::vec4 & value ) override;
    void setMat4( const std::string & name, const glm::mat4 & matrix ) override;

private:
    uint32_t m_program;
};

}
