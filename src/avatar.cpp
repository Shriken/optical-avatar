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
	// load background
	background = loadScaledImage(BACKGROUND_FILE, scaleX, scaleY);
	if (background == NULL) return false;
	window.setDimensions(background->width, background->height);

	char filename[16];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			sprintf(filename, "grid-photos/%i%i.jpg", i, j);
			gridGazes[i][j] = loadScaledImage(filename, 1. / 4, 1. / 4);
			if (gridGazes[i][j] == NULL) return false;
		}
	}

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

	int i = 5 * curFixation.y / background->height;
	int j = 9 * curFixation.x / background->width;
	glDrawPixels(
		gridGazes[i][j]->width, gridGazes[i][j]->height,
		GL_BGR, GL_UNSIGNED_BYTE,
		gridGazes[i][j]->imageData
	);

	markFixation();

	glutSwapBuffers();
}

void markFixation() {
	int w = window.width;
	int h = window.height;
	float x = remap(curFixation.x * scaleX, 0, w, -1, 1);
	float y = remap(curFixation.y * scaleY, 0, h, -1, 1);

	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(3);

	glBegin(GL_LINES);
		glVertex2f(x - 10. / w, y - 10. / h);
		glVertex2f(x + 11. / w, y + 11. / h);
		glVertex2f(x + 10. / w, y - 10. / h);
		glVertex2f(x - 11. / w, y + 11. / h);
	glEnd();
}

void resize(int w, int h) {
	window.setDimensions(w, h);
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':
			quit();
			break;
		case 'r':
			fixationSet.loadFile(FIXATION_FILE);
			break;
		default:
			break;
	}
}

void quit() {
	cvReleaseImage(&background);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			cvReleaseImage(&(gridGazes[i][j]));
		}
	}

	exit(EXIT_SUCCESS);
}
