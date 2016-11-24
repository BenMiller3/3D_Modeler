/*
3GC3 Assignment #3


By: Ben Miller and Jack Snopek
*/

#include "header.h"

//Global Variables
float camPos[] = {1, 10, 4.42f}; 

void keyboard(unsigned char key, int xIn, int yIn){

	switch(key){
		case 'q':
			exit(0);
	}

}

void init(void){

	glClearColor(1, 1, 1, 0);	
	glColor3f(1, 1, 1);			

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();			
	gluPerspective(45, 1, 1, 100);	
}

void display(void){

	glClear(GL_COLOR_BUFFER_BIT); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);
	glColor3f(0, 0, 0);

	glTranslatef(0.0f, 0.0f, -5.0f); 
	glutWireCube(2.0f);
	
	glFlush();	
}

int main(int argc, char** argv){

	glutInit(&argc, argv); 	
	glutInitDisplayMode(GLUT_RGBA);	

	glutInitWindowPosition(50,50);
	glutInitWindowSize(640,480);

	glutCreateWindow("Intro to 3D Objects");	

	glutDisplayFunc(display);	
	glutKeyboardFunc(keyboard);

	init();

	glutMainLoop();	// Enters the GLUT event processing loop

	return(0);
}
