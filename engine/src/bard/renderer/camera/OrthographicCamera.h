/*
 * \file OrthographicCamera.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 08.01.2021
 * \time : 15:26
 */

#pragma once

#include <glm/glm.hpp>

namespace bard
{

class OrthographicCamera
{
public:
    OrthographicCamera( float left, float right, float bottom, float top ) noexcept;

    void setProjection( float left, float right, float bottom, float top ) noexcept;
    void setPosition( const glm::vec3 & position ) noexcept;
    void setRotation( float rotation ) noexcept;

    const glm::vec3 & position() const noexcept;
    float rotation() const noexcept;
    const glm::mat4 & projectionMatrix() const noexcept;
    const glm::mat4 & viewMatrix() const noexcept;
    const glm::mat4 & viewProjectionMatrix() const noexcept;

private:
    void recalculateViewMatrix();

private:
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_viewProjectionMatrix;

    glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
    float m_rotation = 0.0f;
};

}
