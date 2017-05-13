#include <GL/gl.h>
#include <GL/glext.h>
#include <H:\glut.h>

// gcc Mouse.c -o Mouse glut32.lib -lopengl32 -lglu32

enum {
  MENU_CLEAR,
  MENU_EXIT
};
GLfloat x1,x2,y1,y2;
float windowHeight = 800.0;
float windowWidth = 500.0;
int clearDisplay = 0;

void display(void) {
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);
	glColor3f(1.0,0.0,0.0);

	if(!clearDisplay) {
		glBegin(GL_POLYGON);
			glVertex2f(x1,y1);
			glVertex2f(x1,y2);
			glVertex2f(x2,y2);
			glVertex2f(x2,y1);
		glEnd();
	}

	glFlush();
	return;
}

void MyMouse(GLint button, GLint state, GLint x, GLint y) {
	clearDisplay = 0;
	static int first=1;
	
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		if (first) {
			x1= (x-(windowHeight/2)) / (windowHeight/2); 
			y1= -(y-(windowWidth/2)) / (windowWidth/2);
		} else {
			x2= (x-(windowHeight/2)) / (windowHeight/2);
			y2= -(y-(windowWidth/2)) / (windowWidth/2);
			glutPostRedisplay();
		}
		first = !first;
	}
	return;
}

void SelectFromMenu(int idCommand) {
	switch (idCommand) {
		case MENU_CLEAR:
			clearDisplay = 1;
			break;
		case MENU_EXIT:
			exit(0);
			break;
	}
	glutPostRedisplay(); // menu selection requires a redraw
}

int BuildPopupMenu(void) {
	int menu;
	menu = glutCreateMenu(SelectFromMenu);
	glutAddMenuEntry("Clear screen", MENU_CLEAR);
	glutAddMenuEntry("Exit program", MENU_EXIT);
	return menu;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(windowHeight,windowWidth);
	glutCreateWindow("mouse");
	glutDisplayFunc(display);
	glutMouseFunc(MyMouse);
	BuildPopupMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON); // menu opens when right mouse button is pressed
	glutMainLoop();
}
