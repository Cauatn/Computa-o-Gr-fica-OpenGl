#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
//alteracao

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

float x = 0.01f, y, z;
float dx, dy, dz, dt;
int a = 10, b = 28, c = 8 / 3;

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

GLfloat pointVertex[] = { 0,0,0 };

void drawPoint();

int main(void)
{

    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Atrator de Lorenz", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);


    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); // same as above comment

    dt = 0.001f;

    glTranslatef(400, 300, 0);
    glScalef(11, 11, 0);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {

        //Calcula as coordenadas do ponto
        dx = (a * (y - x)) * dt;
        dy = ((x * (b - z) - y)) * dt;
        dz = ((x * y) - (c * z)) * dt;
        x = x + dx;
        y = y + dy;
        z = z + dz;

        pointVertex[0] = x;
        pointVertex[1] = y;
        pointVertex[2] = z;

        // Render OpenGL here
        drawPoint();
        
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void drawPoint()
{
    glEnable(GL_POINT); // make the point circular
    glEnableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're using a vertex array for fixed-function attribute
    glPointSize(1); // must be added before glDrawArrays is called
    glVertexPointer(2, GL_FLOAT, 0, pointVertex); // point to the vertices to be used
    glDrawArrays(GL_POINTS, 0, 1); // draw the vertixes
    glDisableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're finished using the vertex arrayattribute
    glDisable(GL_POINT); // stop the smoothing to make the points circular
}
