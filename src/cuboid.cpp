#include "cuboid.h"
#include "main.h"

Cuboid::Cuboid(float x, float y, float z, float l, float b, float h, color_t color) {
    this->set_position(x, y, z);
    this->set_rotation(0);
    this->set_speed(0, 0, 0);
    this->l = l;
    this->b = b;
    this->h = h;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    const GLfloat vertex_buffer_data[] = {
        -l,-b,-h, // triangle 1 : begin
        -l,-b, h,
        -l, b, h, // triangle 1 : end
        l, b,-h, // triangle 2 : begin
        -l,-b,-h,
        -l, b,-h, // triangle 2 : end
        l,-b, h,
        -l,-b,-h,
        l,-b,-h,
        l, b,-h,
        l,-b,-h,
        -l,-b,-h,
        -l,-b,-h,
        -l, b, h,
        -l, b,-h,
        l,-b, h,
        -l,-b, h,
        -l,-b,-h,
        -l, b, h,
        -l,-b, h,
        l,-b, h,
        l, b, h,
        l,-b,-h,
        l, b,-h,
        l,-b,-h,
        l, b, h,
        l,-b, h,
        l, b, h,
        l, b,-h,
        -l, b,-h,
        l, b, h,
        -l, b,-h,
        -l, b, h,
        l, b, h,
        -l, b, h,
        l,-b, h
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cuboid::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cuboid::set_speed(float x, float y, float z) {
  this->speed = glm::vec3(x, y, z);
}

void Cuboid::update_speed(float x, float y, float z) {
  this->speed += glm::vec3(x, y, z);
}

void Cuboid::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cuboid::set_rotation(float x) {
    this->rotation = x;
}

void Cuboid::update_rotation(float x) {
    this->rotation += x;
}

void Cuboid::update_position(float x, float y, float z) {
    this->position += glm::vec3(x, y, z);
}

void Cuboid::tick() {
    // this->rotation += speed;
    this->position.x -= this->speed.x;
    this->position.y += this->speed.y;
}

void Cuboid::move(GLFWwindow *window) {
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

}

bounding_box_t Cuboid::bounding_box() {
  float x = this->position.x, y = this->position.y, z = this->position.z;
  bounding_box_t bbox = {x, y, z, 2*this->l, 2*this->b, 2*this->h};
  return bbox;
}
