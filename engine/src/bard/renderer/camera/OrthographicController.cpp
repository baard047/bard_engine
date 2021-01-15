/*
 * \file Controller.cpp.cc
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 09.01.2021
 * \time : 18:17
 */

#include "OrthographicController.h"

#include <bard/events/Buss.h>
#include <bard/core/Input.h>

#include <cmath>

namespace bard {

CameraController::CameraController( float aspectRatio, bool rotation )
        : m_aspectRatio( aspectRatio ),
          m_camera( -m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel,
                    -m_zoomLevel, m_zoomLevel ),
          m_rotation( rotation )
{
    //TODO maybe forbid this and let only "camera holders" to subscribe
    Events::Buss::get().subscribe( this, &CameraController::onMouseScrolled );
    Events::Buss::get().subscribe( this, &CameraController::onWindowResized );
}

void CameraController::onUpdate( bard::Timestep ts )
{
    if( Input::isKeyPressed( Key::A ) )
    {
        m_cameraPosition.x -= cos( glm::radians( m_cameraRotation ) ) * m_cameraTranslationSpeed * ts;
        m_cameraPosition.y -= sin( glm::radians( m_cameraRotation ) ) * m_cameraTranslationSpeed * ts;
    }
    else if( Input::isKeyPressed( Key::D ) )
    {
        m_cameraPosition.x += cos( glm::radians( m_cameraRotation ) ) * m_cameraTranslationSpeed * ts;
        m_cameraPosition.y += sin( glm::radians( m_cameraRotation ) ) * m_cameraTranslationSpeed * ts;
    }

    if( Input::isKeyPressed( Key::W ) )
    {
        m_cameraPosition.x += -sin( glm::radians( m_cameraRotation ) ) * m_cameraTranslationSpeed * ts;
        m_cameraPosition.y += cos( glm::radians( m_cameraRotation ) ) * m_cameraTranslationSpeed * ts;
    }
    else if( Input::isKeyPressed( Key::S ) )
    {
        m_cameraPosition.x -= -sin( glm::radians( m_cameraRotation ) ) * m_cameraTranslationSpeed * ts;
        m_cameraPosition.y -= cos( glm::radians( m_cameraRotation ) ) * m_cameraTranslationSpeed * ts;
    }

    if( m_rotation )
    {
        if( Input::isKeyPressed( Key::Q ) )
        {
            m_cameraRotation += m_cameraRotationSpeed * ts;
        }
        if( Input::isKeyPressed( Key::E ) )
        {
            m_cameraRotation -= m_cameraRotationSpeed * ts;
        }

        if( m_cameraRotation > 180.0f )
        {
            m_cameraRotation -= 360.0f;
        }
        else if( m_cameraRotation <= -180.0f )
        {
            m_cameraRotation += 360.0f;
        }

        m_camera.setRotation( m_cameraRotation );
    }

    m_camera.setPosition( m_cameraPosition );

    m_cameraTranslationSpeed = m_zoomLevel;
}

void CameraController::resize( float width, float height )
{
    m_aspectRatio = width / height;
    setCameraProjection();
}

OrthographicCamera & CameraController::getCamera() noexcept
{
    return m_camera;
}

const OrthographicCamera & CameraController::getCamera() const noexcept
{
    return m_camera;
}

float CameraController::getZoomLevel() const noexcept
{
    return m_zoomLevel;
}

void CameraController::setZoomLevel( float level ) noexcept
{
    m_zoomLevel = level;
}

bool CameraController::onMouseScrolled( Events::MouseScrolled & event )
{
    const float zoomSpeed = Input::isKeyPressed( Key::LeftAlt ) ? 1.5f : 0.25f;

    m_zoomLevel -= event.yOffset * zoomSpeed;
    m_zoomLevel = std::max( m_zoomLevel, 0.25f );
    setCameraProjection();

    return false;
}

bool CameraController::onWindowResized( Events::WindowResize & event )
{
    resize( static_cast<float >(event.width), static_cast<float >(event.height) );

    return false;
}

void CameraController::setCameraProjection() noexcept
{
    m_camera.setProjection( -m_aspectRatio * m_zoomLevel,
                            m_aspectRatio * m_zoomLevel,
                            -m_zoomLevel,
                            m_zoomLevel );
}

}