#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);

    glm::mat4 GetViewMatrix() const;
    void SetPosition(const glm::vec3& position);

    void SetTarget(const glm::vec3& target);

    void SetUp(const glm::vec3& up);
    void Move(const glm::vec3& direction, float speed);

    void Rotate(float yaw, float pitch);
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraTarget;
    glm::vec3 cameraDirection;
    glm::vec3 cameraRight;
    glm::vec3 cameraUp;
    glm::mat4 view;
    glm::vec3 up;
    float yaw = -90.0f; // Initialize to face towards -Z
    float pitch = 0.0f;

    void UpdateCameraVectors();
};
