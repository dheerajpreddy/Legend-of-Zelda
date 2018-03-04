#include "main.h"

#ifndef CUBOID_H
#define CUBOID_H


class Cuboid {
public:
    Cuboid() {}
    Cuboid(float x, float y, float z, float l, float b, float h, color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void update_position(float x, float y, float z);
    void set_rotation(float x);
    void update_rotation(float x);
    void set_speed(float x, float y, float z);
    void update_speed(float x, float y, float z);
    void move(GLFWwindow *window);
    void tick();
private:
    VAO *object;
};

#endif // CUBOID_H
