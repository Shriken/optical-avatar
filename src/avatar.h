#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <opencv/cv.hpp>
#include <opencv/highgui.h>

#include <math.h>
#include <string>
#include <time.h>
#include <stdio.h>

#include "log.h"
#include "window.h"
#include "fixations.h"
#include "resources.h"

#define MASK_FILE "mask.jpg"
#define BACKGROUND_FILE "background.jpg"
#define FIXATION_FILE "fixations.txt"

float FOV_Y = 30;

struct Window window(800, 600);
IplImage *mask = NULL;
IplImage *background = NULL;
FixationSet fixationSet(FIXATION_FILE);

fixation curFixation;
clock_t lastFixationTime;

int main(int argc, char **argv);
bool init();
IplImage *loadImage(std::string filename);
void initGlut(int argc, char **argv);

void idle();
void display();
void markFixation();
float remap(float val, float start1, float end1, float start2, float end2);
void resize(int w, int h);
void keyboard(unsigned char key, int x, int y);
void quit();
