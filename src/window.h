#pragma once

struct Window {
	int width;
	int height;
	float aspectRatio;

	Window(int w, int h) : width(w), height(h), aspectRatio(1. * w / h) {}
	void setDimensions(int w, int h) {
		this->width = w;
		this->height = h;
		this->aspectRatio = 1. * w / h;
	}
};
