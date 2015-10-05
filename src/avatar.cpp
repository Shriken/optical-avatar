#include "avatar.h"

int main(int argc, char **argv) {
	if (!init()) {
		logError("there was an error in initialization\n");
		return EXIT_FAILURE;
	}

	printf("%lx\n", sizeof(IplImage));

	initGlut(argc, argv);
	glewInit();

	glutMainLoop();

	return EXIT_SUCCESS;
}

bool init() {
	if ((image = loadImage(MASK_FILE)) == NULL) return true;
	cvFlip(image, image, 0);
	window.setDimensions(image->width, image->height);

	return true;
}

IplImage *loadImage(std::string filename) {
	IplImage *image;
	std::string path = "res/" + filename;

	image = cvLoadImage(path.c_str());
	if (image == NULL) {
		logError("image %s not found\n", path.c_str());
	}

	return image;
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
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawPixels(
		image->width, image->height,
		GL_BGR, GL_UNSIGNED_BYTE,
		image->imageData
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
