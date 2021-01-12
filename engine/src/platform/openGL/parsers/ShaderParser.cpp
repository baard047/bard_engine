/*
 * \file ShaderParser.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 12.01.2021
 * \time : 9:44
 */

#include "ShaderParser.h"

#include <bard/core/Base.h>

namespace OpenGL::Parsing {

namespace {
constexpr const auto TYPE = "#type";
constexpr const auto VERTEX = "vertex";
constexpr const auto FRAGMENT = "fragment";
constexpr const auto PIXEL = "pixel";

GLenum convertType( std::string_view type)
{
    if (type == VERTEX) { return GL_VERTEX_SHADER; }
    if ( type == FRAGMENT || type == PIXEL ) { return GL_FRAGMENT_SHADER; }

    BARD_CONDITION_ERROR(true, "Unknown shader type" + std::string{ type.data() }, return 0 );
}

}

ShaderParser::Sources ShaderParser::getSources( Aux::FileIO::Bytes && source ) noexcept
{
    Sources shaderSources;

    size_t typeTokenLength = strlen(TYPE);
    size_t pos = source.find(TYPE, 0); //Start of shader type declaration line
    while (pos != std::string::npos)
    {
        size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
        BARD_CONDITION_ERROR( eol == std::string::npos, "Syntax error!", break );

        size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
        BARD_CONDITION_ERROR( nextLinePos == std::string::npos, "Syntax error!", break );

        size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
        auto glType = convertType( source.substr(begin, eol - begin) );
        if( glType != 0 )
        {
            pos = source.find(TYPE, nextLinePos); //Start of next shader type declaration line

            shaderSources[ glType ] = ( pos == std::string::npos ) ? source.substr( nextLinePos )
                                                                   : source.substr( nextLinePos, pos - nextLinePos );
        }
    }

    return shaderSources;
}

std::string ShaderParser::getShaderName( std::string_view pathString ) noexcept
{
    auto lastSlash = pathString.find_last_of( "/\\");
    lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
    auto lastDot = pathString.rfind( '.' );
    auto count = lastDot == std::string::npos ? pathString.size() - lastSlash : lastDot - lastSlash;
    return std::string{ pathString.substr( lastSlash, count) };
}

}