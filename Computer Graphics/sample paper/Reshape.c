#include <GL/gl.h>
#include <GL/glext.h>
#include <H:\glut.h>

// gcc Reshape.c -o Reshape glut32.lib -lopengl32 -lglu32

enum {
  MENU_RED,
  MENU_GREEN,
  MENU_BLUE,
};

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_POLYGON);
		glVertex2f(-0.5,-0.5);
		glVertex2f(-0.5,0.5);
		glVertex2f(0.5,0.5);
		glVertex2f(0.5,-0.5);
	glEnd();

	glFlush();
	return;
}

void MyReshape(GLsizei w, GLsizei h) {
	// maintain aspect ratio when resizing the window
	if(w>h) {
        glViewport((w-h)/2, 0, h, h);
    } else {
        glViewport(0, (h-w)/2, w, w);
	}
	return;
}

void SelectFromMenu(int idCommand) {
	switch (idCommand) {
		case MENU_RED:
			glColor3f(1.0, 0.0, 0.0);
			break;
		case MENU_GREEN:
			glColor3f(0.0, 1.0, 0.0);
			break;      
		case MENU_BLUE:
			glColor3f(0.0, 0.0, 1.0);
			break;
	}
	glutPostRedisplay(); // menu selection requires a redraw
}

int BuildPopupMenu(void) {
	int menu;
	menu = glutCreateMenu(SelectFromMenu);
	glutAddMenuEntry("Change colour to red", MENU_RED);
	glutAddMenuEntry("Change colour to green", MENU_GREEN);
	glutAddMenuEntry("Change colour to blue", MENU_BLUE);
	return menu;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("reshape");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	BuildPopupMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON); // menu opens when right mouse button is pressed
	glutMainLoop();
}