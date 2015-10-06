#include "fixations.h"

FixationSet::FixationSet(string filename) {
	filename = "res/" + filename;
	this->file = fopen(filename.c_str(), "r");
	if (this->file == NULL) {
		logError("file %s does not exist\n", filename.c_str());
	}
}

fixation FixationSet::next() {
	fixation ret;

	if (feof(this->file)) {
		ret.duration = -1;
		return ret;
	}

	fscanf(this->file, "%f, %f, %f\n", &ret.x, &ret.y, &ret.duration);
	return ret;
};
