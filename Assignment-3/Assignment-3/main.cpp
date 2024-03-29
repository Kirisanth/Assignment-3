//
//  main.cpp
//  Assignment-3
//
//  Created by Kirisanth Subramaniam on 2013-11-23.
//  Copyright (c) 2013 Kirisanth Subramaniam. All rights reserved.
//

#include "objects.h"
#include "FileIO.h"
#include <stdlib.h>
#include <GLUT/glut.h>
#include <iostream>

#include <fstream>
#include <string>
#include <sstream>

#include <math.h>
int ang = 0;	//angle for rotating cube
double camera[3] = {9,9,9};//declares camera at position   
float objectPos[3];//stores object position
float inter[3];//stores object intersection
bool groundPlane = true;//check if hit on plane
float mouseX, mouseY, mouseZ;//traacks mouse coords
//float posx, posy, posz;
float angY = 0;//roation around Y
float angZ = 0;//rotation around X
//Global Variables
float posx = -10;
float posy = -10;
float posz = 10;
float posw = 10.5;
float posmovx = 0, posmovy = 0, posmovz = 0;
float position[4] = {posx, posy , posz, posw};//lighting postion
float position2[4] = {5, 7 , 1, 2};//lighting postion
GLdouble newPoint [3];//creates new point
GLdouble pNear[3];//depth for z
GLdouble pFar[3]; //depth for z
bool hit = false;//checks hit on object
int x, y, z;
objects objectsList[20];//contains list of objects
int numOfObjects = 0;//contains number of objects
float translateX = 0, translateY = 0, translateZ = 0;//rotation around axis
int targetObject = false;//see's if target object is hit
float rotateX = 0, rotateY = 0, rotateZ = 0;//rotating objects
std::string * loadedStringObjects = new std::string [20];//loading string
int globalsize = 20;
float scale;//scaling for objects
static GLubyte texImage[64][64][4];
static GLuint texName[2];
double texture[3][4][2];//texture for objects
bool deleteObject = false;//check to see if object should be deleted
double color[3][3];//color of plane
int textureChoice = 0;//choice of texture of plane
int colorChoice = 0;//choice of color of plane

//materials
float m_amb[4];//ambient
float m_dif[4];//diffusion
float m_spec[4];//specular
float shiny;

//lighting

/* drawCube() -- draws a cube with different coloured sides using QUAD primitives */

/* Get3DPos - takes a mouse x,y coordinate, and a "winz" corresponding to
 *  the depth through the viewing volume at which to determine the 3D point.
 *  returns (via point array) the 3D point corresponding to the distance along
 *  the mouse ray at depth winz
 */

void findObjectNormal() {

}

void loadNumberOfObjects()
{

    std::string line;
    std::ifstream myfile ("num.txt");

    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            numOfObjects = atoi(line.c_str());
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

void loadFile2(objects objects[20], int size)
{
    std::string line;
    std::ifstream myfile ("example.txt");

    int counter = size - 1;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            std::string word;
            std::stringstream stream(line);
            int p = 0;
            
            std::string stringobj[132];
            while( getline(stream, word, ',') )
            {
                stringobj[p] = word;
                
                
                p++;
            }
            
            p = 0;
            
            for (int i = 0; i < 3; i++) {
                objectsList[counter].org[i] = strtod(stringobj[p].c_str(), NULL);
                p++;
            }
            
            for (int i = 0; i < 3; i++) {
                objectsList[counter].dir[i] = strtod(stringobj[p].c_str(), NULL);
                p++;
            }

            for (int i = 0; i < 3; i++) {
                objectsList[counter].norm[i] = strtod(stringobj[p].c_str(), NULL);
                p++;
            }
            
            
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 3; j++) {
                    objectsList[counter].objectPlaneNormal[i][j] = strtod(stringobj[p].c_str(), NULL);
                    p++;
                }
            }
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        objectsList[counter].objectPointsForNormal[i][j][k] = strtod(stringobj[p].c_str(), NULL);
                        p++;
                    }
                }
            }
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 3; k++) {
                        objectsList[counter].objectVectorForNormal[i][j][k] = strtod(stringobj[p].c_str(), NULL);
                        p++;
                    }
                }
            }
            
            for (int i = 0; i < 3; i++) {
                objectsList[counter].spherePoints[i] = strtod(stringobj[p].c_str(), NULL);
                p++;
            }
            
            objectsList[counter].rotationAngle = strtod(stringobj[p].c_str(), NULL);
            p++;
            objectsList[counter].translateX = strtod(stringobj[p].c_str(), NULL);
            p++;
            objectsList[counter].translateY = strtod(stringobj[p].c_str(), NULL);
            p++;
            objectsList[counter].translateZ = strtod(stringobj[p].c_str(), NULL);
            p++;
            objectsList[counter].rotateX = strtod(stringobj[p].c_str(), NULL);
            p++;
            objectsList[counter].rotateY = strtod(stringobj[p].c_str(), NULL);
            p++;
            objectsList[counter].rotateZ = strtod(stringobj[p].c_str(), NULL);
            p++;
            objectsList[counter].hit = true;
            p++;
            objectsList[counter].objectType = 1;
            objectsList[counter].drawingMaterial = 1;
            p++;
            p++;
            objectsList[counter].scaleFactor = strtod(stringobj[p].c_str(), NULL);
            
            counter--;
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
    
    std::cout << "good";
}

/*
 Function takes in mouse coordiatnes and returns a 3d point
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



//Function performs a ray plan test to check if ray intersected object other then sphere
bool rayPlaneTest(int count, int i){
    float t = objectsList[count].normalMultiplyDirection(i);
    if (t != 0){
        t = objectsList[count].normalMultiplyOrgin(i, t);
        //store instesection points if it did 
        inter[0] = objectsList[count].org[0] + t*objectsList[count].norm[0];
        inter[1] = objectsList[count].org[1] + t*objectsList[count].norm[1];
        inter[2] = objectsList[count].org[2] + t*objectsList[count].norm[2];
        return true;
    }
    else {
        return false;
    }
    
}

//Function performs a ray plan test to check if ray intersected sphere
void spehereRayTest(int count, int i){
    double a, b, c;
    float temp[3], temp2[3];
    float t1, t2;
    a = objectsList[count].norm[0] * objectsList[count].norm[1] + objectsList[count].norm[1] * objectsList[count].norm[1] +objectsList[count].norm[2] * objectsList[count].norm[2];
    temp [0] = 2 * (objectsList[count].org[0] - 0);
    temp [1] = 2 * (objectsList[count].org[1] - 0);
    temp [2] = 2 * (objectsList[count].org[2] - 0);
    b = temp[0] * objectsList[count].norm[0] + temp[1] * objectsList[count].norm[1] + temp[2] * objectsList[count].norm[2];
    temp[0] = objectsList[count].norm[0] - 0;
    temp[1] = objectsList[count].norm[1] - 0;
    temp[2] = objectsList[count].norm[2] - 0;
    
    temp2[0] = objectsList[count].norm[0] - 0;
    temp2[1] = objectsList[count].norm[1] - 0;
    temp2[2] = objectsList[count].norm[2] - 0;
    
    c  = temp[0] * temp[0] + temp[1] * temp[1] + temp[2] * temp[2];
    
    t1 = -b + sqrt(b*b + - 4*a*c)/2*a;
    t2 = b + sqrt(b*b + - 4*a*c)/2*a;
}

/* rayCast - takes a mouse x,y, coordinate, and casts a ray through that point
 *   for subsequent intersection tests with objects.
 */
void rayCast(float x, float y)
{
    //count through number of objects to perform tests on each one
    for (int count = 0; count < numOfObjects; count++){
    //count through number of planes of each object to perform test on each one
    for (int i = 0; i < 6; i++){
        
	Get3DPos(x, y, 0.0, pNear);
	Get3DPos(x, y, 1.0, pFar);
        
    //store ray orgin
	objectsList[count].org[0] = camera[0];
	objectsList[count].org[1] = camera[1];
	objectsList[count].org[2] = camera[2];
	
	//ray direction is the vector (pFar - pNear)
	objectsList[count].dir[0] = pFar[0] - pNear[0];
	objectsList[count].dir[1] = pFar[1] - pNear[1];
	objectsList[count].dir[2] = pFar[2] - pNear[2];
    
    //normalize direction vector
    objectsList[count].normalizeDirection();
    
    //undergoe ray plane test
    groundPlane = rayPlaneTest(count, i);
        
	//update the position of the object to the intersection point
    if ( groundPlane == true){
        objectPos[0] = inter[0];
        objectPos[1] = inter[1];
        objectPos[2] = inter[2];
        
        //check if object is hit between min and max bounds
        if ((objectsList[count].min + objectsList[count].translateX < objectPos[0] && objectPos[0] < objectsList[count].max + objectsList[count].translateX && objectsList[count].min + objectsList[count].translateZ < objectPos[2] && objectPos[2] < objectsList[count].max + objectsList[count].translateZ && objectPos[1] < objectsList[count].max + objectsList[count].translateY && objectsList[count].min + objectsList[count].translateY < objectPos[1])){
            hit = true;
            targetObject = count;
            objectsList[count].hit = true;
            //check to see right click to delete object
            if (deleteObject == true){
                objectsList[count].deleteObject();
            }
            break;
        }
        //return false hit else wise
        else{
            hit = false;
            objectsList[count].hit = false;
        }
        
    
    }
    }   //break out of cycle of object 
        if(hit == true){
            for(int z = 0; z < numOfObjects; z++){
                if(z != count){
                    objectsList[z].hit = false;
                }
            }
            break;
        }
    }
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


//create texture pattern
//algorithm is not mine. cited from:
//www.gamedev.net/topic/500676-opengl-some-info-about-textures/
//game dev website
void makeCheckImages(void)
{
    int i, j, c;
    
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 64; j++) {
            c = ((((i&0x8)==0)^(((j&0x8))==0)))*255;
            texImage[i][j][0] = (GLubyte) c;
            texImage[i][j][1] = (GLubyte) c;
            texImage[i][j][2] = (GLubyte) c;
            texImage[i][j][3] = (GLubyte) 255;
        }
    }
}

//draw platform with textuized features 
void drawPlatform(){
    //bottom
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glBegin(GL_QUADS);
    
    glColor3f(color[colorChoice][0], color[colorChoice][1], color[colorChoice][2]);
    glTexCoord2f(texture[textureChoice][0][0], texture[textureChoice][0][1]);
    glVertex3f(-2.8,-0.3,2.8);
    glTexCoord2f(texture[textureChoice][1][0], texture[textureChoice][1][1]);
    glVertex3f(2.8,-0.3,2.8);
    glTexCoord2f(texture[textureChoice][2][0], texture[textureChoice][2][1]);
    glVertex3f(2.8,-0.3,-2.8);
    glTexCoord2f(texture[textureChoice][3][0], texture[textureChoice][3][1]);
    glVertex3f(-2.8,-0.3,-2.8);
    glEnd();
}



/* display() - the OpenGL display function, this draws the screen
 *  it displays a spinning cube
 */
void display()
{
    //       //    float origin[] = {0,0,0,1};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera[0], camera[1], camera[2], 0, 0, 0, 0, 1, 0);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(objectPos[0],objectPos[1],objectPos[2]);//draw point
    glEnd();
    

    glPushMatrix();
    glRotatef(ang, 0, 1, 0);
    glScaled(posmovx, posmovy, posmovz);
    
    float amb[4] = {1.0, 1, 1, 1};
    float diff[4] = {1,0,0, 1};
    float spec[4] = {0,0,1, 1};

    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);

    glLightfv(GL_LIGHT2, GL_POSITION, position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spec);
    
    
    float amb2[4] = {1.0, 1, 1, 1};
    float diff2[4] = {1,0, 0, 1};
    float spec2[4] = {0,0, 1, 1};
    
    glLightfv(GL_LIGHT1, GL_POSITION, position2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec2);
    
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diff2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, amb2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spec2);


    glPopMatrix();
    
    //TODO:Change to global variables
//    float origin[] = {0,0,0,1};
//    float m_amb[] = {0.33, 0.22, 0.03, 1.0};
//    float m_dif[] = {0.78, 0.57, 0.11, 1.0};
//    float m_spec[] = {0.99, 0.91, 0.81, 1.0};
//    float shiny = 50;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    
    glPushMatrix();
    
    glRotatef(angY, 0, 1, 0);//rotate scene around x axis
    glRotatef(angZ, 0, 0, 1);//rotate scene around y axis
    for (int x = 0; x < numOfObjects; x++){
        glPushMatrix();
        objectsList[x].drawObjects();
        glPopMatrix();
    }
    //drawAxis();
    drawPlatform();
    
	//swap buffers - rendering is done to the back buffer, bring it forward to display
    //glLoadIdentity();
    glPopMatrix();
	glutSwapBuffers();
    
	//force a redisplay, to keep the animation running
	glutPostRedisplay();
}

void idle()
{
    ang = ang + 0.1;
    glutPostRedisplay();
}

/* kbd -- the GLUT keyboard function
 *  key -- the key pressed
 *  x and y - mouse x and y coordinates at the time the function is called
 */
void kbd(unsigned char key, int x, int y)
{
    //change object to cube
    if(key == '1'){
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectType = 1;
            }
        }
    }
    
    //change object to sphere 
    if(key == '2'){
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectType = 2;
            }
        }
    }
    
    //change object to teapot
    if(key == '3'){
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectType = 3;
            }
        }
    }
    
    //change object to cone
    if(key == '4'){
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectType = 4;
            }
        }
    }
    
    //change object to ring
    if(key == '5'){
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectType = 5;
            }
        }
    }
    
    //change texture to mosaic
    if(key == '7'){
        textureChoice = 0;
        colorChoice = 0;
    }
    
    //change texture to checkered 
    if(key == '8'){
        textureChoice = 1;
        colorChoice = 1;
    }
    
    //change texture to stripes
    if(key == '9'){
        textureChoice = 2;
        colorChoice = 2;
    }
    
	//if the "q" key is pressed, quit the program
	if(key == 'q' || key == 'Q')
	{
		exit(0);
	}
    //lighting
    //increase light source
    if (key == 'r') {
        posmovx++;
        posmovy++;
        posmovz++;
        printf("%4.2f \n", posmovx);
    }
    
    //decrease light source 
    if (key == 'e') {
        posmovx--;
        posmovy--;
        posmovz--;
        printf("%4.2f \n", posmovx);
    }
    
    if (key == 'b')
    {
        idle();
    }
    //create new object
    if (key == 'a'){
        objects newObject;
        newObject.objectType = 1;
        newObject.setObjectPoints(0,0,0);
        objectsList[numOfObjects] = newObject;
        numOfObjects++;
    }
    
    //translate object on x axis 
    if (key == 'x'){
        //int mod = glutGetModifiers();
        translateX = 0.1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectTranslateX(translateX);
            }
        }
    }
    //translate object backwards on x axis 
    if (key == 'X'){
        //int mod = glutGetModifiers();
        translateX = -0.1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectTranslateX(translateX);
            }
        }
    }
    
    //translate object on y
    if (key == 'y'){
        translateY = 0.1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectTranslateY(translateY);
            }
        }
    }
    
    //translate object backwards on y 
    if (key == 'Y'){
        translateY = -0.1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectTranslateY(translateY);
            }
        }
    }
    
    //translaye object on z
    if (key == 'z'){
        translateZ = 0.1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                 objectsList[count].objectTranslateZ(translateZ);
            }
        }
    }
    
    //translate object back on z
    if (key == 'Z'){
        translateZ = -0.1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectTranslateZ(translateZ);
            }
        }
    }
    
    //rotate object around x
    if (key == 'i'){
         rotateX = 1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectRotateX(rotateX);
            }
        }
    }
    
    //rotate object backwards around x
    if (key == 'I'){
        rotateX = -1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectRotateX(rotateX);
            }
        }
    }
    
    //rotate objects around y
    if (key == 'u'){
        rotateY = 1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectRotateY(rotateY);
            }
        }
    }
    
    //rotate objects backwards on y
    if (key == 'U'){
        rotateY = -1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectRotateY(rotateY);
            }
        }
    }
    
    //rotate object on z
    if (key == 'o'){
        rotateZ = 1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectRotateZ(rotateZ);
            }
        }
    }
    
    //rotate object backwards on z
    if (key == 'O'){
        rotateZ = -1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectRotateZ(rotateZ);
            }
        }
    }
    
    // increse object size
    if (key == 'm'){
        scale = 0.1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectScale(scale);
            }
        }
    }
    
    //decrease object size
    if (key == 'M'){
        scale = -0.1;
        for (int count = 0; count < numOfObjects;count++){
            if (objectsList[count].hit == true){
                objectsList[count].objectScale(scale);
            }
        }
    }
    
    //Change this to command save or something
    if(key == 's')
    {
        //Loop through array and save content into a file
        FileIO test;
        
        test.saveFile(objectsList, globalsize);
        test.saveNumberOfObjects(numOfObjects);
        
    }
    if(key == 'l')
    {
        //Reads File and stores in global array

        loadNumberOfObjects();
        loadFile2(&objectsList[20], 20);
        std::cout << "red";
        
        glutPostRedisplay();
    }
    
    if (key == 'h'){
        for (int count = 0; count < numOfObjects;count++){
            objectsList[count].deleteObject();
        }
        
    }
    if(key == 'g')
    {
        m_amb[0] = 0.33;
        m_amb[1] = 0.22;
        m_amb[2] = 0.03;
        m_amb[3] = 1.0;
        m_dif[0] = 0.98;
        m_dif[1] = 0.97;
        m_dif[2] = 0.91;
        m_dif[3] = 1.0;
        m_spec[0] = 0.10;
        m_spec[1] = 0.11;
        m_spec[2] = 0.11;
        m_spec[3] = 1.0;
        shiny = 50;
    }
    if(key == 'v')
    {
        m_amb[0] = 0.33;
        m_amb[1] = 0.22;
        m_amb[2] = 0.03;
        m_amb[3] = 1.0;
        m_dif[0] = 0.98;
        m_dif[1] = 0.97;
        m_dif[2] = 0.91;
        m_dif[3] = 1.0;
        m_spec[0] = 1.0;
        m_spec[1] = 1.0;
        m_spec[2] = 1.0;
        m_spec[3] = 1.0;
        shiny = 50;
    }
    if(key == 'n')
    {
        m_amb[0] = 0.33;
        m_amb[1] = 0.22;
        m_amb[2] = 0.03;
        m_amb[3] = 1.0;
        m_dif[0] = 0.18;
        m_dif[1] = 0.07;
        m_dif[2] = 0.11;
        m_dif[3] = 1.0;
        m_spec[0] = 0.99;
        m_spec[1] = 0.91;
        m_spec[2] = 0.81;
        m_spec[3] = 1.0;
        shiny = 50;
    }
    if(key == 'h')
    {
        m_amb[0] = 0.53;
        m_amb[1] = 0.22;
        m_amb[2] = 0.23;
        m_amb[3] = 1.0;
        m_dif[0] = 0.78;
        m_dif[1] = 0.57;
        m_dif[2] = 0.51;
        m_dif[3] = 1.0;
        m_spec[0] = 0.09;
        m_spec[1] = 0.61;
        m_spec[2] = 0.41;
        m_spec[3] = 1.0;
        shiny = 20;
    }
    if(key == 'd')
    {
        shiny = 50;
        m_amb[0] = 0.13;
        m_amb[1] = 0.25;
        m_amb[2] = 0.93;
        m_amb[3] = 1.0;
        m_dif[0] = 0.28;
        m_dif[1] = 0.47;
        m_dif[2] = 0.71;
        m_dif[3] = 1.0;
        m_spec[0] = 0.19;
        m_spec[1] = 0.11;
        m_spec[2] = 0.81;
        m_spec[3] = 1.0;
        shiny = 100;
    }

}

//set texture and color 
void setTextureAndColor(){
    
    texture[2][0][0] = 0;
    texture[2][0][1] = 0;
    texture[2][1][0] = 0;
    texture[2][1][1] = 1;
    texture[2][2][0] = 0;
    texture[2][2][1] = 1;
    texture[2][3][0] = 0;
    texture[2][3][1] = 1;
    
    texture[1][0][0] = 0;
    texture[1][0][1] = 0;
    texture[1][1][0] = 0;
    texture[1][1][1] = 1;
    texture[1][2][0] = 1;
    texture[1][2][1] = 1;
    texture[1][3][0] = 0;
    texture[1][3][1] = 1;
    
    texture[0][0][0] = 0;
    texture[0][0][1] = 0;
    texture[0][1][0] = 0;
    texture[0][1][1] = 1;
    texture[0][2][0] = 0.5;
    texture[0][2][1] = 0.5;
    texture[0][3][0] = 1;
    texture[0][3][1] = 0;
    
    
    color[2][0] = 0.5;
    color[2][1] = 0;
    color[2][2] = 0.3;
    
    color[1][0] = 1;
    color[1][1] = 1;
    color[1][2] = 1;
    
    color[0][0] = 0;
    color[0][1] = 0.2;
    color[0][2] = 0.5;
    
}


void init(void)
{
	//glClearColor(0, 0, 0, 0);

    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    
//    float position[4] = {10.5,10.5,0,10.5};
//    
//    float amb[4] = {1.0, 1, 1, 1};
//    float diff[4] = {1,0,0, 1};
//    float spec[4] = {0,0,1, 1};
//    
//    
//    glLightfv(GL_LIGHT1, GL_POSITION, position);
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
//    glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
//    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
//    
//    glLightfv(GL_LIGHT2, GL_POSITION, position);
//    glLightfv(GL_LIGHT2, GL_DIFFUSE, diff);
//    glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
//    glLightfv(GL_LIGHT2, GL_SPECULAR, spec);
    
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    makeCheckImages();
    setTextureAndColor();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glGenTextures(2, texName);
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64,
                 64, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 texImage);
    glEnable(GL_TEXTURE_2D);
    
    
}

void mouse(int btn, int state, int x, int y)
{
   //ray cast is pressed 
	if(btn == GLUT_LEFT_BUTTON)
	{
        deleteObject = false;
        rayCast(x, y);
	}
    //delete if pressed 
	if(btn == GLUT_RIGHT_BUTTON)
	{
        deleteObject = true;
        rayCast(x, y);
	}
    
	glFlush();
    glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y) {
    
    //Responsible for camera movement, press right to turn right, left for left, up for up and down for down
    switch(key) {
		case GLUT_KEY_UP:
            camera[1] +=+ 0.5;
            break;
		case GLUT_KEY_DOWN :
            camera[1] -= 0.5;
            break;
        case GLUT_KEY_LEFT:
            camera[0] -= 0.5;
            break;
        case GLUT_KEY_RIGHT:
            camera[0] += 0.5;
            break;
	}
    
}

void printCommands(){
    printf("Welcome to our program!\n\n");
    printf("Functions \n \n a - add object \n left click - select object \n right click - delete object \n 1 - change object to cube \n 2 - change object to sphere \n 3 - change object to teapot \n 4 - change object to cone \n 5 - change object to ring \n 7 - change plane to texture 1 \n 8 - change plane to texture 2 \n 9 - change plane to texture 3 \n q - quit program \n r/e - adjust lighting source \n x and shift X - translate object on x \n y and shift y - translate on y \n z and shift z - tranlate on z \n i and shift i - rotate object around x \n u and shift u - rotate object around y \n o and shift o - rotate object around z \n m and shift m - scale object size \n s - save object list \n l - load object list (must save first, restart program then press l to view saved objects) \n h - reset object list");
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
	gluPerspective(25, 1, 1, 100);
    
	glMatrixMode(GL_MODELVIEW);
    glutMouseFunc(mouse);
    
	//register glut callbacks for keyboard and display function
	init();
    glutKeyboardFunc(kbd);
    glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc(display);
    glutIdleFunc(idle);
    printCommands();
    
    
	//start the program!
	glutMainLoop();
    
	return 0;
}
