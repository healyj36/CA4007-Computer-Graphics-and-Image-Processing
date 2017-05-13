#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/glut.h>

// gcc cylinder.c -o cylinder glut32.lib -lopengl32 -lglu32
// don't know what "its axis along the y-axis" means
// missing part b

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

	glutWireCube(0.5);
	
	GLUquadricObj *MyCylinder;
	MyCylinder = gluNewQuadric();
	gluQuadricDrawStyle(MyCylinder, GLU_LINE);
	
	glRotatef(-90.0,0.0,1.0,0.0); // its axis along the y-axis???
	float height = 1.0;
	float radius = 0.5;
	gluCylinder(MyCylinder,radius,radius,height,12,12); // cylinder of height 1.0 and radius 0.5
	
	glFlush();
	return;
}


void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	glFrustum(-1.0,1.0,-1.0,1.0,0.5,3.0);
	glViewport(0,0,w,h);
	return;
}




int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cylinder");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);


	glutMainLoop();
}