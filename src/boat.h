#include "main.h"
#include "cuboid.h"
#include "sail.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, float l, float b, float h, color_t color1);
    Cuboid base;
    Sail sail;
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
    void tick();
    void move(GLFWwindow *window);
private:
    VAO *object;
};

#endif // BOAT_H
