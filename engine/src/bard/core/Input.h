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

namespace bard
{

class Input
{
public:
    static bool isKeyPressed( KeyCode key);

    static bool isMouseButtonPressed( MouseCode button);
    //TODO temp, use glm::vec2 later
    static std::pair<float, float> getMousePosition();
    static float getMouseX();
    static float getMouseY();
};

}