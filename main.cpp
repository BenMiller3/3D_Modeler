/*
3GC3 Assignment #3


By: Ben Miller and Jack Snopek
*/

#include "header.h"
#include "SceneObject.h"

//Global Variables
float camPos[] = {1, 2, 4.42f}; 
float camUp[] = { 0, 1, 0 };//up vector of the camera
float camTarget[] = { 0, 0, 0 };	//where the camera is looking at
float lightPos[3] = {3, 3, 3};
std::vector<SceneObject> sceneObjects;
int selectedObject = -1;


void SpawnObject()
{
	//SceneObject* obj1 = new SceneObject;
	//SceneObject  = new SceneObject();
	SceneObject obj1;
	sceneObjects.push_back(obj1);
}

void TranslateSelected(char direction, float multiplier)
{
	if(direction == 'x')
	{
		sceneObjects[selectedObject].Translate(multiplier, 0 ,0);
	}
	if(direction == 'y')
	{
		sceneObjects[selectedObject].Translate(0 , multiplier ,0);
	}
	if(direction == 'z')
	{
		sceneObjects[selectedObject].Translate(0, 0 , multiplier);
	}
}

void RotateSelected(char direction, float multiplier)
{
	if(direction == 'x')
	{
		sceneObjects[selectedObject].Rotate(multiplier, 0 ,0);
	}
	if(direction == 'y')
	{
		sceneObjects[selectedObject].Rotate(0 , multiplier ,0);
	}
	if(direction == 'z')
	{
		sceneObjects[selectedObject].Rotate(0, 0 , multiplier);
	}
}

void ScaleSelected(char direction, float multiplier)
{
	if(direction == 'x')
	{
		sceneObjects[selectedObject].Scale(multiplier, 0 ,0);
	}
	if(direction == 'y')
	{
		sceneObjects[selectedObject].Scale(0 , multiplier ,0);
	}
	if(direction == 'z')
	{
		sceneObjects[selectedObject].Scale(0, 0 , multiplier);
	}
}

void keyboard(unsigned char key, int xIn, int yIn)
{
	if(key == '1')
		{
			SpawnObject(); return;
		}

	else if(selectedObject >= 0 && selectedObject < sceneObjects.size())
	{
		int mod = glutGetModifiers();

		if (key == 'x' || key == 'X'){
			if (mod == GLUT_ACTIVE_SHIFT){
				TranslateSelected('x', -0.1f);
			}
			else{
				TranslateSelected('x', 0.1f); 
			}
		}
		else if (key == 'w' || key == 'W'){
				if ( mod == GLUT_ACTIVE_SHIFT){
					RotateSelected ('x', -10);
				}
				else {
					RotateSelected ('x', 10);
				}	
		}
		else if (key == 'i' || key == 'I'){
			if ( mod == GLUT_ACTIVE_SHIFT){
					ScaleSelected ('x', -0.1f);
				}
				else {
					ScaleSelected ('x', 0.1f);
				}	
		}

		//////////////////////////YYYYYYYYYYYYYYYYYYYYYYYYYYY/////////////////////////


		else if (key == 'y' || key == 'Y'){
			if (mod == GLUT_ACTIVE_SHIFT){
				TranslateSelected('y', -0.1f);
			}
			else{
				TranslateSelected('y', 0.1f); 
			}
		}
		else if (key == 'a' || key == 'A'){
				if ( mod == GLUT_ACTIVE_SHIFT){
					RotateSelected ('y', -10);
				}
				else {
					RotateSelected ('y', 10);
				}	
		}
		else if (key == 'j' || key == 'J'){
			if ( mod == GLUT_ACTIVE_SHIFT){
					ScaleSelected ('y', -0.1f);
				}
				else {
					ScaleSelected ('y', 0.1f);
				}	
		}

		///////////////////////////ZZZZZZZZZZZZZZZZZZZZZZZZZZZ////////////////////////

		else if (key == 'z' || key == 'Z'){
			if (mod == GLUT_ACTIVE_SHIFT){
				TranslateSelected('z', -0.1f);
			}
			else{
				TranslateSelected('z', 0.1f); 
			}
		}
		else if (key == 's' || key == 'S'){
				if ( mod == GLUT_ACTIVE_SHIFT){
					RotateSelected ('z', -10);
				}
				else {
					RotateSelected ('z', 10);
				}	
		}
		else if (key == 'k' || key == 'K'){
			if ( mod == GLUT_ACTIVE_SHIFT){
					ScaleSelected ('z', -0.1f);
				}
				else {
					ScaleSelected ('z', 0.1f);
				}	
		}
	}

}

void DrawObjects()
{
	//printf("%i", sceneObjects.size());
	//sceneObjects[0].Draw();
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		
		sceneObjects[i].Draw();
	}
}

void EnableLighting()
{
	//Turn the lighting on, set up culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	
	//Normalize normals
	glEnable(GL_NORMALIZE);

	//turn on light 
	glEnable(GL_LIGHT0);

	//light colour
	float amb[4] = {0.1f, 0.1f, 0.1f, 1};
	float dif[4] = {0.5f, 0.5f, 0.5f, 1};
	float spc[4] = {0.5f, 0.5f, 0.5f, 1};
	

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spc);

	float pos[4] = { lightPos[0], lightPos[1], lightPos[2], 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

void init(void){

	glClearColor(0.5f, 0.7f, 0.95f, 1);
	glColor3f(1, 1, 1);			

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();			
	gluPerspective(45, 1, 1, 100);	

	glEnable(GL_DEPTH_TEST); //2nd: enable the depth test and enable lights

	EnableLighting();
	glShadeModel(GL_SMOOTH);
}


void RayCast(int mouseX, int mouseY)
{
	double matModelView[16], matProjection[16]; 
	int viewport[4]; 

	double m_start[4];
	double m_end[4];

	// get matrix and viewport:
	glGetDoublev( GL_MODELVIEW_MATRIX, matModelView ); 
	glGetDoublev( GL_PROJECTION_MATRIX, matProjection ); 
	glGetIntegerv( GL_VIEWPORT, viewport ); 

	// window pos of mouse, Y is inverted on Windows
	double winX = (double)mouseX; 
	double winY = viewport[3] - (double)mouseY; 

	// get point on the 'near' plane (third param is set to 0.0)
	gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
			viewport, &m_start[0], &m_start[1], &m_start[2]); 

	// get point on the 'far' plane (third param is set to 1.0)
	gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
			viewport, &m_end[0], &m_end[1], &m_end[2]); 

	
	//CREATE SORTED LIST FOR SELECTIONS HERE
	////////////////////////////////////////
	/////////////////////////////////////////
	//////////////////////////////////////////

	
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i].selected = false;	
		selectedObject = -1;	
	}

	std::vector<float> hitDistances;
	std::vector<int> hitIndexes;

	for (int i = 0; i < sceneObjects.size(); i++)
	{
		//printf("%i", i);
		if(sceneObjects[i].Select(m_start[0], m_start[1], m_start[2], m_end[0], m_end[1], m_end[2], camPos[0], camPos[1], camPos[2]))
		{
			printf("Hit\n");
			sceneObjects[i].selected = true;
			hitIndexes.push_back(sceneObjects[i].distanceToIntersect);
			selectedObject = i;
			break;
		}
		else
		{
			printf("Miss\n");
		}
	}


	// now you can create a ray from m_start to m_end
}

void mouse(int btn, int state, int mouseX, int mouseY)
{
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
				RayCast(mouseX, mouseY);
		}	
}

void display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //3rd: clear the depth channe;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2],
			  camTarget[0], camTarget[1], camTarget[2],
			  camUp[0], camUp[1], camUp[2]);
	glColor3f(0, 0, 0);

	//glTranslatef(0.0f, 0.0f, 0.0f); 
	DrawObjects();
	
	glutSwapBuffers();	
}

void FPS(int val) {
	glutPostRedisplay();
	//Cinematic frame rate
	glutTimerFunc(17, FPS, 0); 
}


void reshape(int w, int h)
{
	//Windoresizing stuff
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)((w + 0.0f) / h), 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void callBackInit() {
	//Set up
	glutDisplayFunc(display);	
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	//glutSpecialFunc(special);

	glutReshapeFunc(reshape);
	glutTimerFunc(0, FPS, 0);
}

int main(int argc, char** argv)
{


	//PrepareSceneObjects();

	glutInit(&argc, argv); 	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);  //1st: enable frame buffer for depth

	glutInitWindowPosition(50,50);
	glutInitWindowSize(800,600);

	glutCreateWindow("Intro to 3D Objects");	
	

	callBackInit();
	init();

	glutMainLoop();	// Enters the GLUT event processing loop

	return(0);
}
