#include <GL/gl.h>
#include <GL/glext.h>
#include <H:\glut.h>

// gcc Brush.c -o Brush glut32.lib -lopengl32 -lglu32
// does not decrease in brightness

float brushWidth = 10.0;
float brushBrightness = 10.0;
float red = 0.0;
float green = 0.0;
float blue = 0.0;

enum {
  MENU_BRUSH_WIDTH_LARGE,
  MENU_BRUSH_WIDTH_NORMAL,
  MENU_BRUSH_WIDTH_SMALL,
  MENU_BRUSH_COLOUR_RED,
  MENU_BRUSH_COLOUR_GREEN,
  MENU_BRUSH_COLOUR_BLUE
};

void display(void) {
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
	return;
}

void MyMouse2(GLint x, GLint y) {
	glColor3f(red,green,blue);
	glPointSize(brushWidth);
	glBegin(GL_POINTS);
		glVertex2f((x-250.0)/250.0,-(y-250.0)/250.0);
	glEnd();

	glFlush();	

	brushWidth = brushWidth - 0.1;
	
	return;
}

void SelectFromMenu(int idCommand) {
	switch (idCommand) {
		case MENU_BRUSH_WIDTH_LARGE:
			brushWidth = 30.0;
			break;
		case MENU_BRUSH_WIDTH_NORMAL:
			brushWidth = 20.0;
			break;      
		case MENU_BRUSH_WIDTH_SMALL:
			brushWidth = 10.0;
			break;   
		case MENU_BRUSH_COLOUR_RED:
			red = 1.0;
			green = 0.0;
			blue = 0.0;
			break;
		case MENU_BRUSH_COLOUR_GREEN:
			red = 0.0;
			green = 1.0;
			blue = 0.0;
			break;
		case MENU_BRUSH_COLOUR_BLUE:
			red = 0.0;
			green = 0.0;
			blue = 1.0;
			break;
	}
	glutPostRedisplay(); // menu selection requires a redraw
}

int BuildPopupMenu(void) {
	int menu;
	menu = glutCreateMenu(SelectFromMenu);
	glutAddMenuEntry("Large brush", MENU_BRUSH_WIDTH_LARGE);
	glutAddMenuEntry("Normal brush", MENU_BRUSH_WIDTH_NORMAL);
	glutAddMenuEntry("Small brush", MENU_BRUSH_WIDTH_SMALL);
	glutAddMenuEntry("Red paint", MENU_BRUSH_COLOUR_RED);
	glutAddMenuEntry("Green paint", MENU_BRUSH_COLOUR_GREEN);
	glutAddMenuEntry("Blue paint", MENU_BRUSH_COLOUR_BLUE);
	return menu;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutCreateWindow("Brush");
	glutDisplayFunc(display);
	glutMotionFunc(MyMouse2);
	BuildPopupMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON); // menu opens when right mouse button is pressed
	glutMainLoop();
}
