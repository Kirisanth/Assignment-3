//
//  main.cpp
//  Assignment-3
//
//  Created by Kirisanth Subramaniam on 2013-11-23.
//  Copyright (c) 2013 Kirisanth Subramaniam. All rights reserved.
//

#include "ray.h"
#include <stdlib.h>
#include <GLUT/glut.h>
#include <iostream>
#include <math.h>
int ang = 0;	//angle for rotating cube
double camx;
double camy;
double camz;
double objectPos[3];
float inter[3];
bool groundPlane = false;
int mouseX, mouseY;
float posx, posy, posz;

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
    //fuck yoiu
	
	//get the matrices
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );
    
	//"un-project" the 2D point giving the 3D position corresponding to the provided depth (winz)
	gluUnProject( (float)x, (float)(viewport[3]-y), winz, modelview, projection, viewport, &point[0], &point[1], &point[2]);
}

float distance(ray newRay){
    return -1 * (newRay.dir[0]*newRay.norm[0] + newRay.dir[1]*newRay.norm[1] + newRay.dir[2]*newRay.norm[2]);
}

void normalize(ray newRay){
    double length;
    length = sqrt((newRay.dir[0]*newRay.dir[0]) + (newRay.dir[1] * newRay.dir[1]) + (newRay.dir[2] * newRay.dir[2]));
    newRay.norm[0] = newRay.dir[0]/length;
    newRay.norm[1] = newRay.dir[1]/length;
    newRay.norm[2] = newRay.dir[2]/length;
}

void rayPlaneTest(ray newRay, float d){
    double t = (newRay.norm[0] * newRay.dir[0] + newRay.norm[1] * newRay.dir[1] + newRay.norm[2] * newRay.dir[2]);
    if (t != 0){
        t = (-1* (newRay.norm[0] * newRay.org[0] + newRay.norm[1] * newRay.org[1] + newRay.norm[2] * newRay.org[2] + d))/t;
        groundPlane = true;
        inter[0] = newRay.org[0] + t*newRay.dir[0];
        inter[1] = newRay.org[1] + t*newRay.dir[1];
        inter[2] = newRay.org[2] + t*newRay.dir[2];
    }
    else {
        groundPlane = false;
    }
}

/* rayCast - takes a mouse x,y, coordinate, and casts a ray through that point
 *   for subsequent intersection tests with objects.
 */
void rayCast(int x, int y)
{
	GLdouble pNear[3];
	GLdouble pFar[3]; //declare the two points
	float d;
    
    
	//get 3D position of mouse cursor on near and far clipping planes
	Get3DPos(x, y, 0.0, pNear);
	Get3DPos(x, y, 1.0, pFar);
    
	//create a ray originating at the camera position, and using the vector between the two points for the direction
	ray newRay;
	newRay.org[0] = camx;
	newRay.org[1] = camy;
	newRay.org[2] = camz;
	
	//ray direction is the vector (pFar - pNear)
	newRay.dir[0] = pFar[0] - pNear[0];
	newRay.dir[1] = pFar[1] - pNear[1];
	newRay.dir[2] = pFar[2] - pNear[2];
    
	//normalize the ray direction
	normalize(newRay);
    d = distance(newRay);
    
	//printf("%f %f %f\n", newRay.dir[0], newRay.dir[1], newRay.dir[2]);
    
	//test if the ground plane is intersected by the ray
	// NOTE: you have to provide rayPlaneTest!! (see the slides)
	rayPlaneTest(newRay, d);
    
	//update the position of the object to the intersection point
    if ( groundPlane == true){
        objectPos[0] = inter[0];
        objectPos[1] = inter[1];
        objectPos[2] = inter[2];
    }
}

void drawCube()
{
	glBegin(GL_QUADS);
	
    //front
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    
    //top
    glColor3f(1, 1, 0);
    glVertex3f(-1,1,1);
    glVertex3f(1,1,1);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);
    
    //bottom
    glColor3f(0, 1, 0);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);
    glVertex3f(-1,-1,-1);
    
    //left side
    glColor3f(0, 0, 1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    
    //right side
    glColor3f(1,0,1);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    
    //back side
    glColor3f(0,1,0);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    
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
    float origin[] = {0,0,0,1};
	float m_amb[] = {0.33, 0.22, 0.03, 1.0};
	float m_dif[] = {0.78, 0.57, 0.11, 1.0};
	float m_spec[] = {0.99, 0.91, 0.81, 1.0};
	float shiny = 27;
    int x = mouseX;
    int y = mouseY;
    rayCast(x,y);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3i(objectPos[0], objectPos[1], objectPos[2]);
    glColor3f(1,0,0);
    glEnd();
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	//increment the rotation angle every 25th display cycle

    
	//optionally draw the axis
	drawAxis();
    
    
	//push the current modelview matrix onto the matrix stack
	//  this allows us to rotate, then pop the stack so as to only
	//  rotate our cube, and only by the specified amount
	glPushMatrix();
    
	//do the rotation - rotate about the Y axis by angle ang
	
	glRotatef(ang, 0, 1, 0);
	
    //	glTranslatef(1, 0, 0);
	//draw the cube
//	drawCube();
    
    
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
//	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
//	glColor3f(1,1,1);
    
    
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    
    glutSolidTeapot(1);
    
	//pop the matrix back to what it was prior to the rotation
	glPopMatrix();
	
	//swap buffers - rendering is done to the back buffer, bring it forward to display
	glutSwapBuffers();
    
	//force a redisplay, to keep the animation running
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
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
    
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    
	float position[4] = {1.5,0,0, 0};
    
	float amb[4] = {1.0, 1, 1, 1};
	float diff[4] = {1,0,0, 1};
	float spec[4] = {0,0,1, 1};
    
    
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2, 2, -2, 2, -2, 2);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	gluPerspective(45, 1, 1, 100);
    
}
void mouse(int btn, int state, int x, int y)
{
    y = 500 - y;
	if(btn == GLUT_LEFT_BUTTON)
	{
            mouseX = x;
            mouseY = y;

        
	}
	if(btn == GLUT_RIGHT_BUTTON)
	{
        mouseX = x;
        mouseY = y;
	}
    
	glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Spinning Cube");
    
	//enable Z buffer test, otherwise things appear in the order they're drawn
	glEnable(GL_DEPTH_TEST);
    init();
	//setup the initial view
	// change to projection matrix mode, set the extents of our viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.5, 2.5, -2.5, 2.5, -2.5, 2.5);
	
    
//	//set clear colour to white
//	glClearColor(1, 1, 1, 0);
    
	glMatrixMode(GL_MODELVIEW);
	//look down from a 45 deg. angle
	glRotatef(45, 1, 0, 0);
    
    
	//register glut callbacks for keyboard and display function
	glutKeyboardFunc(kbd);
	glutDisplayFunc(display);
    
	//start the program!
	glutMainLoop();
    
	return 0;
}
