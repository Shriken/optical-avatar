#include "main.h"

int main(int argc, char **argv) {
	initGlut(argc, argv);
	glewInit();

	glutMainLoop();

	return EXIT_SUCCESS;
}

bool initGlut(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Avatar");

	glutDisplayFunc(display);

	glClearColor(0., 0., 0., 1.);

	return true;
};

void display() {
	printf("displaying\n");
}
