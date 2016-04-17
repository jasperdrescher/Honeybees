//#include <math.h>
//#include <cstdlib>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//
////Data structures
//typedef struct _Vector {
//	double x, y, z;
//} Vector;
//
////Constants
//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = 600;
//const double PI = 3.14159265;
//
////Vars
//double radian;
//double speed = 10;
//double rot; //rotation
//
////Vectors
//Vector pos;
//Vector vel;
//Vector dir;
//Vector dis;
//Vector mouseCoords;
//
//void display(void) {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//	glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, -100, 100);
//	//Drawing
//	glColor3f(1, 0, 0);
//	glTranslated(pos.x, pos.y, 0);
//	glRotatef(rot, 0, 0, 1);
//	glutSolidTeapot(10);
//
//	glFlush();
//	glutSwapBuffers();
//}
//
//void mouse(int btn, int state, int x, int y) {
//	mouseCoords.x = x - SCREEN_WIDTH / 2;
//	mouseCoords.y = -y + SCREEN_HEIGHT / 2;
//}
//
//void move() {
//	dis.x = mouseCoords.x - pos.x;
//	dis.y - mouseCoords.y - pos.y;
//	
//	if (sqrt(dis.y*dis.y + dis.x*dis.x) < speed) {
//		pos.x = mouseCoords.x;
//		pos.y = mouseCoords.y;
//
//	}
//	else {
//		radian = atan2(dis.y, dis.x);
//		pos.x += cos(radian) * speed;
//		pos.y += sin(radian) * speed;
//		rot = radian * 180 / PI;
//	}
//}
//
//void update(int value) {
//	move();
//	glutPostRedisplay();
//	glutTimerFunc(10, update, 0);
//}
//
//void init(void) {
//	/* Initialize GLUT */
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	/* Window Creation */
//	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
//	glutCreateWindow("Catch the honey");
//	/* When the display needs redrawing... */
//	glutDisplayFunc(display);
//	glutMouseFunc(mouse);
//	glutTimerFunc(25, update, 0);
//	glClearColor(1, 1, 1, 1);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glMatrixMode(GL_MODELVIEW);
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	init();
//	glutMainLoop();
//	return 0;
//}