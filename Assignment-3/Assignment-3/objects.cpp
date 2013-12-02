//
//  objects.cpp
//  Assignment-3
//
//  Created by Meraj Patel on 11/29/2013.
//  Copyright (c) 2013 Kirisanth Subramaniam. All rights reserved.
//

#include <stdlib.h>
#include <GLUT/glut.h>
#include <iostream>
#include "objects.h"
#include <math.h>

//intilize objects 
objects::objects(){
    org[0] = 0;
    org[1] = 0;
    org[2] = 0;
    
    dir[0] = 0;
    dir[1] = 0;
    dir[2] = 0;
    
    norm[0] = 0;
    norm[1] = 0;
    norm[2] = 0;
    
    translateX = 0;
    translateY = 0;
    translateZ = 0;
    
};
objects::objects(double o[3],
                 double d[3],
                 double n[3],
                 double objPlNorm[6][3],
                 double objPtsFNorm[6][3][3],
                 double objVecFNorm[6][2][3],
                 double sphPts[3],
                 double rotateAng,
                 double transX,
                 double transY,
                 double transZ,
                 double rotX,
                 double rotY,
                 double rotZ,
                 bool h,
                 int objT,
                 int dM,
                 double sF){

    for (int i = 0; i < 3; i++) {
        spherePoints[i] = sphPts[i];
        org[i] = o[i];
        dir[i] = d[i];
        norm[i] = n[i];
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            objectPlaneNormal[i][j] = objPlNorm[i][j];
        }
    }
    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; j++) {
                objectPointsForNormal[i][j][k] = objPtsFNorm[i][j][k];
            }
        }
    }
    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; j++) {
                objectVectorForNormal[i][j][k] = objVecFNorm[i][j][k];
            }
        }
    }
    
    rotationAngle = rotateAng;
    translateX = transX;
    translateY = transY;
    translateZ = transZ;
    rotateX = rotX;
    rotateY = rotY;
    rotateZ = rotZ;
    hit = h;
    objectType = objT;
    drawingMaterial = dM; //indicate which choice made by user via integer
    scaleFactor = sF;
};

//TODO: added another constructor

void objects::normalizeDirection(){
    
    float length;
    length = sqrt((dir[0]*dir[0]) + (dir[1] * dir[1]) + (dir[2] * dir[2]));
    norm[0] = dir[0]/length *-1;
    norm[1] = dir[1]/length *-1;
    norm[2] = dir[2]/length *-1;
    
}

void objects::deleteObject(){
    org[0] = 0;
    org[1] = 0;
    org[2] = 0;
    
    dir[0] = 0;
    dir[1] = 0;
    dir[2] = 0;
    
    norm[0] = 0;
    norm[1] = 0;
    norm[2] = 0;
    
    translateX = 0;
    translateY = 0;
    translateZ = 0;
    
    objectType = 0;
    min = 0;
    max = 0;
    hit = false;
}

void objects::drawObjects(){
    glColor3f(0, 0.5, 0.5);
    //glEnable(GL_COLOR_MATERIAL);
    //glColorMaterial(GL_FRONT, GL_DIFFUSE);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
    glTranslatef(translateX, translateY, translateZ);
    glRotatef(rotateX, 1, 0, 0);
    glRotatef(rotateY, 0, 1, 0);
    glRotatef(rotateZ, 0, 0, 1);
    if (objectType == 1){
        glutSolidCube(0.5 + scale);//draw cube
    }
    else if (objectType == 2){
        glutSolidSphere(0.3 + scale, 15, 15);//draw cube
        spherePoints[0] = 0;
        spherePoints[1] = 0;
        spherePoints[2] = 0;
        
    }
    else if (objectType == 3){
        glutSolidTeapot(0.3 + scale);//draw cube
    }
    else if (objectType == 4){
        glutSolidCone(0.2 + scale, 0.2 + scale, 15, 15);//draw cube
    }
    else if (objectType == 5){
        glutSolidTorus(0.1 + scale, 0.2 + scale, 10, 10);
    }
    if (hit == true){
        glColor3f(1, 1, 1);
        glutWireCube(0.7 + scale);
    }
}

void objects::objectScale(float s){
    scale = scale + s;
    min = min + scale/2;
    max = max + scale/2;
}
void objects::objectTranslateX(double x){
    translateX = translateX + x;
    //setObjectPoints(translateX, 0, 0);
}

void objects::objectTranslateY(double y){
    translateY = translateY + y;
    //setObjectPoints(0, translateY, 0);
}
void objects::objectTranslateZ(double z){
    translateZ =translateZ + z;
    //setObjectPoints(0, 0, translateZ);
}
void objects::objectRotateX(double x){
    rotateX = rotateX + x;
    //modifyRotationPoints(rotateX,0,0,1);
}
void objects::objectRotateY(double y){
    rotateY = rotateY + y;
    //modifyRotationPoints(0,rotateY,0,2);
}
void objects::objectRotateZ(double z){
    rotateZ = rotateZ + z;
    //modifyRotationPoints(0,0,rotateZ,3);
}

float objects::findDistance(int i){

   return -1 * (objectPointsForNormal[i][1][0]*objectPlaneNormal[i][0] + objectPointsForNormal[i][1][1]*objectPlaneNormal[i][1] + objectPointsForNormal[i][1][2]*objectPlaneNormal[i][2]);

}

float objects::normalMultiplyDirection(int i){
    return (objectPlaneNormal[i][0] *  norm[0] + objectPlaneNormal[i][1] * norm[1] + objectPlaneNormal[i][2] * norm[2]);
}

float objects::normalMultiplyOrgin(int i, float t){
    return  (-1* (objectPlaneNormal[i][0] * org[0] + objectPlaneNormal[i][1] * org[1] + objectPlaneNormal[i][2] * org[2] + findDistance(i)))/t;
}


void objects::normalizePlane(){
    
    objectPlaneNormal[0][0] = objectVectorForNormal[0][0][1]*objectVectorForNormal[0][1][2] - objectVectorForNormal[0][0][2]*objectVectorForNormal[0][1][1];
    objectPlaneNormal[0][1] = objectVectorForNormal[0][0][2]*objectVectorForNormal[0][1][0] - objectVectorForNormal[0][0][0]*objectVectorForNormal[0][1][2];
    objectPlaneNormal[0][2] = objectVectorForNormal[0][0][0]*objectVectorForNormal[0][1][1] - objectVectorForNormal[0][0][1]*objectVectorForNormal[0][1][0] * -1;
    
    
    objectPlaneNormal[1][0] = objectVectorForNormal[1][0][1]*objectVectorForNormal[1][1][2] - objectVectorForNormal[1][0][2]*objectVectorForNormal[1][1][1];
    objectPlaneNormal[1][1] = objectVectorForNormal[1][0][2]*objectVectorForNormal[1][1][0] - objectVectorForNormal[1][0][0]*objectVectorForNormal[1][1][2];
    objectPlaneNormal[1][2] = objectVectorForNormal[1][0][0]*objectVectorForNormal[1][1][1] - objectVectorForNormal[1][0][1]*objectVectorForNormal[1][1][0];
    
    
    objectPlaneNormal[2][0] = objectVectorForNormal[2][0][1]*objectVectorForNormal[2][1][2] - objectVectorForNormal[2][0][2]*objectVectorForNormal[2][1][1];
    objectPlaneNormal[2][1] = objectVectorForNormal[2][0][2]*objectVectorForNormal[2][1][0] - objectVectorForNormal[2][0][0]*objectVectorForNormal[2][1][2];
    objectPlaneNormal[2][2] = objectVectorForNormal[2][0][0]*objectVectorForNormal[2][1][1] - objectVectorForNormal[2][0][1]*objectVectorForNormal[2][1][0];
    
    
    objectPlaneNormal[3][0] = objectVectorForNormal[3][0][1]*objectVectorForNormal[3][1][2] - objectVectorForNormal[3][0][2]*objectVectorForNormal[3][1][1];
    objectPlaneNormal[3][1] = objectVectorForNormal[3][0][2]*objectVectorForNormal[3][1][0] - objectVectorForNormal[3][0][0]*objectVectorForNormal[3][1][2] *-1;
    objectPlaneNormal[3][2] = objectVectorForNormal[3][0][0]*objectVectorForNormal[3][1][1] - objectVectorForNormal[3][0][1]*objectVectorForNormal[3][1][0];
    
    
    objectPlaneNormal[4][0] = objectVectorForNormal[4][0][1]*objectVectorForNormal[4][1][2] - objectVectorForNormal[4][0][2]*objectVectorForNormal[4][1][1];
    objectPlaneNormal[4][1] = objectVectorForNormal[4][0][2]*objectVectorForNormal[4][1][0] - objectVectorForNormal[4][0][0]*objectVectorForNormal[4][1][2];
    objectPlaneNormal[4][2] = objectVectorForNormal[4][0][0]*objectVectorForNormal[4][1][1] - objectVectorForNormal[4][0][1]*objectVectorForNormal[4][1][0];
    
    
    objectPlaneNormal[5][0] = objectVectorForNormal[5][0][1]*objectVectorForNormal[5][1][2] - objectVectorForNormal[5][0][2]*objectVectorForNormal[5][1][1];
    objectPlaneNormal[5][1] = objectVectorForNormal[5][0][2]*objectVectorForNormal[5][1][0] - objectVectorForNormal[5][0][0]*objectVectorForNormal[5][1][2];
    objectPlaneNormal[5][2] = objectVectorForNormal[5][0][0]*objectVectorForNormal[5][1][1] - objectVectorForNormal[5][0][1]*objectVectorForNormal[5][1][0];
    
}


void objects::setObjectPoints(float x, float y, float z){
    
    //for right face
    objectPointsForNormal[0][0][0] = max + x;
    objectPointsForNormal[0][0][1] = min + y;
    objectPointsForNormal[0][0][2] = max + z;
    
    objectPointsForNormal[0][1][0] = max + x;
    objectPointsForNormal[0][1][1] = max + y;
    objectPointsForNormal[0][1][2] = max + z;
    
    objectPointsForNormal[0][2][0] = min + x;
    objectPointsForNormal[0][2][1] = min + y;
    objectPointsForNormal[0][2][2] = max + z;
    
    //for left face
    objectPointsForNormal[1][0][0] = max + x;
    objectPointsForNormal[1][0][1] = min + y;
    objectPointsForNormal[1][0][2] = max + z;
    
    objectPointsForNormal[1][1][0] = max + x;
    objectPointsForNormal[1][1][1] = max + y;
    objectPointsForNormal[1][1][2] = max + z;
    
    objectPointsForNormal[1][2][0] = max + x;
    objectPointsForNormal[1][2][1] = min + y;
    objectPointsForNormal[1][2][2] = min + z;
    
    //for top face
    objectPointsForNormal[2][0][0] = max + x;
    objectPointsForNormal[2][0][1] = max + y;
    objectPointsForNormal[2][0][2] = max + z;
    
    objectPointsForNormal[2][1][0] = min + x;
    objectPointsForNormal[2][1][1] = max + y;
    objectPointsForNormal[2][1][2] = max + z;
    
    objectPointsForNormal[2][2][0] = min + x;
    objectPointsForNormal[2][2][1] = max + y;
    objectPointsForNormal[2][2][2] = min + z;
    
    //for bottom face
    objectPointsForNormal[3][0][0] = max + x;
    objectPointsForNormal[3][0][1] = min + y;
    objectPointsForNormal[3][0][2] = max + z;
    
    objectPointsForNormal[3][1][0] = min + x;
    objectPointsForNormal[3][1][1] = min + y;
    objectPointsForNormal[3][1][2] = max + z;
    
    objectPointsForNormal[3][2][0] = min + x;
    objectPointsForNormal[3][2][1] = min + y;
    objectPointsForNormal[3][2][2] = min + z;
    
    //for back right face
    objectPointsForNormal[4][0][0] = min + x;
    objectPointsForNormal[4][0][1] = max + y;
    objectPointsForNormal[4][0][2] = min + z;
    
    objectPointsForNormal[4][1][0] = min + x;
    objectPointsForNormal[4][1][1] = min + y;
    objectPointsForNormal[4][1][2] = min + z;
    
    objectPointsForNormal[4][2][0] = max + x;
    objectPointsForNormal[4][2][1] = min + y;
    objectPointsForNormal[4][2][2] = min + z;
    
    //for back left face
    objectPointsForNormal[5][0][0] = min + x;
    objectPointsForNormal[5][0][1] = max + y;
    objectPointsForNormal[5][0][2] = min + z;
    
    objectPointsForNormal[5][1][0] = min + x;
    objectPointsForNormal[5][1][1] = min + y;
    objectPointsForNormal[5][1][2] = min + z;
    
    objectPointsForNormal[5][2][0] = min + x;
    objectPointsForNormal[5][2][1] = min + y;
    objectPointsForNormal[5][2][2] = max + z;
    
    createObjectVectors();
    
    
}

void objects::createObjectVectors(){
    //for vector 1
    objectVectorForNormal[0][0][0] = objectPointsForNormal[0][1][0] - objectPointsForNormal[0][0][0];
    objectVectorForNormal[0][0][1] = objectPointsForNormal[0][1][1] - objectPointsForNormal[0][0][1];
    objectVectorForNormal[0][0][2] = objectPointsForNormal[0][1][2] - objectPointsForNormal[0][0][2];
    
    //for vector 2
    objectVectorForNormal[0][1][0] = objectPointsForNormal[0][2][0] - objectPointsForNormal[0][0][0];
    objectVectorForNormal[0][1][1] = objectPointsForNormal[0][2][1] - objectPointsForNormal[0][0][1];
    objectVectorForNormal[0][1][2] = objectPointsForNormal[0][2][2] - objectPointsForNormal[0][0][2];
    
    //for vector 1
    objectVectorForNormal[1][0][0] = objectPointsForNormal[1][1][0] - objectPointsForNormal[1][0][0];
    objectVectorForNormal[1][0][1] = objectPointsForNormal[1][1][1] - objectPointsForNormal[1][0][1];
    objectVectorForNormal[1][0][2] = objectPointsForNormal[1][1][2] - objectPointsForNormal[1][0][2];
    
    //for vector 2
    objectVectorForNormal[1][1][0] = objectPointsForNormal[1][2][0] - objectPointsForNormal[1][0][0];
    objectVectorForNormal[1][1][1] = objectPointsForNormal[1][2][1] - objectPointsForNormal[1][0][1];
    objectVectorForNormal[1][1][2] = objectPointsForNormal[1][2][2] - objectPointsForNormal[1][0][2];
    
    //for vector 1
    objectVectorForNormal[2][0][0] = objectPointsForNormal[2][0][0] - objectPointsForNormal[2][1][0];
    objectVectorForNormal[2][0][1] = objectPointsForNormal[2][0][1] - objectPointsForNormal[2][1][1];
    objectVectorForNormal[2][0][2] = objectPointsForNormal[2][0][2] - objectPointsForNormal[2][1][2];
    
    //for vector 2
    objectVectorForNormal[2][1][0] = objectPointsForNormal[2][2][0] - objectPointsForNormal[2][1][0];
    objectVectorForNormal[2][1][1] = objectPointsForNormal[2][2][1] - objectPointsForNormal[2][1][1];
    objectVectorForNormal[2][1][2] = objectPointsForNormal[2][2][2] - objectPointsForNormal[2][1][2];
    
    
    //for vector 1
    objectVectorForNormal[3][0][0] = objectPointsForNormal[3][0][0] - objectPointsForNormal[3][1][0];
    objectVectorForNormal[3][0][1] = objectPointsForNormal[3][0][1] - objectPointsForNormal[3][1][1];
    objectVectorForNormal[3][0][2] = objectPointsForNormal[3][0][2] - objectPointsForNormal[3][1][2];
    
    //for vector 2
    objectVectorForNormal[3][1][0] = objectPointsForNormal[3][2][0] - objectPointsForNormal[3][1][0];
    objectVectorForNormal[3][1][1] = objectPointsForNormal[3][2][1] - objectPointsForNormal[3][1][1];
    objectVectorForNormal[3][1][2] = objectPointsForNormal[3][2][2] - objectPointsForNormal[3][1][2];
    
    //for vector 1
    objectVectorForNormal[4][0][0] = objectPointsForNormal[4][0][0] - objectPointsForNormal[4][1][0];
    objectVectorForNormal[4][0][1] = objectPointsForNormal[4][0][1] - objectPointsForNormal[4][1][1];
    objectVectorForNormal[4][0][2] = objectPointsForNormal[4][0][2] - objectPointsForNormal[4][1][2];
    
    
    //for vector 2
    objectVectorForNormal[4][1][0] = objectPointsForNormal[4][2][0] - objectPointsForNormal[4][1][0];
    objectVectorForNormal[4][1][1] = objectPointsForNormal[4][2][1] - objectPointsForNormal[4][1][1];
    objectVectorForNormal[4][1][2] = objectPointsForNormal[4][2][2] - objectPointsForNormal[4][1][2];
    
    //for vector 1
    objectVectorForNormal[5][0][0] = objectPointsForNormal[5][0][0] - objectPointsForNormal[5][1][0];
    objectVectorForNormal[5][0][1] = objectPointsForNormal[5][0][1] - objectPointsForNormal[5][1][1];
    objectVectorForNormal[5][0][2] = objectPointsForNormal[5][0][2] - objectPointsForNormal[5][1][2];
    
    //for vector 2
    objectVectorForNormal[5][1][0] = objectPointsForNormal[5][2][0] - objectPointsForNormal[5][1][0];
    objectVectorForNormal[5][1][1] = objectPointsForNormal[5][2][1] - objectPointsForNormal[5][1][1];
    objectVectorForNormal[5][1][2] = objectPointsForNormal[5][2][2] - objectPointsForNormal[5][1][2];
    
    normalizePlane();
    
}

void objects::modifyRotationPoints(float rotX, float rotY, float rotZ, int angleChoice){
    //for right face
    double temp1, temp2;
    float angle = 0.0;
    int t1 = 0, t2 = 0;
    if (angleChoice == 1){
        t1 = 1;
        t2 = 2;
        angle = rotX;
        printf("1");
    }
    else if(angleChoice == 2){
        t1 = 2;
        t2 = 0;
        angle = rotY;
        printf("2");
    }
    else if(angleChoice == 3){
        t1 = 0;
        t2 = 1;
        angle = rotZ;
        printf("3");
    }
    temp1 = objectPointsForNormal[0][0][t1];
    temp2 = objectPointsForNormal[0][0][t2];
    
    objectPointsForNormal[0][0][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[0][0][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    temp1 = objectPointsForNormal[0][1][t1];
    temp2 = objectPointsForNormal[0][1][t2];
    
    objectPointsForNormal[0][1][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[0][1][t2] = temp1*sin(angle) + temp2*cos(angle);

    temp1 = objectPointsForNormal[0][2][t1];
    temp2 = objectPointsForNormal[0][2][t2];
    
    objectPointsForNormal[0][2][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[0][2][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    //
    
    temp1 = objectPointsForNormal[1][0][t1];
    temp2 = objectPointsForNormal[1][0][t2];
    
    objectPointsForNormal[1][0][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[1][0][t2] = temp1*sin(angle) + temp2*cos(angle);

    
    temp1 = objectPointsForNormal[1][1][t1];
    temp2 = objectPointsForNormal[1][1][t2];
    
    objectPointsForNormal[1][1][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[1][1][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    temp1 = objectPointsForNormal[1][2][t1];
    temp2 = objectPointsForNormal[1][2][t2];
    
    objectPointsForNormal[1][2][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[1][2][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    temp1 = objectPointsForNormal[2][0][t1];
    temp2 = objectPointsForNormal[2][0][t2];
    
    objectPointsForNormal[2][0][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[2][0][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    temp1 = objectPointsForNormal[2][1][t1];
    temp2 = objectPointsForNormal[2][1][t2];
    
    objectPointsForNormal[2][1][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[2][1][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    
    temp1 = objectPointsForNormal[2][2][t1];
    temp2 = objectPointsForNormal[2][2][t2];
    
    objectPointsForNormal[2][2][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[2][2][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    //
    
    //for bottom face
    temp1 = objectPointsForNormal[3][0][t1];
    temp2 = objectPointsForNormal[3][0][t2];
    
    objectPointsForNormal[3][0][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[3][0][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    temp1 = objectPointsForNormal[3][1][t1];
    temp2 = objectPointsForNormal[3][1][t2];
    
    objectPointsForNormal[3][1][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[3][1][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    
    temp1 = objectPointsForNormal[3][2][t1];
    temp2 = objectPointsForNormal[3][2][t2];
    
    objectPointsForNormal[3][2][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[3][2][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    //
    
    temp1 = objectPointsForNormal[4][0][t1];
    temp2 = objectPointsForNormal[4][0][t2];
    
    objectPointsForNormal[4][0][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[4][0][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    temp1 = objectPointsForNormal[4][1][t1];
    temp2 = objectPointsForNormal[4][1][t2];
    
    objectPointsForNormal[4][1][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[4][1][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    
    temp1 = objectPointsForNormal[4][2][t1];
    temp2 = objectPointsForNormal[4][2][t2];
    
    objectPointsForNormal[4][2][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[4][2][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    //
    
    temp1 = objectPointsForNormal[5][0][t1];
    temp2 = objectPointsForNormal[5][0][t2];
    
    objectPointsForNormal[5][0][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[5][0][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    temp1 = objectPointsForNormal[5][1][t1];
    temp2 = objectPointsForNormal[5][1][t2];
    
    objectPointsForNormal[5][1][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[5][1][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    
    temp1 = objectPointsForNormal[5][2][t1];
    temp2 = objectPointsForNormal[5][2][t2];
    
    objectPointsForNormal[5][2][t1] = temp1*cos(angle) - temp2*sin(angle);
    objectPointsForNormal[5][2][t2] = temp1*sin(angle) + temp2*cos(angle);
    
    createObjectVectors();
}

std::string objects::changeDataToString()
{

    
    

    std::string stringObject;
    
    
    stringObject = std::to_string(org[0]);
    stringObject = stringObject + "," + std::to_string(org[1]);
    stringObject = stringObject + "," + std::to_string(org[2]);
    stringObject = stringObject + "," + std::to_string(dir[0]);
    stringObject = stringObject + "," + std::to_string(dir[1]);
    stringObject = stringObject + "," + std::to_string(dir[2]);
    stringObject = stringObject + "," + std::to_string(norm[0]);
    stringObject = stringObject + "," + std::to_string(norm[1]);
    stringObject = stringObject + "," + std::to_string(norm[2]);

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            stringObject = stringObject + "," + std::to_string(objectPlaneNormal[i][j]);
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                stringObject = stringObject + "," + std::to_string(objectPointsForNormal[i][j][k]);
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                stringObject = stringObject + "," + std::to_string(objectVectorForNormal[i][j][k]);
            }
        }
    }
    stringObject = stringObject + "," + std::to_string(spherePoints[0]);
    stringObject = stringObject + "," + std::to_string(spherePoints[1]);
    stringObject = stringObject + "," + std::to_string(spherePoints[2]);
    stringObject = stringObject + "," + std::to_string(rotationAngle);
    stringObject = stringObject + "," + std::to_string(translateX);
    stringObject = stringObject + "," + std::to_string(translateY);
    stringObject = stringObject + "," + std::to_string(translateZ);
    stringObject = stringObject + "," + std::to_string(rotateX);
    stringObject = stringObject + "," + std::to_string(rotateY);
    stringObject = stringObject + "," + std::to_string(rotateZ);
    
    (hit == true) ? stringObject = stringObject + "," + "true" : stringObject = stringObject + "," + "false";

    stringObject = stringObject + "," + std::to_string(objectType);
    stringObject = stringObject + "," + std::to_string(drawingMaterial);
    stringObject = stringObject + "," + std::to_string(scaleFactor);

    return stringObject;
}
