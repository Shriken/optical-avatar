#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <opencv/cv.hpp>
#include <opencv/highgui.h>

#include <stdio.h>
#include <math.h>

#include "log.h"
#include "window.h"

#define MASK_FILE "mask.jpg"

float FOV_Y = 30;

struct Window window(800, 600);
IplImage *image = NULL;

int main(int argc, char **argv);
bool init();
void initGlut(int argc, char **argv);

void idle();
void display();
void keyboard(unsigned char key, int x, int y);
void quit();
