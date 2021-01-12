/*
 * \file FileIO.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 11.01.2021
 * \time : 13:02
 */

#pragma once

#include <fstream>
#include <string>
#include <streambuf>
#include <system_error>

#include "Expected.h"

namespace Aux::FileIO {

using Bytes = std::string;
using FilePath = std::string; //TODO std::filesystem::path ?

using InputStream = std::ifstream;
using OutputStream = std::ofstream;

using InputIterator = std::istreambuf_iterator< InputStream::char_type >;

Expected< Bytes, std::error_code > readFile( const FilePath & path ) noexcept;
std::error_code writeFile( std::string_view content, const FilePath & path ) noexcept;

}