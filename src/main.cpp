#include "main.h"
#include "timer.h"
#include "cuboid.h"
#include "camera.h"
#include "boat.h"
#include "monster.h"
#include "barrel.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Cuboid ocean, rocks[100];
Monster m;
Boat boat;
Barrel barrels[100];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
Camera cam;
Timer t60(1.0 / 60);

// Declaring camera angle views
extern int camView;
unsigned long long int score = 0;

float randomGen(float min, float max) {
  return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    Matrices.view = glm::lookAt( cam.eye, cam.target, cam.up ); // Rotating cam for 3D
    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 MVP;  // MVP = Projection * View * Model

    ocean.draw(VP);
    boat.draw(VP);
    for(int i=0; i<100; i++) {
      rocks[i].draw(VP);
      barrels[i].draw(VP);
    }
}

void updateTitle() {
  char s[100];
  sprintf(s, "Health: %lld, Score: %llu", boat.health, score);
  glfwSetWindowTitle(window, s);
}

void tick_input(GLFWwindow *window) {
    boat.move(window);                 // Moves boat
    cam.update(boat, camView);  // Updates camera based on camView
}

void tick_elements() {
    ocean.tick();
    boat.tick();

    // Collission detection with rocks
    for(int i=0; i<100; i++) {
      if (detect_collision(boat.bounding_box(), rocks[i].bounding_box())) {
        boat.update_position(2*cos(boat.rotation*M_PI / 180.0f), 0, -2*sin(boat.rotation*M_PI / 180.0f));
        boat.update_health(-1);
      }
      if (detect_collision(boat.bounding_box(), barrels[i].bounding_box())) {
        barrels[i].set_position(randomGen(-500, 500), 2.5, randomGen(-500, 500));
        score+= barrels[i].gift_val;
      }
      rocks[i].tick();
      barrels[i].tick();
    }

    // Updating title bar
    updateTitle();

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    glm::vec3 eye ( 10, 7, 0 ), target (0, 0, 0), up (0, 1, 0);
    cam = Camera(eye, target, up);
    ocean       = Cuboid(0.0, 0.0, 0.0, 1000.0, 2.0, 1000.0, COLOR_OCEAN_BLUE);
    boat       = Boat(0.0, 2.5, 0.0, 3.0, 1.0, 1.5, COLOR_RED);
    for (int i = 0; i < 100; i++) {
        rocks[i] = Cuboid(randomGen(-500, 500), 2.5, randomGen(-500, 500), 0.5, 0.5, 0.5, COLOR_BLACK);
        barrels[i] = Barrel(randomGen(-500, 500), 2.5, randomGen(-500, 500), COLOR_BARREL);
    }
    // m = Monster(3.0, 2.5, 3.0, 1.0, 0, COLOR_BLACK);
    // b = Barrel(3.0, 2.5, 3.0, COLOR_BARREL);
    // rocks[0]    = Cuboid(2.0, 2.5, 0.0, 0.5, 0.5, 0.5, COLOR_BLACK);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 900;
    int height = 900;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.length + b.length)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.width + b.width));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(1.57f, (float)(900/900), 0.01f, 500.0f);
}
