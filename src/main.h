#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <math.h>

#include "cube.h"

float FOV_Y = 30;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
float ASPECT_RATIO = 1. * WINDOW_WIDTH / WINDOW_HEIGHT;

float rot_angle = 0;

int main(int argc, char **argv);
bool initGlut(int argc, char **argv);

void idle();
void display();
void keyboard(unsigned char key, int x, int y);
void quit();
