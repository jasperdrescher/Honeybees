//Hello world!
//Please read the LICENSE.md and README.md files for credits, references and the license.
//Keep in mind that this is my first attempt at writing a program in C++, so any feedback is appreciated.
//This file originates from the following repository: https://github.com/JasperDre/Honeybees.

#include <math.h>			//Standard definitions.
#include <cstdlib>			//Standard definitions.
#include <Windows.h>		//Standard definitions.
#include <GL/glew.h>		//GLUT.
#include <GL/freeglut.h>	//FreeGLUT.
#include <iostream>			//C++ I/O.
#include <stdlib.h>			//Standard definitions.

#define WINDOWWIDTH 768
#define WINDOWHEIGHT 768
#define PLAYERSIZE (0.2f + playerScore / 164.0f)
#define PLAYFIELDSIZE 4.0f
#define CAMERAMOVESPEED 0.1f
#define HEXAGONCOUNT 42
#define HEXAGONSIZE 0.25f
#define ENEMYSIZE 0.4f

using  namespace std;

int windowID;
float playerScore = 0.0f;
float currentHexagonPos[HEXAGONCOUNT][2];
float currentEnemyPos[1][2];
float cameraPosition[2] = { 0,0 };

int w = WINDOWWIDTH, h = WINDOWHEIGHT;
const int font = (int)GLUT_BITMAP_9_BY_15;
char s[30];
char d[30];
double t;

float randomFloat(float a, float b) {
   	float random = ((float)rand() / (float)RAND_MAX);
   	float diff = b - a;
   	float r = random * diff;
   	return a + r;
}

void drawPlayer(float x, float y) {
	glColor3f(0.988, 0.815, 0.211);
	glBegin(GL_POLYGON);
	glVertex2d(x - (PLAYERSIZE / 2), y + (PLAYERSIZE / 2));
	glVertex2d(x + (PLAYERSIZE / 2), y + (PLAYERSIZE / 2));
	glVertex2d(x + (PLAYERSIZE / 2), y - (PLAYERSIZE / 2));
	glVertex2d(x - (PLAYERSIZE / 2), y - (PLAYERSIZE / 2));
	glEnd();
}

void drawHexagon(float x, float y, float size) {
   	glColor3f(0.980, 0.698, 0.172);
   	glBegin(GL_POLYGON);
   	glVertex2d(-0.4 * size + x, 0.2 * size + y);
   	glVertex2d(-0.4 * size + x, -0.2 * size + y);
   	glVertex2d(0 * size + x, -0.4 * size + y);
   	glVertex2d(0.4 * size + x, -0.2 * size + y);
   	glVertex2d(0.4 * size + x, 0.2 * size + y);
   	glVertex2d(0 * size + x, 0.4 * size + y);
	glEnd();
}

void drawEnemy(float x, float y, float size) {
	glColor3f(0.863, 0.078, 0.235);
	glBegin(GL_POLYGON);
	glVertex2d(x - (ENEMYSIZE / 2), y + (ENEMYSIZE / 2));
	glVertex2d(x + (ENEMYSIZE / 2), y + (ENEMYSIZE / 2));
	glVertex2d(x + (ENEMYSIZE / 2), y - (ENEMYSIZE / 2));
	glVertex2d(x - (ENEMYSIZE / 2), y - (ENEMYSIZE / 2));
	glEnd();
}

void drawBorders() {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-PLAYFIELDSIZE, PLAYFIELDSIZE);
	glVertex2f(PLAYFIELDSIZE, PLAYFIELDSIZE);
	glVertex2f(PLAYFIELDSIZE, -PLAYFIELDSIZE);
	glVertex2f(-PLAYFIELDSIZE, -PLAYFIELDSIZE);
	glEnd();
}
   
void setupHexagons() {
   	for (int hexagonCount = 0; hexagonCount < HEXAGONCOUNT; hexagonCount++)
   	{
   		currentHexagonPos[hexagonCount][0] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);
   		currentHexagonPos[hexagonCount][1] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);
   	}
}

void setupEnemy() {
	currentEnemyPos[0][0] = randomFloat(-PLAYFIELDSIZE + ENEMYSIZE, PLAYFIELDSIZE - ENEMYSIZE);
	currentEnemyPos[0][1] = randomFloat(-PLAYFIELDSIZE + ENEMYSIZE, PLAYFIELDSIZE - ENEMYSIZE);
}

bool doesCollide(float item1[], float item2[], float size) {
   	float diffX = item1[0] - item2[0];
   	float diffY = item1[1] - item2[1];
   	float distance = sqrtf((diffX * diffX) + (diffY * diffY));
   	return distance < size;
}

void updateHexagons() {
   	for (int hexagonOuter = 0; hexagonOuter < HEXAGONCOUNT - 1; hexagonOuter++) {
   		for (int hexagonInner = hexagonOuter + 1; hexagonInner < HEXAGONCOUNT; hexagonInner++) {
   			if (doesCollide(currentHexagonPos[hexagonOuter], currentHexagonPos[hexagonInner], HEXAGONSIZE)) {
				currentHexagonPos[hexagonInner][0] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);
				currentHexagonPos[hexagonInner][1] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);
   			}
   		}
   	}
}

void checkPlayerCollision() {
	for (int hexagonIndex = 0; hexagonIndex < HEXAGONCOUNT; hexagonIndex++) {
		if (doesCollide(cameraPosition, currentHexagonPos[hexagonIndex], (HEXAGONSIZE + PLAYERSIZE) / 2)) {
			currentHexagonPos[hexagonIndex][0] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);
			currentHexagonPos[hexagonIndex][1] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);
			playerScore++;
		}
	}
	if (doesCollide(cameraPosition, currentEnemyPos[0], (0.3f + PLAYERSIZE) / 2)) {
		currentEnemyPos[0][0] = randomFloat(-PLAYFIELDSIZE + ENEMYSIZE, PLAYFIELDSIZE - ENEMYSIZE);
		currentEnemyPos[0][1] = randomFloat(-PLAYFIELDSIZE + ENEMYSIZE, PLAYFIELDSIZE - ENEMYSIZE);
		playerScore = 0.0f;
	}
}

void moveEnemy(int value) {
	currentEnemyPos[0][0] = (currentEnemyPos[0][0] > PLAYFIELDSIZE - ENEMYSIZE) ? -PLAYFIELDSIZE + ENEMYSIZE : currentEnemyPos[0][0] + randomFloat(-0.01, 0.1);
	currentEnemyPos[0][1] = (currentEnemyPos[0][1] > PLAYFIELDSIZE - ENEMYSIZE) ? -PLAYFIELDSIZE + ENEMYSIZE : currentEnemyPos[0][1] + randomFloat(-0.01, 0.1);
	glutTimerFunc(250, moveEnemy, 0);
	glutPostRedisplay();
}

static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	w = width;
	h = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);     
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void setOrthographicProjection() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0);
	glMatrixMode(GL_MODELVIEW);
}
void resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
void renderBitmapString(float x, float y, void *font, const char *string) {
	const char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void keyboardFunc(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'a':
		cameraPosition[0] += CAMERAMOVESPEED;
		break;
	case 'd':
		cameraPosition[0] -= CAMERAMOVESPEED;
		break;
	case 'w':
		cameraPosition[1] += CAMERAMOVESPEED;
		break;
	case 's':
		cameraPosition[1] -= CAMERAMOVESPEED;
		break;
	case 27:
		glutDestroyWindow(windowID);
		exit(0);
		break;
	default:
		cout << "Press escape or WASD.  All other characters are ignored" << endl;
		break;
	}
	float halfPlayerSize = PLAYERSIZE / 2.0f;
	//The following is an alternative to: if (cameraPositon[0] > PLAYFIELDSIZE) { cameraPosition[0] = PLAYFIELDSIZE; }.
	cameraPosition[0] = (cameraPosition[0] > PLAYFIELDSIZE - halfPlayerSize) ? PLAYFIELDSIZE - halfPlayerSize : cameraPosition[0];
	cameraPosition[0] = (cameraPosition[0] < -PLAYFIELDSIZE + halfPlayerSize) ? -PLAYFIELDSIZE + halfPlayerSize : cameraPosition[0];
	cameraPosition[1] = (cameraPosition[1] > PLAYFIELDSIZE - halfPlayerSize) ? PLAYFIELDSIZE - halfPlayerSize : cameraPosition[1];
	cameraPosition[1] = (cameraPosition[1] < -PLAYFIELDSIZE + halfPlayerSize) ? -PLAYFIELDSIZE + halfPlayerSize : cameraPosition[1];
}

void display(void) {
	glLoadIdentity();
	gluLookAt(cameraPosition[0], cameraPosition[1], -1, cameraPosition[0], cameraPosition[1], 0, 0.0, 1.0, 0.0);
   	updateHexagons();
	checkPlayerCollision();
   	glClearColor(1.000, 0.992, 0.878, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	resetPerspectiveProjection();
   	for (int hexagonCount = 0; hexagonCount < HEXAGONCOUNT; hexagonCount++) {
   		drawHexagon(currentHexagonPos[hexagonCount][0], currentHexagonPos[hexagonCount][1], HEXAGONSIZE);
   	}
	drawEnemy(currentEnemyPos[0][0], currentEnemyPos[0][1], 0.3f);
	drawBorders();
	drawPlayer(cameraPosition[0], cameraPosition[1]);
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glColor3d(0.0, 0.0, 1.0);
	renderBitmapString(0.1, 15, (void*)font, d);
	renderBitmapString(0.1, 30, (void*)font, s);
	glPopMatrix();
   	glutSwapBuffers();
	glutPostRedisplay();
}

void update(int value) {
	t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	int score = (int)playerScore;
	int time = (int)t;
	sprintf_s(d, "Score: %2d", score);
	sprintf_s(s, "Time: %2d sec", time);
	glutTimerFunc(500, update, 0);
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	cout << "Welcome to Honeybees.\n\
	- Use your keyboard to move.\n\
	- Press escape to quit.\n";
   	setupHexagons();
	setupEnemy();
   	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
   	glutInitWindowPosition(0, 0);
   	char s[4096] = "Honeybees";
	windowID = glutCreateWindow(s);
	glutDisplayFunc(display);
	glutTimerFunc(25, update, 0);
	glutTimerFunc(25, moveEnemy, 0);
	glutKeyboardFunc(keyboardFunc);
   	glutMainLoop();
   	return 0;
}