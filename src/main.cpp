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
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Avatar");

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);

	glClearColor(0., 0., 0., 1.);

	return true;
};

void idle() {
	rot_angle += 0.01;
	if (rot_angle > 2 * M_PI) rot_angle -= 2 * M_PI;

	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// perspective transform
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV_Y, ASPECT_RATIO, 0.1, 100);

	// model transform
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(0, 0, -8);
	glRotatef(180. / M_PI * rot_angle, 0, 1, 0);

	glVertexPointer(3, GL_FLOAT, 0, CUBE_TRIS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1, 1, 1);
	glCullFace(GL_BACK);

	glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

	glPopMatrix();

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
