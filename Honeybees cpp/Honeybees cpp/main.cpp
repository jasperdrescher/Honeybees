#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

void changeViewPort(int w, int h)
{
	//Change the Viewport to a editable width and height
	glViewport(0, 0, w, h);
}

void setup() {
	//Set the background color to grey
	glClearColor(0.863, 0.863, 0.863, 1.0f);
}

void drawHexagon(float x, float y, float size) {
	glBegin(GL_TRIANGLES);
	glVertex2f((-0.5f*size) + x, (-0.5f*size) + y);
	glVertex2f((0.0f*size) + x, (0.5f*size) + y);
	glVertex2f((0.5f*size) + x, (-0.5f*size) + y);
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
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Catch the honey");
	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(render);

	setup();

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}

	glutMainLoop();
	return 0;
}