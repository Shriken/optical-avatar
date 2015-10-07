#pragma once

float remap(
	float val,
	float start1, float end1,
	float start2, float end2
) {
	val = (val - start1) / (end1 - start1);
	val = val * (end2 - start2) + start2;

	return val;
}
