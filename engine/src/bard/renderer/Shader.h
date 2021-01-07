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

namespace bard
{

class Shader
{
public:
    using Ptr = std::shared_ptr< Shader >;

public:
    Shader( const std::string &vertexSrc, const std::string & fragmentSrc );
    ~Shader();

    void bind() const;
    void unbind() const;

private:
    uint32_t m_rendererID;
};

}