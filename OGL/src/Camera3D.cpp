#include	"Camera3D.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
    cameraPos = position;
    cameraTarget = target;
    this->up = up;
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
    return view;
}

void Camera::SetPosition(const glm::vec3& position) {
    cameraPos = position;
    UpdateCameraVectors();
}

void Camera::SetTarget(const glm::vec3& target) {
    cameraTarget = target;
    UpdateCameraVectors();
}

void Camera::SetUp(const glm::vec3& up) {
    cameraUp = up;
    UpdateCameraVectors();
}
void Camera::Move(const glm::vec3& direction, float speed)
{
    cameraPos += direction * speed;
    UpdateCameraVectors();
}
void Camera::Rotate(float yaw, float pitch)
{
    this->yaw += yaw;
    this->pitch += pitch;

    // Constrain the pitch angle to prevent flipping
    if (this->pitch > 89.0f) this->pitch = 89.0f;
    if (this->pitch < -89.0f) this->pitch = -89.0f;

    UpdateCameraVectors();
}
void Camera::UpdateCameraVectors() {

    // Calculate the new direction vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirection = glm::normalize(front);

    // Recalculate the right and up vectors
    cameraRight = glm::normalize(glm::cross(cameraDirection, up));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraDirection));

    // Update the view matrix
    view = glm::lookAt(cameraPos+ cameraUp, cameraPos + cameraDirection, cameraUp);
}
