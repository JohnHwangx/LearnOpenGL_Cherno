#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum Camera_Type {
	ORBIT,
	ROAM
};

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	~Camera();

	void CameraTranslation(Camera_Movement direction, float deltaTime);
	void CameraRotation(float xoffset, float yoffset, bool constrainPitch = true);
	void CameraYaw(float yaw);
	void CameraPitch(float pitch, bool constrainPitch = true);
	glm::mat4 GetViewMatrix() const;

	void SetCameraType(const Camera_Type type);
	void SetDistance(const float distance);

private:
	void updateCameraVectors();

private:
	Camera_Type m_CameraType;
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	// euler Angles
	float m_Yaw;
	float m_Pitch;
	// camera options
	float m_MovementSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

	float m_Distance = 3.0f;
};