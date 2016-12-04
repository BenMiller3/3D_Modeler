/*
3GC3 Assignment #3


By: Ben Miller and Jack Snopek
*/

#include "header.h"
#include "SceneObject.h"

using namespace std;

//Global Variables
float camPos[] = {1, 2, 4.42f}; 
float camUp[] = { 0, 1, 0 };//up vector of the camera
float camTarget[] = { 0, 0, 0 };	//where the camera is looking at
float lightPos[3] = {3, 3, 3};
std::vector<SceneObject> sceneObjects;
int selectedObject = -1;

int colourOption = 1;	// Materials 1-5
std::vector<int> objectTypes;
std::vector<int> materialTypes;

float angle = 0;
float angle2 = 0;


void SpawnObject()
{
	SceneObject obj1;
	sceneObjects.push_back(obj1);
}

void TranslateSelected(char direction, float multiplier)
{
	if(direction == 'x') sceneObjects[selectedObject].Translate(multiplier, 0 ,0);
	if(direction == 'y') sceneObjects[selectedObject].Translate(0 , multiplier ,0);
	if(direction == 'z') sceneObjects[selectedObject].Translate(0, 0 , multiplier);
}

void RotateSelected(char direction, float multiplier)
{
	if(direction == 'x') sceneObjects[selectedObject].Rotate(multiplier, 0 ,0);
	if(direction == 'y') sceneObjects[selectedObject].Rotate(0 , multiplier ,0);
	if(direction == 'z') sceneObjects[selectedObject].Rotate(0, 0 , multiplier);
}

void ScaleSelected(char direction, float multiplier)
{
	if(direction == 'x') sceneObjects[selectedObject].Scale(multiplier, 0 ,0);
	if(direction == 'y') sceneObjects[selectedObject].Scale(0 , multiplier ,0);
	if(direction == 'z') sceneObjects[selectedObject].Scale(0, 0 , multiplier);
}

void ResetScene(){
	sceneObjects.clear();
}

void SaveScene(){
	cout << "Please enter a name to save the file as: ";
	string input;
	cin >> input;

	string filename = input + ".txt";
	
	/*
	ofstream myfile;
	myfile.open(filename);

	for(int i = 0; i > sceneObjects.size(); i++){
		myfile >> sceneObjects[i];
	}
	
	myfile.close();
	*/

	cout << endl << "You successfully saved the file as " << filename << endl;
}

void LoadScene(){
	cout << "Please enter the filename of the configuration you want to load: ";
	string saveFile;
	cin >> saveFile;

	/*
	ofstream oldFile;
	oldFile.open(saveFile);

	if(oldFile.is_open()){
		while(getline (oldFile, line)){
			sceneObjects.push_back(line);
		}
	}
	myfile.close();
	*/

	cout << "Loading previous scene " << saveFile;
}

void keyboard(unsigned char key, int xIn, int yIn)
{
	if(key == 'r'){
		ResetScene();
	}

	if(key == 'd'){
		angle+= 1;
	}
	if(key == 'D'){
		angle -= 1;
	}
	if(key == 'f'){
		angle2 += 1;
	}
	if(key == 'F'){
		angle2 -= 1;
	}
	if(key == 'l'){
		//LoadScene();
	}
	if(key == 's'){
		//SaveScene();
	}

	// keys 1-5 = different material selections
	if(key == '1') {
		colourOption = 1;
		if(selectedObject >= 0){
			materialTypes[selectedObject] = 1;
		}
	}
	if(key == '2') {
		colourOption = 2;
		if(selectedObject >= 0){
			materialTypes[selectedObject] = 2;
		}
	}
	if(key == '3') {
		colourOption = 3;
		if(selectedObject >= 0){
			materialTypes[selectedObject] = 3;
		}
	}
	if(key == '4') {
		colourOption = 4;
		if(selectedObject >= 0){
			materialTypes[selectedObject] = 4;
		}
	}
	if(key == '5') {
		colourOption = 5;
		if(selectedObject >= 0){
			materialTypes[selectedObject] = 5;
		}
	}
	
	// key 6-9 and 0, change material
	if(key == '6')
		{
			objectTypes.push_back(2);
			materialTypes.push_back(colourOption);
			SpawnObject(); return;
		}
	if(key == '7')
		{
			objectTypes.push_back(3);
			materialTypes.push_back(colourOption);
			SpawnObject(); return;
		}
	if(key == '8')
		{
			objectTypes.push_back(4);
			materialTypes.push_back(colourOption);
			SpawnObject(); return;
		}
	if(key == '9')
		{
			objectTypes.push_back(5);
			materialTypes.push_back(colourOption);
			SpawnObject(); return;
		}
	if(key == '0')
		{
			objectTypes.push_back(1);
			materialTypes.push_back(colourOption);
			SpawnObject(); return;
		}

	if(key == 'q'){
		exit(0);
	}

	else if(selectedObject >= 0 && selectedObject < sceneObjects.size())
	{
		int mod = glutGetModifiers();

		// x values
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

		// y values
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

		// z values
		else if (key == 'z' || key == 'Z'){
			if (mod == GLUT_ACTIVE_SHIFT){
				TranslateSelected('z', -0.1f);
			}
			else{
				TranslateSelected('z', 0.1f); 
			}
		}
		else if (key == 'o' || key == 'O'){
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
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i].Draw(objectTypes[i],materialTypes[i]);
	}
}

void printInstructions(){
	cout << "\n\n\nCreated by: Ben Miller and Jack Snopek" << endl;
	cout << "Ben Miller, 001416516" << endl;
	cout << "Jack Snopek, 001408851\n\n" << endl;

	cout << "CONTROLS" << endl;
	cout << "Click an object to select it, once selected use the keys:\n" << endl;
	cout << "x,y,z to translate the object" << endl;
	cout << "a,o,w to rotate the object" << endl;
	cout << "i,j,k to scale the object" << endl;
	cout << "The SHIFT modifier will reverse all of the above transformations" << endl;

	cout << "\nTo CREATE an object press the following keys to create different shapes: " << endl;
	cout << "6 = Cone" << endl;
	cout << "7 = Sphere" << endl;
	cout << "8 = Cube" << endl;
	cout << "9 = Torus" << endl;
	cout << "0 = Teapot" << endl;

	cout << "\nTo change the MATERIAL of an object, select it and use the following keys to select a material: " << endl;
	cout << "1 = Ruby (default)" << endl;
	cout << "2 = Emerald" << endl;
	cout << "3 = Pearl" << endl;
	cout << "4 = Yellow Rubber" << endl;
	cout << "5 = Cyan Plastic" << endl;

	cout << "\nTo rotate the scene about its Y axis use the keys d and D" << endl;
	cout << "To rotate the scene about its Z axis use the keys f and F" << endl;

	cout << "\nTo DELETE an object from the scene, select it and then use the right mouse click to remove it" << endl;
	cout << "To RESET the scene back to its defaults and remove all objects, press the r key to RESET the scene" << endl;

	cout << "\nTo SAVE the current configuration to a text file press the l key and then enter the filename you wish to ";
	cout << "save the program as." << endl;

	//cout << "To LOAD a previous configuration ensure the .txt file is in the same directory as this program and then specify"
	//cout << " the filename at the prompt to load the previous configuration. This will overwrite the current scene." << endl;

	cout << "\nPress q at anytime to quit the program." << endl;
}


void init(void){

	glClearColor(0.5f, 0.7f, 0.95f, 1);
	glColor3f(1, 1, 1);			

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();			
	gluPerspective(45, 1, 1, 100);	

	glEnable(GL_DEPTH_TEST); //2nd: enable the depth test and enable lights
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
			//printf("Hit\n");
			hitDistances.push_back(sceneObjects[i].distanceToIntersect);
			hitIndexes.push_back(i);			
		}
		else
		{
			//printf("Miss\n");
		}
	}

	float biggestDistSoFar = 9999999;
	int indexNow = -1;
	for (int i = 0; i < hitDistances.size(); i++)
	{
		if(hitDistances[i] < biggestDistSoFar)
		{
			//printf("Big Dist Now Is %f\n", hitDistances[i] );
			biggestDistSoFar = hitDistances[i];
			indexNow = hitIndexes[i]; 
		}
	}

	if(indexNow >= 0)
	{
		sceneObjects[indexNow].selected = true;
		selectedObject = indexNow;
	}
}

void mouse(int btn, int state, int mouseX, int mouseY)
{
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
				RayCast(mouseX, mouseY);
		}

	// On right click, delete objects from scene	
	if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && selectedObject >= 0 && selectedObject < sceneObjects.size())
		{
				TranslateSelected('x', 99999);
		}	
}

void DrawGroundPlane(){

	glPushMatrix();

	glPushMatrix();
	float m_amb[] = {0.0215, 0.1745, 0.0215};
	float m_dif[] = {0.07568, 0.61424, 0.07568};
	float m_spec[] = {0.2, 0.2, 0.2};	
	float shiny = 0.6;

	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	glColor3f(0,0,0);

	// Ground 
	glPushMatrix();
		glColor3f(0.5,0.5,0.5);
		glTranslatef(0,-2,1);
		glScalef(1.1,0.1,1);;
		glutSolidCube(10);
		glColor3f(0,0,0);
		glutWireCube(10);
	glPopMatrix();


	glPopMatrix();


	// Left wall
	glPushMatrix();
		glColor3f(1,1,1);
		glRotatef(-22.5,0,1,0);
		glTranslatef(2,0,-5);
		glScalef(1,0.7,0.1);
		glutSolidCube(8);
		glColor3f(0,0,0);
		glutWireCube(8);
	glPopMatrix();

	// Right wall
	glPushMatrix();
		glColor3f(1,1,1);
		glRotatef(22.5,0,1,0);
		glTranslatef(-2,0,-5);
		glScalef(1.2,0.7,0.1);
		glutSolidCube(8);
		glColor3f(0,0,0);
		glutWireCube(8);
	glPopMatrix();

	glPopMatrix();
}

void display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //3rd: clear the depth channe;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2],
			  camTarget[0], camTarget[1], camTarget[2],
			  camUp[0], camUp[1], camUp[2]);
	glColor3f(0, 0, 0);

	// Lighting
     glPushMatrix();
         glEnable(GL_COLOR_MATERIAL);
         glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
        
        float pos1[] = {1,1,1,0};
        float amb1[4] = {1,1,1,1};
        float diff1[4] = {0.5, 0.5, 0.5, 1};
        float spec1[4] = {1, 1, 1, 1};

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glShadeModel(GL_SMOOTH);

        glLightfv(GL_LIGHT0, GL_POSITION, pos1);
 	 	glLightfv(GL_LIGHT0, GL_AMBIENT, amb1);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diff1);
        glLightfv(GL_LIGHT0, GL_SPECULAR, spec1);
    glPopMatrix();

    glRotatef(angle,0,1,0);
    glRotatef(angle2,0,0,1);

	DrawObjects();
	DrawGroundPlane();


	
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

	glutReshapeFunc(reshape);
	glutTimerFunc(0, FPS, 0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv); 	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);  

	glutInitWindowPosition(50,50);
	glutInitWindowSize(800,600);

	glutCreateWindow("3GC3 - Assigment 3 (3D Modeler)");	
	
	printInstructions();

	callBackInit();
	init();

	glutMainLoop();	

	return(0);
}
