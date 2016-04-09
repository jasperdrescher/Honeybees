#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

void display(void) {
	/* Set background color (green) */
	glClearColor(0.565, 0.933, 0.565, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	/* Set drawing color */
	glColor3d(0.957, 0.643, 0.376);
	/* Tell OpenGL your intentions */
	glBegin(GL_POLYGON);
	/* Set the vertices */
	glVertex2d(-0.5, 0.5);
	glVertex2d(-0.5, -0.5);
	glVertex2d(0, -0.8);
	glVertex2d(0.5, -0.5);
	glVertex2d(0.5, 0.5);
	glVertex2d(0, 0.8);
	/* Done making polygon */
	glEnd();
	/* Clear screen and draw */
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	/* Initialize GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	/* Window Creation */
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Catch the honey");
	/* When the display needs redrawing... */
	glutDisplayFunc(display);
	/* Continue until user quits */
	glutMainLoop();
	return 0;
}