#include "cuboid.h"
#include "boat.h"
#include "sail.h"
#include "main.h"

unsigned long long bouncer = 0;

float randomGen2(float min, float max) {
  return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

Boat::Boat(float x, float y, float z, float l, float b, float h, color_t color) {
    this->set_position(x, y, z);
    this->set_rotation(0);
    this->set_speed(0, 0, 0);
    this->set_health(100);
    this->l = l;
    this->b = b;
    this->h = h;
    this->base = Cuboid(x, y, z, l, b, h, color);
    this->sail = Sail(x, y+ 2, z, 5, 4, 0.2, COLOR_WHITE);
    this->sail.set_rotation(this->rotation + 90);
    this->counter = 0;
    this->wind = 0;
}

void Boat::draw(glm::mat4 VP) {
  this->sail.draw(VP);
  this->base.draw(VP);
}

void Boat::set_speed(float x, float y, float z) {
  this->speed = glm::vec3(x, y, z);
  this->base.set_speed(x, y, z);
  this->sail.set_speed(x, y, z);
}

void Boat::update_speed(float x, float y, float z) {
  this->speed += glm::vec3(x, y, z);
  this->base.update_speed(x, y, z);
  this->sail.update_speed(x, y, z);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->base.set_position(x, y, z);
    this->sail.set_position(x, y+ 2, z);
}

void Boat::set_rotation(float x) {
    this->rotation = x;
    this->base.set_rotation(x);
}

void Boat::update_rotation(float x) {
    this->rotation += x;
    this->base.update_rotation(x);
}

void Boat::update_health(long long x) {
    this->health +=x;
}

void Boat::set_health(long long x) {
    this->health =x;
}


void Boat::update_position(float x, float y, float z) {
    this->position += glm::vec3(x, y, z);
    this->base.update_position(x, y, z);
    this->sail.update_position(x, y, z);
}

void Boat::tick() {
    this->update_position(0, 0.05*cos((bouncer++)/8), 0);
    this->position.x -= this->speed.x;
    this->position.y += this->speed.y;
    this->position.z += this->speed.z;
    this->position = this->base.position;
    this->rotation = this->base.rotation;
    this->sail.position = this->base.position + glm::vec3(0, 2.5, 0);
    this->windHandler();
    this->base.tick();
    this->sail.tick();
}

void Boat::move(GLFWwindow *window) {
  int left  = glfwGetKey(window, GLFW_KEY_LEFT), right = glfwGetKey(window, GLFW_KEY_RIGHT), up = glfwGetKey(window, GLFW_KEY_UP), down = glfwGetKey(window, GLFW_KEY_DOWN), space = glfwGetKey(window, GLFW_KEY_SPACE);
  if (up) {
    this->update_position(-0.1*cos(this->rotation*M_PI/180.0f), 0, 0.1*sin(this->rotation * M_PI / 180.0f));
  }
  else if (down) {
    this->update_position(0.1*cos(this->rotation*M_PI/180.0f), 0, -0.1*sin(this->rotation * M_PI / 180.0f));
  }
  if (left) {
    this->update_rotation(1.0);
  } else if (right) {
    this->update_rotation(-1.0);
  }
  if (space && this->position.y < 3.15) {
    this->update_position(0, 7.0, 0);
  }
  if (this->position.y > 3.15) {
    this->update_position(0, -0.15, 0);
  }
  this->base.move(window);
  // this->sail.move(window);
}

void Boat::windHandler() {
  //Increasing counter to change wind
  if ((this->counter++) % 500 == 0) {
      this->wind = (int)randomGen2(0, 4);
  }
  // Changing rotation of sail and position of boat based on wind
  if (this->wind == 0) {                                     // No wind, default
    this->sail.set_rotation(this->rotation+90);              // Sail is always perpendicular to boat
  } else if (this->wind == 1 || this->wind == 2) {
    // Sail rotation
    if(this->sail.rotation < 90) {
      this->sail.update_rotation(1);
    } else if(this->sail.rotation > 90) {
      this->sail.update_rotation(-1);
    }
    // Boat position
    if(wind == 1) {
      this->update_position(0.01, 0, 0);
    } else {
      this->update_position(-0.01, 0, 0);
    }
  } else {
    // Sail rotation
    if(this->sail.rotation < 0) {
      this->sail.update_rotation(1);
    } else if(this->sail.rotation > 0) {
      this->sail.update_rotation(-1);
    }
    // Boat position
    if(wind == 3) {
      this->update_position(0, 0, 0.01);
    } else {
      this->update_position(0, 0, -0.01);
    }
  }

}

bounding_box_t Boat::bounding_box() {
  float x = this->position.x, y = this->position.y, z = this->position.z;
  bounding_box_t bbox = {x, y, z, 2*this->l, 2*this->b, 2*this->h};
  return bbox;
}
