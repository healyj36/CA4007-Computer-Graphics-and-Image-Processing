#include <GL/gl.h>
#include <GL/glext.h>
#include <H:\glut.h>
#include <stdio.h>

// gcc assignment2.c -o assignment2 glut32.lib -lopengl32 -lglu32

/*
This program displays three spheres.
  - sphere1 is at the origin. It is textured by the lenna image.
  - sphere2 is above and to the left of the origin. It is made of a brass material.
  - sphere3 is below and to the right of the origin. It is made of a red plastic material.
There are two lights.
  - A spotlight source to the left of the brass sphere.
  - A point light source to the right of the red plastic sphere.
The scene rotates when the left mouse button is held pressed inside the window.
  - The user can toggle the rotation by pressing 's' (clockwise or counter clockwise)
    - (A message will be printed into the console, nidicating which direction the scene will now spin)
  - The program starts with the spin value set to clockwise
A menu can be opened by the right mouse click, here we can;
  - Toggle spin direction (same as pressing 's')
  - Toggle polygon fill
  - Toggle texturing on all spheres
  - Exit the program
The program can be closed when the 'q' button is pressed
The program maintains its aspect ratio when the window is resized
  
NOTE: The texture is read in from a file 'texture.bin'
*/

enum {
  MENU_SPIN,
  MENU_POLYMODE,
  MENU_TEXTURING,
  MENU_EXIT_PROGRAM
};

typedef int BOOL;
#define TRUE 1
#define FALSE 0

static BOOL isTexturingDisabled = FALSE;
static BOOL isFillPolygons = TRUE;
static BOOL isRotateClockwise = TRUE;

typedef struct material {
	GLfloat ambient[4] ;
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} material;

material brass = {
	{0.329412, 0.223529, 0.027451, 1.0},
	{0.780392, 0.568627, 0.113725, 1.0},
	{0.992157, 0.941176, 0.807843, 1.0},
	21.794872
};

material red_plastic = {
	{0.0, 0.0, 0.0, 1.0},
	{0.5, 0.0, 0.0, 1.0},
	{0.7, 0.6, 0.6, 1.0},
	25.0
};

float no_shininess = 0.0f;
float low_shininess = 100.0f;
float high_shininess = 5.0f;

void materials(material *m, float shininess) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

GLubyte image[64][64][3];
static GLfloat theta[]={0.0,0.0,0.0}; // to make the scene spin
static GLint axis=2.0; // to make the scene spin
	
void makeSphere(int isTexture) {
	glEnable(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	// apply the image to the sphere only if isTexture == 1
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	GLUquadricObj *MySphere;
	MySphere = gluNewQuadric();
	gluQuadricTexture(MySphere,isTexture); // apply the image to the sphere only if isTexture == 1
	gluSphere(MySphere,0.5,50,50); // create sphere radius = 0.5; slices, stacks = 50, 50. slices and stacks defines how 'round' the sphere will be
}	

void display(void) {
	glClearColor(0.0,0.0,1.0,1.0); // scene colour (r,g,b,trasparency). set to blue
	glClear(GL_COLOR_BUFFER_BIT);
	
	glCullFace(GL_BACK); // for materials
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(theta[0],1.0,0.0,0.0); // to make the scene spin
	glRotatef(theta[1],0.0,1.0,0.0); // to make the scene spin
	glRotatef(theta[2],0.0,0.0,1.0); // to make the scene spin
	gluLookAt(1.0,1.0,0.0, 0.0,0.0,0.0, 0.0,1.0,0.0);

	GLfloat posSpotlight[4] = {1.0,2.0,3.0,1.0};
	GLfloat posLightPoint[4] = {-2.0,-4.0,-6.0,0.0};
	GLfloat defaultDiffuseSpecular[4] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, posSpotlight); // set position of the splotlight
	// GL_LIGHT0 and GL_LIGHT1->GL_LIGHT7 have different default values for GL_DIFFUSE and GL_SPECULAR
	// so we must set these values for GL_LIGHT1 to the same as GL_LIGHT0
	glLightfv(GL_LIGHT1, GL_DIFFUSE, defaultDiffuseSpecular); // set value of GL_DIFFUSE to default value of GL_LIGHT0
	glLightfv(GL_LIGHT1, GL_SPECULAR, defaultDiffuseSpecular); // set value of GL_SPECULAR to default value of GL_LIGHT0
	glLightfv(GL_LIGHT1, GL_POSITION, posLightPoint); // set position of the light point
	
	glEnable(GL_TEXTURE_2D);

	makeSphere(1); // make center sphere, with lenna image texturing
	
	glTranslatef(0.0,1.0,1.0); // translate up 1.0 and to the left 1.0

	/// enable lighting and materials after creating a textured sphere, so as not to apply the material to that sphere ///
	if(!isTexturingDisabled) { // if texturing hasn't been disabled...
		glEnable(GL_LIGHTING); // for lighting
		glEnable(GL_LIGHT0); // for spotlight source
		glEnable(GL_LIGHT1); // for point light source
		glEnable(GL_CULL_FACE); // for materials
	}
	
	materials(&brass, low_shininess);
	makeSphere(0); // make top left sphere, with brass texturing
	
	glTranslatef(0.0,-2.0,-2.0);  // translate down 2.0 and to the right 2.0
	
	materials(&red_plastic, high_shininess);
	makeSphere(0); // make bottom right sphere, with red plastic texturing
	
	/// disable lighting and materials after creating the material spheres, so as not to apply the material to the other sphere after redisplay ///
	if(!isTexturingDisabled) { // if texturing hasn't been disabled...
		glDisable(GL_LIGHTING); // for lighting
		glDisable(GL_LIGHT0); // for spotlight source
		glDisable(GL_LIGHT1); // for point light source
		glDisable(GL_CULL_FACE); // for materials
	}
	glFlush();
	return;
}

void spinSphereCounterClockwise() { // to make the scene spin counter clockwise
	theta[axis]+=0.1; // increasing this number increases the speed
	if(theta[axis]>360.0) // if the angle reaches 360, reset it back to 0
		theta[axis]-=360.0;
	glutPostRedisplay();
}

void spinSphereClockwise() { // to make the scene spin clockwise
	theta[axis]-=0.1; // increasing this number increases the speed
	if(theta[axis]>360.0) // if the angle reaches 360, reset it back to 0
		theta[axis]-=360.0;
	glutPostRedisplay();
}

void MyReshape(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
//	glFrustum(-1.0,1.0,-1.0,1.0,1.0,3.0);
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
		case MENU_SPIN:
			isRotateClockwise = !isRotateClockwise; // toggle rotation direction
			if(isRotateClockwise) {
				printf("Set to rotate clockwise on left mouse click\n");
			} else {
				printf("Set to rotate counter clockwise on left mouse click\n");
			}
			break;
		case MENU_POLYMODE:
			isFillPolygons = !isFillPolygons; // toggle polygon fill or line
			glPolygonMode(GL_FRONT_AND_BACK, isFillPolygons ? GL_FILL : GL_LINE);
			break;      
		case MENU_TEXTURING:
			isTexturingDisabled = !isTexturingDisabled; // toggle texturing
			if(isTexturingDisabled) {
				glEnable(GL_LIGHTING);
			}
			else {
				glDisable(GL_LIGHTING);
			}
			break;   
		case MENU_EXIT_PROGRAM:
			printf("Bye!\n");
			exit(0); // close the program
			break;
	}
	glutPostRedisplay(); // menu selection requires a redraw
}

int BuildPopupMenu(void) {
	int menu;
	menu = glutCreateMenu(SelectFromMenu);
	glutAddMenuEntry("Toggle Spin Direction\ts", MENU_SPIN);
	glutAddMenuEntry("Toggle Polygon Fill", MENU_POLYMODE);
	glutAddMenuEntry("Toggle Texturing", MENU_TEXTURING);
	glutAddMenuEntry("Exit Program\tq", MENU_EXIT_PROGRAM);
	return menu;
}

void onKeyPress(unsigned char key, int x, int y) {
	if(key=='q') { // when q is pressed...
		printf("Bye!\n");
		exit(0); // ...close the program
	}
	if(key=='s') { // when s is pressed...
		isRotateClockwise = !isRotateClockwise; // ...toggle rotation direction
		if(isRotateClockwise) {
			printf("Set to rotate clockwise on left mouse click\n");
		} else {
			printf("Set to rotate counter clockwise on left mouse click\n");
		}
	}
}

void onClick(int button, int state, int x, int y) {
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		if(isRotateClockwise) {
			glutIdleFunc(spinSphereClockwise); // when the right button is pressed & toggle is set to clockwise, spin clockwise
		} else {
			glutIdleFunc(spinSphereCounterClockwise); // when the right button is pressed & toggle is set to counter clockwise, spin counter clockwise
		}
	}
	if(state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
		glutIdleFunc(NULL); // when the left button is released, stop spinning
	}
}

void passiveMouse(GLint x, GLint y) {
	if (x > 125 && x < 375 && y > 125 && y < 375) {
		printf("in\n");
	} else {
		printf("out\n");
	}
	glutPostRedisplay();
	return;
}

int main(int argc, char **argv) {
	/// read in texture into 'image' ///
	int i,j;
	FILE *fp;
	char buffer[4096],*pb;

	fp = fopen("texture.bin","r");
	fread(buffer, 4096,1,fp);

	pb = buffer;

	for(i=0; i<64; i++) {
	   for(j=0; j<64; j++) {		
			image[i][j][0]=(GLubyte)*pb;
			image[i][j][1]=(GLubyte)*pb;
			image[i][j][2]=(GLubyte)*pb;
			pb++;
		}
	}

	/// initialise ///
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("Spinning Spheres");
	glutDisplayFunc(display);
	glutKeyboardFunc(onKeyPress);
	glutMouseFunc(onClick);
	//glutPassiveMotionFunc(passiveMouse);
	printf("Press 'q' to quit\n");
	printf("Press 's' to toggle clockwise or counter clockwise scene rotation\n");
	//glutIdleFunc(spinsphere); // when window is idle (not being used i.e. always) make the scene spin
	glutReshapeFunc(MyReshape);
	BuildPopupMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON); // menu opens when right mouse button is pressed
	
	glutMainLoop();
}