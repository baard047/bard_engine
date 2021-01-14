/*
 * \file RenderCommand.cpp
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 08.01.2021
 * \time : 12:37
 */

#include "RenderCommand.h"
#include <platform/openGL/RendererAPI.h>

namespace bard
{

//TODO create

std::unique_ptr< RendererAPI > RenderCommand::s_rendererAPI = std::make_unique< OpenGL::RendererAPI >();

}