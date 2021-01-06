/*
 * \file Renderer.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 06.01.2021
 * \time : 15:43
 */

#pragma once

#include <cstdint>

namespace bard
{

enum class RendererAPI : uint_least8_t
{
    None = 0, OpenGL
};

class Renderer
{
public:
    //temporary
    static constexpr RendererAPI API = RendererAPI::OpenGL;
};


}
