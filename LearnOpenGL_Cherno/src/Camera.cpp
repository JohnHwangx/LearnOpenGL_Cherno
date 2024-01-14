#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	:m_Position(position), m_Up(up), m_Yaw(YAW), m_Pitch(pitch),
    m_CameraType(Camera_Type::ORBIT), 
    m_Zoom(ZOOM), 
	m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_MovementSpeed(SPEED), 
	m_MouseSensitivity(SENSITIVITY),
    m_WorldUp(up)
{
    updateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::CameraTranslation(Camera_Movement direction, float deltaTime)
{
    float velocity = m_MovementSpeed * deltaTime;
    if (direction == FORWARD)
        m_Position += m_Front * velocity;
    if (direction == BACKWARD)
        m_Position -= m_Front * velocity;

    if (direction == LEFT) {
        m_Position -= m_Right * velocity;
        m_Center -= m_Right * velocity;
    }
        
    if (direction == RIGHT) {
        m_Position += m_Right * velocity;
        m_Center += m_Right * velocity;
    }
}

void Camera::CameraRotation(float xoffset, float yoffset, bool constrainPitch)
{
    if (Camera_Type::ROAM == m_CameraType)
    {
        xoffset *= m_MouseSensitivity;
        yoffset *= m_MouseSensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if (m_Pitch < -89.0f)
                m_Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }
    else
    {
        xoffset *= m_MouseSensitivity;
        yoffset *= m_MouseSensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if (m_Pitch < -89.0f)
                m_Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }
}

void Camera::CameraYaw(float yaw)
{
    m_Yaw = yaw;
    updateCameraVectors();
}

void Camera::CameraPitch(float pitch, bool constrainPitch)
{
    m_Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    if (Camera_Type::ORBIT == m_CameraType) {

        return glm::lookAt(m_Position + (m_Front * m_Distance), m_Center, glm::vec3(0.0, 1.0, 0.0));
    }
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::SetCameraType(const Camera_Type type)
{
	m_CameraType = type;
}

void Camera::SetDistance(const float distance)
{
    m_Distance = distance;
}

void Camera::updateCameraVectors()
{
    if (m_CameraType == Camera_Type::ROAM) {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }
    else 
    {
        glm::vec3 front;
        front.x = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);

        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }
}
