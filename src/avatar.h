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
#include "util.h"
#include "window.h"
#include "fixations.h"
#include "resources.h"

#define MASK_FILE "mask.jpg"
#define BACKGROUND_FILE "background.jpg"
#define FIXATION_FILE "fixations.txt"

float FOV_Y = 30;

float scaleX = 2;
float scaleY = 2;
struct Window window(800, 600);
IplImage *background = NULL;
IplImage *gridGazes[5][9];
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
void resize(int w, int h);
void keyboard(unsigned char key, int x, int y);
void quit();
