#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#ifdef __APPLE__
#  	include <OpenGL/gl.h>
#  	include <OpenGL/glu.h>
#  	include <GLUT/glut.h>
#else
#  	include <GL/gl.h>
#  	include <GL/glu.h>
#   include <GL/freeglut.h>
#	include <windows.h>
#endif

#include "Window.h"
#include "DrawMesh.h"
using namespace std;

//Object Variables
Window objWindow("perspective");
DrawMesh objDrawMesh;
int window1, window2;


float camPos[] = {0, 10, 0};
float light_pos[] = {-150,150,100,1.0};
float light_pos2[] = {150,150,-100,1.0};
bool randomGenerated = false, once = true, showlight = true;
int wireFrame = 0, viewMode = 0, randNumMeshSize = 0, lightCounter = 1, shaddingCounter = 1;


//Window size
void CreateDisplayWindow(int width, int height){
	objWindow.setWidth(width);
	objWindow.setHeight(height);

	objWindow.setPosX((glutGet(GLUT_SCREEN_WIDTH)-objWindow.getWidth())/2);
	objWindow.setPosY((glutGet(GLUT_SCREEN_HEIGHT)-objWindow.getHeight())/2);

	//Set the Window Size
	glutInitWindowSize(objWindow.getWidth(), objWindow.getHeight());
	//Set Window position
	glutInitWindowPosition(objWindow.getPosX(), objWindow.getPosY());
	//glutCreateWindow("3D Terrain");
}


void Lighting(){
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	if(showlight){
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}else{
		glDisable(GL_LIGHTING);
	}


	float amb[4] = {1, 1, 1, 1};
	float diff[4] = {1, 1, 1, 1};
	float spec[4] = {1, 1, 1, 1};


	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
	glLightf(GL_LIGHT0, GL_SHININESS, 100);

	glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
	glLightf(GL_LIGHT1, GL_SHININESS, 100);

	float mat_ambient[4] ={ 0.0f,0.05f,0.0f,1.0f };
	float mat_diffuse[4] ={ 0.4f,0.5f,0.4f,1.0f};
	float mat_specular[4] ={0.04f,0.7f,0.04f,1.0f };
	float shine =  10.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}
/*  display() - the OpenGL display function, this draws the screen
 *  it displays a spinning cube
 */
 void Display(){
 	//clear the screen
	glutSetWindow(window1);
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Lighting();

 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
 	gluLookAt(camPos[0],camPos[1],camPos[2], randNumMeshSize,0,randNumMeshSize, 0,1,0);

 	//draw the Terrain
 	objDrawMesh.drawTerrain(wireFrame);

 	//swap buffers - rendering is done to the back buffer, bring it forward to display
 	glutSwapBuffers();
 	//force a redisplay, to keep the animation running
 	//glutPostRedisplay();
}

void Display2(){
 	//clear the screen
	glutSetWindow(window2);
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Lighting();
 	
 	//draw the Terrain
 	objDrawMesh.draw2DTerrain(wireFrame);

 	//swap buffers - rendering is done to the back buffer, bring it forward to display
 	glutSwapBuffers();
 	//force a redisplay, to keep the animation running
 	//glutPostRedisplay();
 }
int randomeMeshSize(){
	return 50 + (rand() % (300 - 50 + 1));
}
void ResetMesh(){
	glClear(GL_COLOR_BUFFER_BIT);
	objDrawMesh.resetVertex();
	objDrawMesh.resetFace();
}
void SetMesh(){
	objDrawMesh.setMeshSize(randNumMeshSize);
	objDrawMesh.setAllVertex();
	objDrawMesh.setAllFace();
}
/*  KeyBoardAction -- the GLUT keyboard function
 *  key -- the key pressed
 *  x and y - mouse x and y coordinates at the time the function is called
 */
void KeyBoardAction(unsigned char key, int x, int y){
	//if the "q" key is pressed, quit the program
	if(key == 'q'){
		exit(0);
	}else if(key == 'r'){
		ResetMesh();
		randNumMeshSize = randomeMeshSize();
		SetMesh();
	}else if(key == 'w'){
		wireFrame++;
	}else if(key == 's'){
		shaddingCounter++;
		if (shaddingCounter % 2 == 0){
			glShadeModel(GL_FLAT);
		}else{
			glShadeModel(GL_SMOOTH);
		}
	}else if(key == 'l'){
		lightCounter++;
		if (lightCounter % 2 == 0){
			showlight = false;
		}else{
			showlight = true;
		}
	}else if(key == 'c'){
		ResetMesh();
		SetMesh();
		int randNum = 50 + (rand() % (200 - 50 + 1));
		glClear(GL_COLOR_BUFFER_BIT);
		for(int i = 0; i < randNum; i++){
			objDrawMesh.circleAlgorithm();
		}
	}else if(key == 'f'){
		ResetMesh();
		SetMesh();
		int randNum = 50 + (rand() % (200 - 50 + 1));
		glClear(GL_COLOR_BUFFER_BIT);
		for(int i = 0; i < randNum; i++){
			objDrawMesh.heightFault();
		}
	}/*else if(key == 'd'){
		ResetMesh();
		SetMesh();
		int randNum = 50 + (rand() % (200 - 50 + 1));
		glClear(GL_COLOR_BUFFER_BIT);
		//for(int i = 0; i < randNum; i++){
			//objDrawMesh.midPoint();
		//}
	}*/

	if(key == 'h'){
		light_pos[0] += 10;
		light_pos2[0] += 10;
	}else if(key == 'k'){
		light_pos[0] -= 10;
		light_pos2[0] -= 10;
	}
	if(key == 'u'){
		light_pos[2] += 10;
		light_pos2[2] += 10;
	}else if(key == 'j'){
		light_pos[2] -= 10;
		light_pos2[2] -= 10;
	}/*else if(key == 'v' || key == 'V'){
		viewMode++;
		if(viewMode%2 == 0){
			objWindow.setDisplay("perspective");
			objWindow.viewDisplay();
		}else{
			objWindow.setDisplay("ortho");
			objWindow.viewDisplay();
		}
	}*/
}

void KeyBoardSpecial(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
		if(camPos[0] < randNumMeshSize+20){
			camPos[0] += 1;
		}
	}else if(key == GLUT_KEY_RIGHT){
		if(camPos[0] > -20){
			camPos[0] -= 1;
		}
	}
	if(key == GLUT_KEY_UP){
		if(camPos[2] < randNumMeshSize+20){
			camPos[2] += 1;
		}
	}else if(key == GLUT_KEY_DOWN){
		if(camPos[2] > -20){
			camPos[2] -= 1;
		}
	}
	if(key == GLUT_KEY_HOME){
		if(camPos[1] > 10){
			camPos[1] -= 1;
		}
	}else if(key == GLUT_KEY_END){
		//if(camPos[1] < 50){
			camPos[1] += 1;
		//}
	}
	glutPostRedisplay();
}

void idle (void){
  glutSetWindow (window1);
  glutPostRedisplay ();
  glutSetWindow (window2);
  glutPostRedisplay ();
}
//Init
void glutCallbacks(){
	glutDisplayFunc(Display);
	glutKeyboardFunc(KeyBoardAction);
	glutSpecialFunc(KeyBoardSpecial);
  	glutIdleFunc (idle);
}
void glutCallbacks2(){
	glutDisplayFunc(Display2);
	glutKeyboardFunc(KeyBoardAction);
}
int main(int argc, char** argv){


	cout << "Enter meshsize between 50 to 300: " << endl;
	//ResetMesh();
	cin >> randNumMeshSize;

	cout << "----------- MENU COMMANDS -----------" << endl;
	cout << "r KEY------------ GENERATE RANDOM SIZE FLATE TERRAIN" << endl;
	cout << "l KEY ---------------- TOGGLE LIGHTING" << endl;
	cout << "w KEY --------------- TOGGLE WIRE MODE" << endl;
	cout << "s KEY -------------- TOGGLE SHADE MODE" << endl;
	cout << "f KEY -------------- GENERATE FAUL TERRAIN" << endl;
	cout << "c KEY -------------- GENERATE CIRCULE TERRAIN" << endl;
	cout << "h,k,u,j ------------ MOVE LIGHT" << endl;
	cout << "ARROW KEYS ------------ ROTATE TERRAIN" << endl;
	cout << "END KEY ----------- ZOOM INTO TERRAIN" << endl;
	cout << "HOME KEY ---------- ZOOM OUT OF TERRAIN" << endl;
	cout << "q ------------------------ EXIT" << endl;


	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);


	CreateDisplayWindow(600, 600);
	//Creates the Terrain window
	window1 = glutCreateWindow("3D Terrain");
	glutCallbacks();
	//enable Z buffer test, otherwise things appear in the order they're drawn
	glEnable(GL_DEPTH_TEST);
	Lighting();
	objWindow.viewDisplay();

	CreateDisplayWindow(500, 500);
	//Creates the Terrain window
	window2 = glutCreateWindow("2D Terrain");
	glutCallbacks2();
	

	SetMesh();



	//glMatrixMode(GL_MODELVIEW);
	//look down from a 45 deg. angle
	//glRotatef(45, 45, 45, 0);

	//Start the events of mainloop
	glutMainLoop();

	return 0;
}
