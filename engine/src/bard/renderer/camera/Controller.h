/*
 * \file Controller.h
 * \copyright (C) 2021 Special Technological Center Ltd
 * \author : Bardashevsky A.K.
 * \date : 09.01.2021
 * \time : 18:17
 */

#pragma once

#include "OrthographicCamera.h"

#include <bard/events/ApplicationEvent.h>
#include <bard/events/MouseEvent.h>
#include <bard/core/Timestep.h>

namespace bard {

class CameraController
{
public:
    explicit CameraController( float aspectRatio, bool rotation = false );

    void onUpdate( bard::Timestep ts );
    void resize( float width, float height );

    OrthographicCamera & getCamera() noexcept;
    const OrthographicCamera & getCamera() const noexcept;
    float getZoomLevel() const noexcept;

    void setZoomLevel( float level ) noexcept;

private:
    bool onMouseScrolled( Events::MouseScrolled & event );
    bool onWindowResized( Events::WindowResize & event );

    void setCameraProjection() noexcept;

private:
    float m_aspectRatio;
    float m_zoomLevel = 1.0f;
    OrthographicCamera m_camera;

    bool m_rotation;
    glm::vec3 m_cameraPosition = { 0.0f, 0.0f, 0.0f };
    float m_cameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
    float m_cameraTranslationSpeed = 5.f;
    float m_cameraRotationSpeed = 180.0f;
};

}



