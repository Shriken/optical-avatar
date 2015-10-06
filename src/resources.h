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

	return image;
}
