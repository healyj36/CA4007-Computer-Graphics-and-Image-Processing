#include <GL/gl.h>
#include <GL/glext.h>
#include <H:\glut.h>
#include <math.h>
#include <stdio.h>

// gcc Rotate.c -o Rotate glut32.lib -lopengl32 -lglu32

float theta = M_PI/4;
int windowY = 500;
int windowX = 500;

void drawSquare(float x, float y) {
	glBegin(GL_POLYGON);
		glVertex2f(-x,-y);
		glVertex2f(-y,x);
		glVertex2f(x,y);
		glVertex2f(y,-x);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat x=cos(theta), y=sin(theta);
	
	drawSquare(x, y);

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

void spinAntiClockwise() { // to make the scene anti spin clockwise
	theta += 0.0001;
	if(theta > 2*M_PI)
		theta -= 2*M_PI;
	glutPostRedisplay();

	return;
}

void MyMouse(GLint x, GLint y) {
	if (x > (windowX/2))
		glutIdleFunc(spinAntiClockwise);
	else
		glutIdleFunc(spinClockwise);

	GLfloat x1=cos(theta), y1=sin(theta);
	
	drawSquare(x1, y1);

	glFlush();	
	return;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(windowX,windowY);
	glutCreateWindow("Rotate");
	glutDisplayFunc(display);
	glutPassiveMotionFunc(MyMouse);
	glutIdleFunc(spinClockwise);
	glutMainLoop();
}
