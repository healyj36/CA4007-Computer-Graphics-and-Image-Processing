#include <GL/gl.h>
#include <GL/glext.h>
#include <H:\glut.h>
#include <stdio.h>
#include <math.h>

// gcc Idle.c -o Idle glut32.lib -lopengl32 -lglu32

typedef int BOOL;
#define TRUE 1
#define FALSE 0

float theta = M_PI/4;
static BOOL isRotateClockwise = TRUE;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat x=cos(theta), y=sin(theta);

	glBegin(GL_POLYGON);
		glVertex2f(-x,-y);
		glVertex2f(-y,x);
		glVertex2f(x,y);
		glVertex2f(y,-x);
	glEnd();
	
	glFlush();
	return;
}

void spinClockwise() { // to make the scene spin clockwise
	theta -= 0.0001;
	if(theta > 2*M_PI)
		theta -= 2*M_PI;
	glutPostRedisplay();

	return;
}

void spinCounterClockwise() { // to make the scene spin counter clockwise
	theta += 0.0001;
	if(theta > 2*M_PI)
		theta -= 2*M_PI;
	glutPostRedisplay();

	return;
}

void onClick(int button, int state, int x, int y) {
	if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
		isRotateClockwise = !isRotateClockwise;
		
		if(isRotateClockwise) {
			glutIdleFunc(spinClockwise); // when the right button is pressed & toggle is set to clockwise, spin clockwise
		} else {
			glutIdleFunc(spinCounterClockwise); // when the right button is pressed & toggle is set to counter clockwise, spin counter clockwise
		}
		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("idle");
	glutDisplayFunc(display);
	glutIdleFunc(spinClockwise);
	glutMouseFunc(onClick);
	glutMainLoop();
}