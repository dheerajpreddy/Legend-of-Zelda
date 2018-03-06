#include "camera.h"
#include "main.h"
#include "cuboid.h"

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

void Camera::update(Boat boat, int camView) {
    if(camView == 0) {
      // Follow view
      this->set_up(0, 1, 0);
      this->set_target(boat.position.x, this->target.y, boat.position.z);
      this->set_eye(boat.position.x + 15*cos(boat.rotation.y * M_PI / 180.0f), 10, boat.position.z - 15*sin(boat.rotation.y * M_PI / 180.0f));
    } else if (camView == 1) {
      // First person view
      this->set_up(0, 1, 0);
      this->set_target(boat.position.x - 10*cos(boat.rotation.y * M_PI / 180.0f), this->target.y, boat.position.z + 10*sin(boat.rotation.y * M_PI / 180.0f));
      this->set_eye(boat.position.x - 4*cos(boat.rotation.y * M_PI / 180.0f), boat.position.y, boat.position.z + 4*sin(boat.rotation.y * M_PI / 180.0f));
    } else if (camView == 2) {
      // Top view
      this->set_eye(boat.position.x, boat.position.y + 20, boat.position.z);
      this->set_target(boat.position.x, boat.position.y, boat.position.z);
      this->set_up(-cos(boat.rotation.y * M_PI / 180.0f), this->up.y, sin(boat.rotation.y * M_PI / 180.0f));
    } else if (camView == 3) {
      // Tower view
      this->set_up(0, 1, 0);
      this->set_target(boat.position.x, this->target.y, boat.position.z);
      this->set_eye(-10, 40, 10);
    } else if (camView == 4) {
      camView = 1;
    }
}
