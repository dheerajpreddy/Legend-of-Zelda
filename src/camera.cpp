#include "camera.h"
#include "main.h"

Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up) {
    this->eye = eye;
    this->target = target;
    this->up = up;
}

void Camera::set_eye(float x, float y, float z) {
    this->eye = glm::vec3(x, y, z);
}
void Camera::set_target(float x, float y, float z) {
    this->target = glm::vec3(x, y, z);
}
void Camera::set_up(float x, float y, float z) {
    this->up = glm::vec3(x, y, z);
}

void Camera::update_eye(float x, float y, float z) {
    this->eye += glm::vec3(x, y, z);
}
void Camera::update_target(float x, float y, float z) {
    this->target += glm::vec3(x, y, z);
}
void Camera::update_up(float x, float y, float z) {
    this->up += glm::vec3(x, y, z);
}
