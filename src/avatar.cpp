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

	// perspective transform
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV_Y, window.aspectRatio, 0.1, 100);

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'q') {
		quit();
	}
}

void quit() {
	exit(EXIT_SUCCESS);
}
