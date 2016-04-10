#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

void drawHexagon(float x, float y, float size) {
	/* Set drawing color (RGBA)*/
	glColor3d(0.957, 0.643, 0.376);
	/* Tell OpenGL your intentions */
	glBegin(GL_POLYGON);
	/* Set the vertices glVertex2d(x, y);*/
	glVertex2d(-0.5 * size + x, 0.5 * size + y);
	glVertex2d(-0.5 * size + x, -0.5 * size + y);
	glVertex2d(0 * size + x, -0.8 * size + y);
	glVertex2d(0.5 * size + x, -0.5 * size + y);
	glVertex2d(0.5 * size + x, 0.5 * size + y);
	glVertex2d(0 * size + x, 0.8 * size + y);
	/* Done making polygon */
	glEnd();
}
void display(void) {
	/* Set background color (RGBA) */
	glClearColor(0.565, 0.933, 0.565, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw the honey (x,y,size)*/
	drawHexagon(-0.5f, -0.4f, 0.5f);
	drawHexagon(0.5f, 0.4f, 0.7f);
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