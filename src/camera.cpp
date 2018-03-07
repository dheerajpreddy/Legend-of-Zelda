#include "camera.h"
#include "main.h"
#include "cuboid.h"
// #include "math.h"
int old_view = 0;

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

void Camera::update(GLFWwindow *window, Boat boat, int camView) {
    if(camView == 0) {
      // Follow view
      this->set_up(0, 1, 0);
      this->set_target(boat.position.x, this->target.y, boat.position.z);
      this->set_eye(boat.position.x + 15*cos(boat.rotation.y * M_PI / 180.0f), 10, boat.position.z - 15*sin(boat.rotation.y * M_PI / 180.0f));
    } else if (camView == 1) {
      // First person view
      this->set_up(0, 1, 0);
      this->set_target(boat.position.x - 10*cos(boat.rotation.y * M_PI / 180.0f), boat.position.y + 0.5, boat.position.z + 10*sin(boat.rotation.y * M_PI / 180.0f));
      this->set_eye(boat.position.x - 4*cos(boat.rotation.y * M_PI / 180.0f), boat.position.y , boat.position.z + 4*sin(boat.rotation.y * M_PI / 180.0f));
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
    double cursor_x, cursor_y;

    // if (!glfwGetKey(window, GLFW_KEY_F)) {
    //   old_view = camView;
    // } else {
    //   // camView = 0;
    //   // this->set_up(0, 1, 0);
    //   // this->set_target(boat.position.x - 10*cos(boat.rotation.y * M_PI / 180.0f), boat.position.y + 0.5, boat.position.z + 10*sin(boat.rotation.y * M_PI / 180.0f));
    //   // this->set_eye(boat.position.x - 4*cos(boat.rotation.y * M_PI / 180.0f), boat.position.y , boat.position.z + 4*sin(boat.rotation.y * M_PI / 180.0f));
    //
    //   glfwGetCursorPos(window, &cursor_x, &cursor_y);
    //   cursor_x -= 840;
    //   cursor_y -= 524;
    //   // this->update_target(0, cursor_y/100, -cursor_x/100);
    //   float x_dist = boat.position.x - 10*cos(boat.rotation.y * M_PI / 180.0f) - boat.position.x - 4*cos(boat.rotation.y * M_PI / 180.0f);
    //   float z_dist = boat.position.z + 10*sin(boat.rotation.y * M_PI / 180.0f) - boat.position.z + 4*sin(boat.rotation.y * M_PI / 180.0f);
    //   float theta = 270.0f + atan2(z_dist,x_dist)*180.0f/M_PI;
    //   // printf("%f\n", theta);
    //   int mouse_left = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    //   int b = glfwGetKey(window, GLFW_KEY_B);
    //   if (b) {
    //     std::cout<<1<<std::endl;
    //     boat.fireball.set_position(boat.position.x, boat.position.y, boat.position.z);
    //     cursor_y += 524;
    //     boat.fireball.shoot(boat.rotation.y, 1.5);
    //     std::cout<<boat.fireball.position.x<<" "<<boat.fireball.position.y<<" "<<boat.fireball.position.z<<std::endl;
    //   }
    // }

}
