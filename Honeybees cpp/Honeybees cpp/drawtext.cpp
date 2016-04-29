/*#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

void drawBitmapText(char *string, float x, float y, float z)
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}

void drawStrokeText(char*string, int x, int y, int z)
{
	char *c;
	glPushMatrix();
	glTranslatef(x, y + 8, z);
	// glScalef(0.09f,-0.08f,z);

	for (c = string; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(47, 79, 79); //not working?
	drawBitmapText("Hello world", 200, 200, 0);
	glutSwapBuffers();
}

// Main routine
// Set up OpenGL, hook up callbacks, and start the main loop
int main(int argc, char** argv)
{
	// Need to double buffer for animation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// Create and position the graphics window
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 360);
	glutCreateWindow("Solar System Demo");
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutReshapeFunc(reshape);
	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop();
	return(0);			// Compiler requires this to be here. (Never reached)
}*/