//
//  main.cpp
//  Assignment-3
//
//  Created by Kirisanth Subramaniam on 2013-11-23.
//  Copyright (c) 2013 Kirisanth Subramaniam. All rights reserved.
//

#include <stdlib.h>
#include <GLUT/glut.h>
#include <iostream>
int ang = 0;	//angle for rotating cube

/* drawCube() -- draws a cube with different coloured sides using QUAD primitives */
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
