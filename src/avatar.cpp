#include "avatar.h"

int main(int argc, char **argv) {
	if (!init()) {
		logError("there was an error in initialization\n");
		return EXIT_FAILURE;
	}

	initGlut(argc, argv);
	glewInit();

	glutMainLoop();

	return EXIT_SUCCESS;
}

bool init() {
	if ((mask = loadImage(MASK_FILE)) == NULL) return true;
	cvFlip(mask, mask, 0);

	if ((background = loadImage(BACKGROUND_FILE)) == NULL) return true;
	cvFlip(background, background, 0);
	window.setDimensions(background->width, background->height);

	// mark the fixation as dirty so it gets loaded in main
	curFixation.duration = 0;
	lastFixationTime = 0;

	return true;
}

void initGlut(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window.width, window.height);
	glutCreateWindow("Avatar");

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(resize);

	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);

	glClearColor(0., 0., 0., 1.);
};

void idle() {
	float time = 1. * clock() / CLOCKS_PER_SEC;
	fixation nextFixation;

	if (time - lastFixationTime >= curFixation.duration) {
		nextFixation = fixationSet.next();
		if (nextFixation.duration > 0) {
			curFixation = nextFixation;
			lastFixationTime = time;
			printf(
				"new fixation: %f %f %f\n",
				curFixation.x, curFixation.y, curFixation.duration
			);
			glutPostRedisplay();
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawPixels(
		background->width, background->height,
		GL_BGR, GL_UNSIGNED_BYTE,
		background->imageData
	);

	glDrawPixels(
		mask->width, mask->height,
		GL_BGR, GL_UNSIGNED_BYTE,
		mask->imageData
	);

	markFixation();

	glutSwapBuffers();
}

void markFixation() {
	int w = window.width;
	int h = window.height;
	float x = remap(curFixation.x, 0, w, -1, 1);
	float y = remap(curFixation.y, 0, h, -1, 1);

	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(3);

	glBegin(GL_LINES);
		glVertex2f(x - 10. / w, y - 10. / h);
		glVertex2f(x + 11. / w, y + 11. / h);
		glVertex2f(x + 10. / w, y - 10. / h);
		glVertex2f(x - 11. / w, y + 11. / h);
	glEnd();
}

float remap(
	float val,
	float start1, float end1,
	float start2, float end2
) {
	val = (val - start1) / (end1 - start1);
	val = val * (end2 - start2) + start2;

	return val;
}

void resize(int w, int h) {
	window.setDimensions(w, h);
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'q') {
		quit();
	}
}

void quit() {
	exit(EXIT_SUCCESS);
}
