#pragma once

#include <stdio.h>
#include <string>

#include "log.h"

using namespace std;

struct fixation {
	float x, y;
	float duration;
};

class FixationSet {
	FILE *file;
public:
	FixationSet(string filename);
	~FixationSet();
	void loadFile(string filename);
	fixation next();
};
