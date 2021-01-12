/*
 * \file ShaderParser.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 12.01.2021
 * \time : 9:44
 */

#pragma once

#include <unordered_map>
#include <string>

#include <bard/auxiliary/FileIO.h>

#include <glad/glad.h>

namespace OpenGL::Parsing {

struct ShaderParser
{
    using ShaderType = GLenum;
    using Sources = std::unordered_map< ShaderType, std::string >;

    static Sources getSources( Aux::FileIO::Bytes && raw ) noexcept;
    static std::string getShaderName( std::string_view pathString ) noexcept;
};

}