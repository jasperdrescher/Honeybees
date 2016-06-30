/*
* Please read the LICENSE.md and README.md files for credits, references, and the license.
* Keep in mind that this is my first attempt at writing a program in C++, so any feedback is appreciated.
* This file and its repository are available from: https://github.com/JasperDre/Honeybees.
*/

//Include libraries for this file.
#include <math.h>			//Standard definitions.
#include <cstdlib>			//Standard definitions.
#include <Windows.h>		//Standard definitions.
#include <GL/glew.h>		//GLEW.
#include <GL/freeglut.h>	//FreeGLUT.
#include <iostream>			//C++ I/O.
#include <stdlib.h>			//Standard definitions.

//Define symbolic replacements which are called frequently.
#define WINDOWWIDTH 768		//Define the width of the window.
#define WINDOWHEIGHT 768	//Define the height of the window.
#define PLAYERSIZE (0.2f + playerScore / 164.0f)	//Define the size of the player by a seed (0.2f) and increment it by the score (divided by a value).
#define PLAYFIELDSIZE 4.0f	//Define the size of the scene and borders.
#define CAMERAMOVESPEED 0.1f	//Define the speed which the camera moves by.
#define HEXAGONCOUNT 42		//Define the count of the hexagonal cells.
#define HEXAGONSIZE 0.25f	//Define the size of the hexagonal cells.
#define ENEMYSIZE 0.4f		//Define the size of the enemy.

//Declare variables.
using  namespace std;		//Make std accesible.

int windowID;				//Set the id of the window to acces it later on.
float playerScore = 0.0f;	//Set a seed for the score.
float currentHexagonPos[HEXAGONCOUNT][2];	//Create an array to store the position of the hexagons currentHexagonPos[count][x and y].
float currentEnemyPos[1][2];	//Create an array to store the position of the hexagons currentEnemyPos[count][x and y].
float cameraPosition[2] = { 0,0 };	//Create an array to store the coordinates of both axis (x and y).

const int font = (int)GLUT_BITMAP_9_BY_15;	//Set an integer to contain the font.
char scoreText[30];					//Array to store 30 characters. Text that is rendered on the screen to display the score.
char timeText[30];					//Array to store 30 characters. Text that is rendered on the screen to display the runtime.
double runtimeSeconds;		//Number of seconds since the game started (runtime).

//Gerenate a random number between a minimum and maximum value from a seed (rand()).
float randomFloat(float minValue, float maxValue) {
   	float random = ((float)rand() / (float)RAND_MAX);
   	float diff = maxValue - minValue;
   	float resultValue = random * diff;
   	return minValue + resultValue;
}

//Draw the player using a polygon.
void drawPlayer(float x, float y) {
	glColor3f(0.988, 0.815, 0.211);		//Set the color of the player.
	glBegin(GL_POLYGON);				//Use GL_POLYGON to draw a square by calculating the center of the camera position.
	glVertex2d(x - (PLAYERSIZE / 2), y + (PLAYERSIZE / 2));
	glVertex2d(x + (PLAYERSIZE / 2), y + (PLAYERSIZE / 2));
	glVertex2d(x + (PLAYERSIZE / 2), y - (PLAYERSIZE / 2));
	glVertex2d(x - (PLAYERSIZE / 2), y - (PLAYERSIZE / 2));
	glEnd();
}

//Draw the hexagonal cells using a polygon.
void drawHexagon(float x, float y, float size) {
   	glColor3f(0.980, 0.698, 0.172);		//Set the color of the honey.
   	glBegin(GL_POLYGON);		//Use GL_POLYGON to draw a hexagonal cell.
   	glVertex2d(-0.4 * size + x, 0.2 * size + y);
   	glVertex2d(-0.4 * size + x, -0.2 * size + y);
   	glVertex2d(0 * size + x, -0.4 * size + y);
   	glVertex2d(0.4 * size + x, -0.2 * size + y);
   	glVertex2d(0.4 * size + x, 0.2 * size + y);
   	glVertex2d(0 * size + x, 0.4 * size + y);
	glEnd();
}

//Draw the enemy using a polygon.
void drawEnemy(float x, float y, float size) {
	glColor3f(0.863, 0.078, 0.235);		//Set the color of the enemy.
	glBegin(GL_POLYGON);		//Use GL_POLYGON to draw a square.
	glVertex2d(x - (ENEMYSIZE / 2), y + (ENEMYSIZE / 2));
	glVertex2d(x + (ENEMYSIZE / 2), y + (ENEMYSIZE / 2));
	glVertex2d(x + (ENEMYSIZE / 2), y - (ENEMYSIZE / 2));
	glVertex2d(x - (ENEMYSIZE / 2), y - (ENEMYSIZE / 2));
	glEnd();
}

//Draw the borders of the playable area / field using a line between by 4 vertices.
void drawBorders() {
	glColor3f(1.0, 0.0, 0.0);	//Set the color of the borders.
	glBegin(GL_LINE_LOOP);		//Use GL_LINE_LOOP to draw a line from 4 vertices.
	glVertex2f(-PLAYFIELDSIZE, PLAYFIELDSIZE);
	glVertex2f(PLAYFIELDSIZE, PLAYFIELDSIZE);
	glVertex2f(PLAYFIELDSIZE, -PLAYFIELDSIZE);
	glVertex2f(-PLAYFIELDSIZE, -PLAYFIELDSIZE);
	glEnd();
}

//Scatter the hexagonal cells across the field using a random float.
void setupHexagons() {
   	for (int hexagonCount = 0; hexagonCount < HEXAGONCOUNT; hexagonCount++)	//For every hexagonal cell do the following...
   	{
   		currentHexagonPos[hexagonCount][0] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);	//Random value for the x-axis.
   		currentHexagonPos[hexagonCount][1] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);	//Random value for the y-axis.
   	}
}

//Place the enemy in the field using a random float.
void setupEnemy() {
	currentEnemyPos[0][0] = randomFloat(-PLAYFIELDSIZE + ENEMYSIZE, PLAYFIELDSIZE - ENEMYSIZE);		//Random value for the x-axis.
	currentEnemyPos[0][1] = randomFloat(-PLAYFIELDSIZE + ENEMYSIZE, PLAYFIELDSIZE - ENEMYSIZE);		//Random value for the y-axis.
}

//Check if two items (item 1 and item 2) have less than a certain distance (size) and return a true or false.
bool doesCollide(float item1[], float item2[], float size) {
   	float diffX = item1[0] - item2[0];		//Difference between the items on the x-axis.
   	float diffY = item1[1] - item2[1];		//Difference between the items on the y-axis.
   	float distance = sqrtf((diffX * diffX) + (diffY * diffY));		//Calculate the distance between the two items.
   	return distance < size;		//Check if the distance is less than the collision value.
}

//Check if the hexagonal cells are colliding using the boolean above. If so, change the position of one of them.
void updateHexagons() {
   	for (int hexagonOuter = 0; hexagonOuter < HEXAGONCOUNT - 1; hexagonOuter++) {
		//Only check the distance from the last one, which is more efficient.
   		for (int hexagonInner = hexagonOuter + 1; hexagonInner < HEXAGONCOUNT; hexagonInner++) {
   			if (doesCollide(currentHexagonPos[hexagonOuter], currentHexagonPos[hexagonInner], HEXAGONSIZE)) {
				currentHexagonPos[hexagonInner][0] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);	//Replace the current position on the x-axis with a random value within the borders.
				currentHexagonPos[hexagonInner][1] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);	//Replace the current position on the x-axis with a random value within the borders.
   			}
   		}
   	}
}

//Check if the player collides with a hexagonal cell or the enemy.
void checkPlayerCollision() {
	for (int hexagonIndex = 0; hexagonIndex < HEXAGONCOUNT; hexagonIndex++) {
		if (doesCollide(cameraPosition, currentHexagonPos[hexagonIndex], (HEXAGONSIZE + PLAYERSIZE) / 2)) {		//Check if the current camera / player position and hexagon are colliding.
			currentHexagonPos[hexagonIndex][0] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);	//Replace the current position on the x-axis with a random value within the borders.
			currentHexagonPos[hexagonIndex][1] = randomFloat(-PLAYFIELDSIZE + HEXAGONSIZE, PLAYFIELDSIZE - HEXAGONSIZE);	//Replace the current position on the x-axis with a random value within the borders.
			playerScore++;	//Increment the score everytime the player and a hexagon collide.
		}
	}
	if (doesCollide(cameraPosition, currentEnemyPos[0], (0.3f + PLAYERSIZE) / 2)) {		//Check if the current camera / player position and enemy are colliding.
		currentEnemyPos[0][0] = randomFloat(-PLAYFIELDSIZE + ENEMYSIZE, PLAYFIELDSIZE - ENEMYSIZE);		//Replace the current position on the x-axis with a random value within the borders.
		currentEnemyPos[0][1] = randomFloat(-PLAYFIELDSIZE + ENEMYSIZE, PLAYFIELDSIZE - ENEMYSIZE);		//Replace the current position on the x-axis with a random value within the borders.
		playerScore = 0.0f; //Reset the score everytime the player and enemy collide.
	}
}

//Move the enemy using a random float, changed everytime it's called.
void moveEnemy(int value) {
	currentEnemyPos[0][0] = (currentEnemyPos[0][0] > PLAYFIELDSIZE - ENEMYSIZE) ? -PLAYFIELDSIZE + ENEMYSIZE : currentEnemyPos[0][0] + randomFloat(-0.01, 0.1);		//Check if the current position is outside the borders. If so, move it back inside. If not, give it a new position on the x-axis.
	currentEnemyPos[0][1] = (currentEnemyPos[0][1] > PLAYFIELDSIZE - ENEMYSIZE) ? -PLAYFIELDSIZE + ENEMYSIZE : currentEnemyPos[0][1] + randomFloat(-0.01, 0.1);		//Check if the current position is outside the borders. If so, move it back inside. If not, give it a new position on the y-axis.
	glutTimerFunc(250, moveEnemy, 0);	//Redo this every 250 milliseconds.
	glutPostRedisplay();	//Request a redraw.
}

//Constrain the position of the camera, and therefore the player.
void constrainPlayerPos() {
	float halfPlayerSize = PLAYERSIZE / 2.0f;	//Calculate half the size of the player.
	//The following is an alternative to: if (cameraPositon[0] > PLAYFIELDSIZE) { cameraPosition[0] = PLAYFIELDSIZE; }.
	cameraPosition[0] = (cameraPosition[0] > PLAYFIELDSIZE - halfPlayerSize) ? PLAYFIELDSIZE - halfPlayerSize : cameraPosition[0];
	cameraPosition[0] = (cameraPosition[0] < -PLAYFIELDSIZE + halfPlayerSize) ? -PLAYFIELDSIZE + halfPlayerSize : cameraPosition[0];
	cameraPosition[1] = (cameraPosition[1] > PLAYFIELDSIZE - halfPlayerSize) ? PLAYFIELDSIZE - halfPlayerSize : cameraPosition[1];
	cameraPosition[1] = (cameraPosition[1] < -PLAYFIELDSIZE + halfPlayerSize) ? -PLAYFIELDSIZE + halfPlayerSize : cameraPosition[1];
}

//Set the projection to orthographic.
void setOrthographicProjection() {
	glMatrixMode(GL_PROJECTION);	//Set the projection to render the text correctly on the screen.
	glPushMatrix();		//
	glLoadIdentity();
	gluOrtho2D(0, WINDOWWIDTH, 0, WINDOWHEIGHT);
	glScalef(1, -1, 1);
	glTranslatef(0, -WINDOWHEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
}

//Reset the projection.
void resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);	//Put the projection back into the projection used by the gameplay.
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//Render the characters from a ASCII string.
void renderBitmapString(float x, float y, void *font, const char *displayText) {
	const char *pointerInString;
	glRasterPos2f(x, y);
	for (pointerInString = displayText; *pointerInString != '\0'; pointerInString++) {
		glutBitmapCharacter(font, *pointerInString);
	}
}

//Keyboard function called by GLUT on key-input.
void keyboardFunc(unsigned char key, int x, int y) {
	switch (key)	//Switch function to check which key is pressed and trigger an action.
	{
	case 'a':
	case 'A':
		cameraPosition[0] += CAMERAMOVESPEED;	//Move the player to the left, by a pre-defined speed.
		break;
	case 'd':
	case 'D':
		cameraPosition[0] -= CAMERAMOVESPEED;	//Move the player to the right, by a pre-defined speed.
		break;
	case 'w':
	case 'W':
		cameraPosition[1] += CAMERAMOVESPEED;	//Move the player up, by a pre-defined speed.
		break;
	case 's':
	case 'S':
		cameraPosition[1] -= CAMERAMOVESPEED;	//Move the player down, by a pre-defined speed.
		break;
	case 27:									//Escape key.
		glutDestroyWindow(windowID);			//Terminate the program cleanly.
		exit(0);								//Return a succesful exit value.
		break;
	default:
		cout << "Press escape or WASD.  All other characters are ignored" << endl;
		break;
	}
	constrainPlayerPos();
}

//Display callback from GLUT.
void display(void) {
	glLoadIdentity();
	gluLookAt(cameraPosition[0], cameraPosition[1], -1, cameraPosition[0], cameraPosition[1], 0, 0.0, 1.0, 0.0);	//Modify the camera.
   	updateHexagons();
	checkPlayerCollision();
   	glClearColor(1.000, 0.992, 0.878, 0);	//Set the background colour.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//Clear buffers to preset values. 
	resetPerspectiveProjection();
   	for (int hexagonCount = 0; hexagonCount < HEXAGONCOUNT; hexagonCount++) {	//Render the hexagonal cells.
   		drawHexagon(currentHexagonPos[hexagonCount][0], currentHexagonPos[hexagonCount][1], HEXAGONSIZE);
   	}
	drawEnemy(currentEnemyPos[0][0], currentEnemyPos[0][1], 0.3f);
	drawBorders();
	drawPlayer(cameraPosition[0], cameraPosition[1]);
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glColor3d(0.0, 0.0, 1.0);	//Set the colour of the text.
	renderBitmapString(0.1, 15, (void*)font, scoreText);
	renderBitmapString(0.1, 30, (void*)font, timeText);
	glPopMatrix();
   	glutSwapBuffers();
	glutPostRedisplay();
}

//Update values of the text to display on the screen.
void update(int value) {
	runtimeSeconds = glutGet(GLUT_ELAPSED_TIME) / 1000.0;	//Get the number of seconds since the program began.
	int scoreInt = (int)playerScore;	//Score of the player.
	int timeInt = (int)runtimeSeconds;	//Runtime in seconds.
	sprintf_s(scoreText, "Score: %2d", scoreInt);
	sprintf_s(timeText, "Time: %2d sec", timeInt);
	glutTimerFunc(500, update, 0);	//Update every 500 milliseconds.
	glutPostRedisplay();
}

//Start the main loop.
int main(int argc, char **argv) {
	cout << "Welcome to Honeybees.\n\
	- Use your keyboard to move.\n\
	- Press escape to quit.\n";
   	setupHexagons();
	setupEnemy();
   	glutInit(&argc, argv);	//Parsing command line parameters into GLUT.
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
   	glutInitWindowPosition(0, 0);
   	char windowTitle[30] = "Honeybees";	//Set the title of the window.
	windowID = glutCreateWindow(windowTitle);	//Create the window with the title and store the ID.
	glutDisplayFunc(display);
	glutTimerFunc(25, update, 0);
	glutTimerFunc(25, moveEnemy, 0);
	glutKeyboardFunc(keyboardFunc);
   	glutMainLoop();
   	return 0;
}