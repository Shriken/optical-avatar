#pragma once

#include <string>

#include "opencv/cv.hpp"

using namespace std;

IplImage *loadImage(string filename) {
	IplImage *image;
	string path = "res/" + filename;

	image = cvLoadImage(path.c_str());
	if (image == NULL) {
		logError("image %s not found\n", path.c_str());
	}

	cvFlip(image, image, 0);

	return image;
}

IplImage *loadScaledImage(string filename, float xScale, float yScale) {
	IplImage *image = loadImage(filename);
	if (image == NULL) return NULL;

	IplImage *dest = cvCreateImage(
		cvSize(image->width * xScale, image->height * yScale),
		image->depth,
		image->nChannels
	);

	cvResize(image, dest);
	cvReleaseImage(&image);

	return dest;
}
