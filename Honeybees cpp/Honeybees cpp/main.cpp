#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

void drawHexagon(float x, float y, float size) {
	glBegin(GL_TRIANGLES);
	glVertex2f((-0.5f*size) + x, (-0.5f*size) + y);
	glVertex2f((0.0f*size) + x, (0.5f*size) + y);
	glVertex2f((0.5f*size) + x, (-0.5f*size) + y);
	/*glVertex2f(-0.1f, -.1f);
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, .5f);
	glVertex2f(.5f, 0.0f);
	for (float index = 0; index < 6; index++)
	{
		glVertex2f((index) / 3.0f, 0.8f);
	}*/
	//glEnd();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
	glLoadIdentity();
	drawHexagon(-.5f, 0.0f, 1.0f);
	drawHexagon(.5f, 0.0f, 1.0f);
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(720, 480);
	glutCreateWindow("Catch the honey");
	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(render);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}

	glutMainLoop();
	return 0;
}
