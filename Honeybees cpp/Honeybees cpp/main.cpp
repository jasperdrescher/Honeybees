// DONE Block movement when colliding with the border / lines.
//Draw more hexagons within the borders.
//Destroy hexagons on collision with the player.
//Add bitmap sprite as player (bee).
//Add an enemy sprite which moves across the screen and destroy player on collision.

#include <math.h>
#include <cstdlib>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>

#define PLAYERSIZE 0.2f
#define PLAYFIELDSIZE 4.0f
#define CAMERAMOVESPEED 0.1f

float currentHexagonPos[6][2];

volatile float cameraPosition[2] = { 0,0 };

float randomFloat(float a, float b) {
   	float random = ((float)rand() / (float)RAND_MAX);
   	float diff = b - a;
   	float r = random * diff;
   	return a + r;
}
   
void drawHexagon(float x, float y, float size) {
   	//Set drawing color (RGBA)
   	glColor3d(0.957, 0.643, 0.376);
   	//Tell OpenGL your intentions
   	glBegin(GL_POLYGON);
   	//Set the vertices glVertex2d(x, y);
   	glVertex2d(-0.5 * size + x, 0.5 * size + y);
   	glVertex2d(-0.5 * size + x, -0.5 * size + y);
   	glVertex2d(0 * size + x, -0.8 * size + y);
   	glVertex2d(0.5 * size + x, -0.5 * size + y);
   	glVertex2d(0.5 * size + x, 0.5 * size + y);
   	glVertex2d(0 * size + x, 0.8 * size + y);
	glEnd();
   	//Done making polygon
}

void drawBorders() {
	glColor3d(0.957, 0.643, 0.376);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-PLAYFIELDSIZE, PLAYFIELDSIZE);
	glVertex2f(PLAYFIELDSIZE, PLAYFIELDSIZE);
	glVertex2f(PLAYFIELDSIZE, -PLAYFIELDSIZE);
	glVertex2f(-PLAYFIELDSIZE, -PLAYFIELDSIZE);
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
  
void drawPlayer(float x, float y) {
	 glBegin(GL_POLYGON);
	 glVertex2d(x - (PLAYERSIZE / 2), y + (PLAYERSIZE / 2));
	 glVertex2d(x + (PLAYERSIZE / 2), y + (PLAYERSIZE / 2));
	 glVertex2d(x + (PLAYERSIZE / 2), y - (PLAYERSIZE / 2));
	 glVertex2d(x - (PLAYERSIZE / 2), y - (PLAYERSIZE / 2));
	 glEnd();
}
void display(void) {
	glLoadIdentity();
	gluLookAt(cameraPosition[0], cameraPosition[1], -1, cameraPosition[0], cameraPosition[1], 0, 0.0, 1.0, 0.0);
   	updateHexagons();
	//Set background color (RGBA)
   	glClearColor(0.565, 0.933, 0.565, 0);
   	glClear(GL_COLOR_BUFFER_BIT);
   
   	//draw the honey (x,y,size)
   	for (int hexagonCount = 0; hexagonCount < 6; hexagonCount++) {
   		drawHexagon(currentHexagonPos[hexagonCount][0], currentHexagonPos[hexagonCount][1], 0.2f);
   	}
	drawBorders();
	drawPlayer(cameraPosition[0], cameraPosition[1]);
	//Clear screen and draw
   	glutSwapBuffers();
	glutPostRedisplay();
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
		 default:
			 break;
	 }
	 // if (cameraPositon[0] > PLAYFIELDSIZE) { cameraPosition[0] = PLAYFIELDSIZE; }
	 //Keep the player inside the drawBorders / boundary.
	 float halfPlayerSize = PLAYERSIZE / 2.0f;
	 cameraPosition[0] = (cameraPosition[0] > PLAYFIELDSIZE - halfPlayerSize) ? PLAYFIELDSIZE - halfPlayerSize : cameraPosition[0];
	 cameraPosition[0] = (cameraPosition[0] < -PLAYFIELDSIZE + halfPlayerSize) ? -PLAYFIELDSIZE + halfPlayerSize : cameraPosition[0];
	 cameraPosition[1] = (cameraPosition[1] > PLAYFIELDSIZE - halfPlayerSize) ? PLAYFIELDSIZE - halfPlayerSize : cameraPosition[1];
	 cameraPosition[1] = (cameraPosition[1] < -PLAYFIELDSIZE + halfPlayerSize) ? -PLAYFIELDSIZE + halfPlayerSize : cameraPosition[1];
};

int main(int argc, char **argv) {
   	//pre-configure  game layout
   	setupHexagons();
   	//Initialize GLUT
   	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
   	//Window Creation
   	glutInitWindowSize(1280, 720);
   	glutInitWindowPosition(200, 100);
   	glutCreateWindow("Catch the honey");
   	//When the display needs redrawing
   	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunc);
   	//Continue until user quits
   	glutMainLoop();
   	return 0;
}