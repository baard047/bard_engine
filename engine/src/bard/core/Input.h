/*
 * \file Input.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 05.01.2021
 * \time : 14:48
 */

#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

#include <utility>
#include <glm/vec2.hpp>

namespace bard
{

class Input
{
public:
    //NOTE: definitions need to be done by a platform
    static bool isKeyPressed( KeyCode key);
    static bool isMouseButtonPressed( MouseCode button);
    static glm::vec2 getMousePosition();
    static float getMouseX();
    static float getMouseY();
};

}