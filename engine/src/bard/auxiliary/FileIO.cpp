/*
 * \file FileIO.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 11.01.2021
 * \time : 13:02
 */

#include "FileIO.h"

namespace Aux::FileIO {

Expected< Bytes, std::error_code > readFile( const FilePath & path ) noexcept
{
    InputStream stream;

    const auto mask = stream.exceptions() | std::ios::failbit | std::ios::badbit;
    stream.exceptions( mask );

    try
    {
        stream.open( path.c_str(), std::ios::in | std::ios::binary );
        stream.seekg( 0, std::ios::end );

        Bytes content;
        content.reserve( stream.tellg() );

        stream.seekg( 0, std::ios::beg );
        content.assign( InputIterator{ stream }, InputIterator{} );

        stream.close();

        return std::move( content );
    }
    catch ( const std::system_error & error )
    {
        auto code = error.code();
        return code;
    }
}

std::error_code writeFile( std::string_view content, const FilePath & path ) noexcept
{
    OutputStream stream;

    const auto mask = stream.exceptions() | std::ios::failbit | std::ios::badbit;
    stream.exceptions( mask );

    try
    {
        stream.open( path.c_str() );
        stream.write( content.data(), content.size() );
        return {};
    }
    catch ( const std::system_error & error )
    {
        auto code = error.code();
        return code;
    }
}

}