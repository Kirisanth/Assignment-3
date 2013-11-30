//
//  main.cpp
//  Assignment-3
//
//  Created by Kirisanth Subramaniam on 2013-11-23.
//  Copyright (c) 2013 Kirisanth Subramaniam. All rights reserved.
//

#include "objects.h"
#include <stdlib.h>
#include <GLUT/glut.h>
#include <iostream>
#include <math.h>
int ang = 0;	//angle for rotating cube
double camera[3] = {5,5,5};
float objectPos[3];
float inter[3];
bool groundPlane = true;
float mouseX, mouseY, mouseZ;
//float posx, posy, posz;
float angY = 0;//roation around Y
float angZ = 0;//rotation around X
//Global Variables
float posx = -10;
float posy = -10;
float posz = 10;
float posw = 10.5;
float posmovx = 0, posmovy = 0, posmovz = 0;
float position[4] = {posx, posy , posz, posw};
float planeNormal[6][3] = {{0,1,0},{-0.125,0,0},{0,0,0.125},{0.25,0,0},{0,0,-0.25}};//TOP,LEFT,RIGHT,BACKRIGHT,BACKLEFT,BOTTOM
float planePoints[6][3] = {{0.25,0.25,0},{0,-0.25,0.25},{0.25,-0.25,0.25},{0.25,0.25,0.25},{-0.25,-0.25,-0.25},{0.25,-0.25,-0.25}};
GLdouble newPoint [3];
GLdouble pNear[3];
GLdouble pFar[3]; //declare the two points
bool hit = false;
int x, y, z;
objects objectsList[20];
int numOfObjects = 0;

//lighting

/* drawCube() -- draws a cube with different coloured sides using QUAD primitives */

/* Get3DPos - takes a mouse x,y coordinate, and a "winz" corresponding to
 *  the depth through the viewing volume at which to determine the 3D point.
 *  returns (via point array) the 3D point corresponding to the distance along
 *  the mouse ray at depth winz
 */

void Get3DPos(int x, int y, float winz, GLdouble point[3])
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	
	//get the matrices
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );
    
	//"un-project" the 2D point giving the 3D position corresponding to the provided depth (winz)
	gluUnProject( (float)x, (float)(viewport[3]-y), winz, modelview, projection, viewport, &point[0], &point[1], &point[2]);
    
}


//float distance(ray newRay){
//    return -1 * (0*newRay.norm[0] + 0*newRay.norm[1] + 0*newRay.norm[2]);
//}

/* rayCast - takes a mouse x,y, coordinate, and casts a ray through that point
 *   for subsequent intersection tests with objects.
 */
void rayCast(float x, float y)
{
	float d;
    
    for (int i = 0; i < 5; i++){
	//get 3D position of mouse cursor on near and far clipping planes
	Get3DPos(x, y, 0.0, pNear);
	Get3DPos(x, y, 1.0, pFar);
    
	//create a ray originating at the camera position, and using the vector between the two points for the direction
	objects newRay;
	newRay.org[0] = camera[0];
	newRay.org[1] = camera[1];
	newRay.org[2] = camera[2];
	
	//ray direction is the vector (pFar - pNear)
	newRay.dir[0] = pFar[0] - pNear[0];
	newRay.dir[1] = pFar[1] - pNear[1];
	newRay.dir[2] = pFar[2] - pNear[2];
    
	//normalize the ray direction
	//normalize(newRay);
    
    float length;
    length = sqrt((newRay.dir[0]*newRay.dir[0]) + (newRay.dir[1] * newRay.dir[1]) + (newRay.dir[2] * newRay.dir[2]));
    newRay.norm[0] = newRay.dir[0]/length *-1;
    newRay.norm[1] = newRay.dir[1]/length *-1;
    newRay.norm[2] = newRay.dir[2]/length *-1;
    
    //printf("%f %f %f\n", newRay.norm[0], newRay.norm[1], newRay.norm[2]);
    
    d = -1 * (planePoints[i][0]*planeNormal[i][0] + planePoints[i][1]*planeNormal[i][1] + planePoints[i][2]*planeNormal[i][2]);
    
    float t = (planeNormal[i][0] *  newRay.norm[0] + planeNormal[i][1] * newRay.norm[1] + planeNormal[i][2] * newRay.norm[2]);
    
    if (t != 0){
        t = (-1* (planeNormal[i][0] * newRay.org[0] + planeNormal[i][1] * newRay.org[1] + planeNormal[i][2] * newRay.org[2] + d))/t;
        inter[0] = newRay.org[0] + t*newRay.norm[0];
        inter[1] = newRay.org[1] + t*newRay.norm[1];
        inter[2] = newRay.org[2] + t*newRay.norm[2];
        groundPlane = true;
    }
    else {
        groundPlane = false;
    }
    
	//update the position of the object to the intersection point
    if ( groundPlane == true){
        objectPos[0] = inter[0];
        objectPos[1] = inter[1];
        objectPos[2] = inter[2];
        
        printf("%f\n",objectPos[0]);
        printf("%f\n",objectPos[1]);
        printf("%f\n",objectPos[2]);
        printf("dsfasdfa\n");
        
        if ((-0.25 < objectPos[0] && objectPos[0] < 0.25 && -0.25 < objectPos[2] && objectPos[2] < 0.25)){
                hit = true;
                printf("\ntrue");
                break;
        }
        else{
            hit = false;
        }
        
    }
    }
}

void drawCube()
{
	glBegin(GL_QUADS);
	
    
    
    glColor3f(1, 0.5, 0.5);
    glVertex3f(-0.5,0,0.5);
    glVertex3f(0.5,0,0.5);
    glVertex3f(0.5,0.5,-0.5);
    glVertex3f(-0.5,0.5,-0.5);
    
    glColor3f(1, 0.5, 0.5);
    glVertex3f(-0.5,1,0.5);
    glVertex3f(0.5,1,0.5);
    glVertex3f(0.5,1,-0.5);
    glVertex3f(-0.5,1,-0.5);
    
    
	glEnd();
    
    glLineWidth(2.5);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex3f(-0.5,0,0.5);
    glVertex3f(0.5,0.5,-0.5);
    
    glVertex3f(0.5,0,0.5);
    glVertex3f(-0.5,0.5,-0.5);
    
    glEnd();
}

/* drawAxis() -- draws an axis at the origin of the coordinate system
 *   red = +X axis, green = +Y axis, blue = +Z axis
 */
void drawAxis()
{
	glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0,0,0);
    glVertex3f(50,0,0);
    
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,50,0);
    
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,50);
	glEnd();
}

/* display() - the OpenGL display function, this draws the screen
 *  it displays a spinning cube
 */
void display()
{
//    float origin[] = {0,0,0,1};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
    
    glPushMatrix();
    for (int x = 0; x < numOfObjects; x++){
        objectsList[x].drawObjects();
    }
    
    glRotatef(angY, 0, 0, 1);//rotate scene around x axis
    glRotatef(angZ, 0, 1, 0);//rotate scene around y axis
    glColor3f(0, 0.5, 0.5);
    //glutSolidCube(0.5);
    if (hit == true){
    glColor3f(1, 1, 1);
    glutWireCube(0.7);
    }
	float m_amb[] = {0.33, 0.22, 0.03, 1.0};
	float m_dif[] = {0.78, 0.57, 0.11, 1.0};
	float m_spec[] = {0.99, 0.91, 0.81, 1.0};
	float shiny = 27;
    
    //rayCast(x,y);
	//clear the screen
    //drawCube();
	//optionally draw the axis
	drawAxis();
    
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(objectPos[0],objectPos[1],objectPos[2]);//draw point
    glEnd();
    
    
	float amb[4] = {1.0, 1, 1, 1};
	float diff[4] = {1,0,0, 1};
	float spec[4] = {0,0,1, 1};
    
    
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    
    //glutSolidTeapot(1);
    
	//pop the matrix back to what it was prior to the rotation
    //	glPopMatrix();
	
	//swap buffers - rendering is done to the back buffer, bring it forward to display
    glPopMatrix();
	glutSwapBuffers();
    
	//force a redisplay, to keep the animation running
	glutPostRedisplay();
}

void idle()
{
    ang++;
    glutPostRedisplay();
}

/* kbd -- the GLUT keyboard function
 *  key -- the key pressed
 *  x and y - mouse x and y coordinates at the time the function is called
 */
void kbd(unsigned char key, int x, int y)
{
	//if the "q" key is pressed, quit the program
	if(key == 'q' || key == 'Q')
	{
		exit(0);
	}
    if (key == 'r') {
        //        posx++;
        //        posy++;
        posmovx++;
        posmovy++;
        posmovz++;
        //        posz++;
        printf("%4.2f \n", posmovx);
    }
    if (key == 'e') {
        //        posx--;
        //        posy--;
        //        posz--;
        posmovx--;
        posmovy--;
        posmovz--;
        printf("%4.2f \n", posmovx);
    }
    if (key == 'b')
    {
        idle();
        //        glutPostRedisplay();
    }
    if (key == 'a'){
        objects newObject;
        newObject.objectType = 1;
        objectsList[numOfObjects] = newObject;
        numOfObjects++;
    }
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
    
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
    
    //	float position[4] = {1.5,0,0, 0};
    //    float position[4] = {10.5,10.5,0,10.5};
    
    //	float amb[4] = {1.0, 1, 1, 1};
    //	float diff[4] = {1,0,0, 1};
    //	float spec[4] = {0,0,1, 1};
    
    
    //	glLightfv(GL_LIGHT1, GL_POSITION, position);
    //	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
    //	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
    //	glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    
    //    glLightfv(GL_LIGHT2, GL_POSITION, position);
    //	glLightfv(GL_LIGHT2, GL_DIFFUSE, diff);
    //	glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
    //	glLightfv(GL_LIGHT2, GL_SPECULAR, spec);
    
    
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(-2, 2, -2, 2, -2, 2);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//gluPerspective(45, 1, 1, 100);
    
}
void mouse(int btn, int state, int x, int y)
{
   
	if(btn == GLUT_LEFT_BUTTON)
	{
        //Get3DPos(x,y,0,newPoint);
        rayCast(x, y);
	}
	if(btn == GLUT_RIGHT_BUTTON)
	{
        mouseX = x;
        mouseY = y;
	}
    
	glFlush();
    glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y) {
    
    //Responsible for camera movement, press right to turn right, left for left, up for up and down for down
    switch(key) {
		case GLUT_KEY_UP:
            angY = angY +1;
            break;
		case GLUT_KEY_DOWN :
            angY = angY -1;
            break;
        case GLUT_KEY_LEFT:
            angZ = angZ + 1;
            break;
        case GLUT_KEY_RIGHT:
            angZ = angZ - 1;
            break;
	}
    
}

int main(int argc, char** argv)
{
	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Assignment 3");
    glClearColor(0.5, 0.5, 0.5, 0);
	//enable Z buffer test, otherwise things appear in the order they're drawn
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2.5, 2.5, -2.5, 2.5, -2.5, 2.5);
	gluPerspective(15, 1, 1, 100);
    
    //	//set clear colour to white
    //	glClearColor(1, 1, 1, 0);
    
	glMatrixMode(GL_MODELVIEW);
 
	//glRotatef(0, camera[0], camera[1], camera[2]);
    
    glutMouseFunc(mouse);
    
	//register glut callbacks for keyboard and display function
	glutKeyboardFunc(kbd);
    glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc(display);
    glutIdleFunc(idle);
    
	//start the program!
	glutMainLoop();
    
	return 0;
}
