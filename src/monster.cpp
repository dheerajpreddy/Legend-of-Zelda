#include "cuboid.h"
#include "monster.h"
#include "main.h"

unsigned long long bouncer2 = 3;

Monster::Monster(float x, float y, float z, float scale, int type, color_t color) {
    this->set_position(x, y, z);
    this->set_rotation(0, 0, 0);
    this->set_speed(0, 0, 0);
    this->set_health(100);
    this->l = 3*scale, this->b=3*scale, this->h=3*scale;
    this->type = type;

    this->center = Cuboid(x, y, z, l, b, h, color);
    this->left = Cuboid(x, y, z + 3*l/2, l/2, b/2, h/2, color);
    this->right = Cuboid(x, y, z - 3*l/2, l/2, b/2, h/2, color);
    this->top = Cuboid(x, y + 3*l/2, z, l/2, b/2, h/2, color);
}

void Monster::draw(glm::mat4 VP) {
  this->center.draw(VP);
  this->left.draw(VP);
  this->right.draw(VP);
  this->top.draw(VP);
}

void Monster::set_speed(float x, float y, float z) {
  this->speed = glm::vec3(x, y, z);
  this->center.set_speed(x, y, z);
  this->left.set_speed(x, y, z);
  this->right.set_speed(x, y, z);
  this->top.set_speed(x, y, z);
}

void Monster::update_speed(float x, float y, float z) {
  this->speed += glm::vec3(x, y, z);
  this->center.update_speed(x, y, z);
  this->left.update_speed(x, y, z);
  this->right.update_speed(x, y, z);
  this->top.update_speed(x, y, z);
}

void Monster::set_position(float x, float y, float z) {
  this->position = glm::vec3(x, y, z);
  this->center.set_position(x, y, z);
  this->left.set_position(x, y, z + 4.5);
  this->right.set_position(x, y, z - 4.5);
  this->top.set_position(x, y + 4.5, z);
}

void Monster::set_rotation(float x, float y, float z) {
    this->rotation = glm::vec3(x, y, z);
    this->center.set_rotation(x, y, z);
    this->left.set_rotation(x, y, z);
    this->right.set_rotation(x, y, z);
    this->top.set_rotation(x, y, z);
}

void Monster::update_rotation(float x, float y, float z) {
    this->rotation += glm::vec3(x, y, z);
    this->center.update_rotation(x, y, z);
    this->left.update_rotation(x, y, z);
    this->right.update_rotation(x, y, z);
    this->top.update_rotation(x, y, z);
}

void Monster::update_health(long long x) {
    this->health +=x;
}

void Monster::set_health(long long x) {
    this->health = x;
}

void Monster::update_position(float x, float y, float z) {
    this->position += glm::vec3(x, y, z);
    this->center.update_position(x, y, z);
    this->left.update_position(x, y, z);
    this->right.update_position(x, y, z);
    this->top.update_position(x, y, z);
}

void Monster::tick() {
  this->update_position(0, 0.02*cos((bouncer2++)/8), 0);
}

// void Monster::move(GLFWwindow *window) {
//   int left  = glfwGetKey(window, GLFW_KEY_LEFT), right = glfwGetKey(window, GLFW_KEY_RIGHT), up = glfwGetKey(window, GLFW_KEY_UP), down = glfwGetKey(window, GLFW_KEY_DOWN), space = glfwGetKey(window, GLFW_KEY_SPACE);
//   if (up) {
//     this->update_position(-0.1*cos(this->rotation*M_PI/180.0f), 0, 0.1*sin(this->rotation * M_PI / 180.0f));
//   }
//   else if (down) {
//     this->update_position(0.1*cos(this->rotation*M_PI/180.0f), 0, -0.1*sin(this->rotation * M_PI / 180.0f));
//   }
//   if (left) {
//     this->update_rotation(1.0);
//   } else if (right) {
//     this->update_rotation(-1.0);
//   }
//   if (space && this->position.y < 3.15) {
//     this->update_position(0, 7.0, 0);
//   }
//   if (this->position.y > 3.15) {
//     this->update_position(0, -0.15, 0);
//   }
//   this->base.move(window);
//   // this->sail.move(window);
// }

bounding_box_t Monster::bounding_box() {
  float x = this->position.x, y = this->position.y, z = this->position.z;
  bounding_box_t bbox = {x, y, z, 2*this->l, 2*this->b, 2*this->h};
  return bbox;
}
