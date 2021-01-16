/*
 * \file OrthographicCamera.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 08.01.2021
 * \time : 15:26
 */

#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace bard
{

OrthographicCamera::OrthographicCamera( float left, float right, float bottom, float top ) noexcept
    : m_viewMatrix( 1.0f )
{
    setProjection( left, right, bottom, top );
}

void OrthographicCamera::setProjection( float left, float right, float bottom, float top ) noexcept
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::setPosition( const glm::vec3 & position ) noexcept
{
    if( m_position != position )
    {
        m_position = position;
        recalculateViewMatrix();
    }
}

void OrthographicCamera::setRotation( float rotation ) noexcept
{
    if( m_rotation != rotation )
    {
        m_rotation = rotation;
        recalculateViewMatrix();
    }
}

const glm::vec3 & OrthographicCamera::position() const noexcept
{
    return m_position;
}

float OrthographicCamera::rotation() const noexcept
{
    return m_rotation;
}

const glm::mat4 & OrthographicCamera::projectionMatrix() const noexcept
{
    return m_projectionMatrix;
}

const glm::mat4 & OrthographicCamera::viewMatrix() const noexcept
{
    return m_viewMatrix;
}

const glm::mat4 & OrthographicCamera::viewProjectionMatrix() const noexcept
{
    return m_viewProjectionMatrix;
}

void OrthographicCamera::recalculateViewMatrix()
{
    glm::mat4 transform = glm::translate( glm::mat4( 1.f ), m_position )
                          * glm::rotate( glm::mat4( 1.f ),
                                         glm::radians( m_rotation ),
                                         glm::vec3( 0.f, 0.f, 1.f ) );

    m_viewMatrix = glm::inverse( transform );
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

}