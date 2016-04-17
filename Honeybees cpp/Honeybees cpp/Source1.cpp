#include <math.h>
#include <cstdlib>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>

float currentHexagonPos[6][2];

//Data structures
typedef struct _Vector {
	double x, y, z;
} Vector;

//Constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const double PI = 3.14159265;

//Vars
double radian;
double speed = 10;
double rot; //rotation

//Vectors
Vector pos;
Vector vel;
Vector dir;
Vector dis;
Vector mouseCoords;

float randomFloat(float a, float b) {
	float random = ((float)rand() / (float)RAND_MAX);
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

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

void setupHexagons() {
	for (int hexagonCount = 0; hexagonCount < 6; hexagonCount++)
	{
		currentHexagonPos[hexagonCount][0] = randomFloat(-1.0f, 1.0f);
		currentHexagonPos[hexagonCount][1] = randomFloat(-1.0f, 1.0f);
	}
}

bool doesCollide(float hexagon1[], float hexagon2[]) {
	float diffX = hexagon1[0] - hexagon2[0];
	float diffY = hexagon1[1] - hexagon2[1];
	float distance = sqrtf((diffX * diffX) + (diffY * diffY));
	return distance < 0.2f;
}

void updateHexagons() {
	for (int hexagonOuter = 0; hexagonOuter < 5; hexagonOuter++) {
		for (int hexagonInner = hexagonOuter + 1; hexagonInner < 6; hexagonInner++) {
			if (doesCollide(currentHexagonPos[hexagonOuter], currentHexagonPos[hexagonInner])) {
				currentHexagonPos[hexagonInner][0] = randomFloat(-1.0f, 1.0f);
				currentHexagonPos[hexagonInner][1] = randomFloat(-1.0f, 1.0f);
			}
		}
	}
}

void display(void) {
	updateHexagons();
	glClearColor(0.565, 0.933, 0.565, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* draw the honey (x,y,size)*/
	for (int hexagonCount = 0; hexagonCount < 6; hexagonCount++) {
		drawHexagon(currentHexagonPos[hexagonCount][0], currentHexagonPos[hexagonCount][1], 0.2f);
	}
	glLoadIdentity();
	glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, -100, 100);
	//Drawing
	glColor3f(1, 0, 0);
	glTranslated(pos.x, pos.y, 0);
	glRotatef(rot, 0, 0, 1);
	glutSolidTeapot(10);

	glFlush();
	glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y) {
	mouseCoords.x = x - SCREEN_WIDTH / 2;
	mouseCoords.y = -y + SCREEN_HEIGHT / 2;
}

void move() {
	dis.x = mouseCoords.x - pos.x;
	dis.y - mouseCoords.y - pos.y;

	if (sqrt(dis.y*dis.y + dis.x*dis.x) < speed) {
		pos.x = mouseCoords.x;
		pos.y = mouseCoords.y;

	}
	else {
		radian = atan2(dis.y, dis.x);
		pos.x += cos(radian) * speed;
		pos.y += sin(radian) * speed;
		rot = radian * 180 / PI;
	}
}

void update(int value) {
	move();
	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
}

void init(void) {
	setupHexagons();
	/* Initialize GLUT */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	/* Window Creation */
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Catch the honey");
	/* When the display needs redrawing... */
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutTimerFunc(25, update, 0);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	init();
	//glutPostRedisplay();
	glutMainLoop();
	return 0;
}