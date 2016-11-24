/*
3GC3 Assignment #3


By: Ben Miller and Jack Snopek
*/

// Requirements to run on OSX
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

// Rest of requirements
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Globals
float camPos[] = {1, 10, 4.42f}; // This is where the camera is

void keyboard(unsigned char key, int xIn, int yIn){

	switch(key){
		case 'q':
			exit(0);
	}

}

void init(void){

	glClearColor(1, 1, 1, 0);	// Clear the screen
	glColor3f(1, 1, 1);			// Sets the curent drawing colour

	glMatrixMode(GL_PROJECTION);	// Specify the current matrix
	glLoadIdentity();			// Replace current Matrix w/ identity matrix
	gluPerspective(45, 1, 1, 100);	// Sets a perspective projection matrix
}


/*
The meat goes here, display f'n. GLUT displays this callback
function, clears the screen, sets the camera pos., draws the 
ground plane and the movable box
*/
void display(void){

	glClear(GL_COLOR_BUFFER_BIT); // Clear buffers to preset vals

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);
	glColor3f(0, 0, 0);

	glTranslatef(0.0f, 0.0f, -5.0f); 

	glutWireCube(2.0f);

	// Flush out to a single buffer
	glFlush();	// Forces execution of GL commands in finite time
}

/*
Main function -- the program entry point!
*/
int main(int argc, char** argv){

	glutInit(&argc, argv); 	// Initializes the GLUT library
	glutInitDisplayMode(GLUT_RGBA);	// Sets the initial display mode

	glutInitWindowPosition(50,50);
	glutInitWindowSize(640,480);

	glutCreateWindow("Intro to 3D Objects");	// Creates window and title!

	glutDisplayFunc(display);	// Registers f'n display as callback f'n
	glutKeyboardFunc(keyboard);

	init();

	//OtherCall b -- Would take another H file and call it b
	//b.hello(); call another function from another prog. but why
	// I guess to make building blocks that would help to build
	// A HOUSE! :)

	glutMainLoop();	// Enters the GLUT event processing loop

	return(0);
}
